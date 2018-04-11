#include "Machine.h"
#include "CPU.h"
#include "Memory.h"
#include "constants.h"
#include "Exception.h"
#include "PCB.h"
#include "useful_classes/LList.h"
#include "useful_classes/MyString.h"
#include "useful_classes/Queue.h"
#include "useful_functions/bit_manipulation.h"
#include "useful_functions/char_arrays.h"

#include "PageTable.h"

#include <stdio.h>
#include <fstream>
using namespace std;


// Default Constructor
// Pre :
// Post: initlizes the Machine class
Machine::Machine() {
  importConfigFile();
  memory = new Memory( memory_size );
  nextPCBId = 1;
  page_table.setSize(memory_size / pagesize);
  page_table.setFreePages(memory_size / pagesize);

}

//PRE:  @param bool & in_bool, iif true the Machine needs input
//      @param bool & out_bool, iif true the Machine is requesting to output
//                              to the terminal
//POST: @return iif out_bool is true is the return meaningful, the output
//      reprents the output to send to the terminal
char * Machine::executeLine(bool & in_bool, bool & out_bool) {

  uint line = getCurrentLine(); //fetch: gets the current line
  cpu.incrementPC();           //once the line is fetched the PC is incremented
  uint opcode = getOpcode(line); //decode: determines opcode being called
  char * output;
  switch(opcode) { //execute: sends to the correct opcode
    case ADD:
      add( getRegX(line), getRegY(line), getRegZ(line) );
      break;
    case NAND:
      nand( getRegX(line), getRegY(line), getRegZ(line) );
      break;
    case ADDI:
      addi( getRegX(line), getRegY(line), getSignedOrOffset(line) );
      break;
    case LW:
      lw( getRegX(line), getRegY(line), getSignedOrOffset(line) );
      break;
    case SW:
      sw( getRegX(line), getRegY(line), getSignedOrOffset(line) );
      break;
    case BEQ:
      beq( getRegX(line), getRegY(line), getSignedOrOffset(line) );
      break;
    case JALR:
      jalr( getRegX(line), getRegY(line) );
      break;
    case HALT:
      halt();
      break;
    case IN:
      in_bool = true;  //signal to say the Machine needs input
      break;
    case OUT:
      out_bool = true; //signal to say the Machine needs output
      output = out( getRegX(line)); //builds the output
      break;
    case LA:
      la( getRegX(line), getSignedOrOffset(line));
      break;
    case BGT:
      bgt( getRegX(line), getRegY(line), getSignedOrOffset(line) );
      break;
  }
  return output;
}

//PRE:  the running_queue must have a process enqueue
//POST: @return ID of the first process in the running queue
uint Machine::getCurrentProcessID() {
  return getCurrentProcess()->getID();
}

//PRE:  @param char * input, the number
//      @param bool & in_bool, is true iff the Machine needs input
//      @param bool & out_bool, is true iff the Machine needs to output
//      @param bool $ done, is true iff the Machine hasnt finnished its process
//      @param bool & post_i_o, tracks if the last command was i/o
//      @param bool & current_process_done, tracks if the process at the
//             front at the front of the queue is done
//      @param bool & set_steps_made, if the steps made has been inited
//POST: @return if out_bool is true return value is meaningful and is requesting
//              for the terminal to output the return value
char * Machine::runCommand(char * input, bool & in_bool, bool & out_bool,
                           bool & done, bool & post_i_o,
                           bool & current_process_done,
                           bool & set_slice_made) {
  char * return_value;
  MyString string = input;                   //copies the char* uinto MyString
  LList<MyString> tokens = string.split(' '); //splits the string at ' '
  MyString command = tokens.getFront();       //gets the command
  if( compareCharArray(command.getString(), COMMANDS[LOAD_NUM]) ) {
    loadSim(input);
    out_bool = false; done = true;
  } else if( compareCharArray(command.getString(), COMMANDS[MEM_NUM]) ) {
    return_value = memSim(input);
    out_bool = true; done = true;
  } else if( compareCharArray(command.getString(), COMMANDS[CPU_NUM]) ) {
    return_value = cpuSim();
    out_bool = true; done = true;
  } else if( compareCharArray(command.getString(), COMMANDS[STEP_NUM]) ) {
    int num_slices = arrayToInt( tokens.getNth(STEP_TOKEN_N).getString() );
    if (!set_slice_made) { //ASSERT: the slices have not been set
      num_slices_made = 0;
      set_slice_made = true;
    }
    return_value = sliceSim(input, in_bool, out_bool, done, post_i_o,
                            current_process_done, num_slices);
    evaluteSliceState(done, num_slices);
  } else if( compareCharArray(command.getString(), COMMANDS[JOBS_NUM]) ) {
    return_value = jobsSim();
    out_bool = true; done = true;
  } else if( compareCharArray(command.getString(), COMMANDS[KILL_NUM]) ) {
    return_value = killSim(input, out_bool);
    done = true;
  } else if( compareCharArray(command.getString(), COMMANDS[CONFIG_NUM]) ) {
    return_value = configSim();
    out_bool = true; done = true;
  }
  return return_value;
}

//PRE:  @param char * input, the number
//      @param bool & in_bool, is true iff the Machine needs input
//      @param bool & out_bool, is true iff the Machine needs to output
//      @param bool $ done, is true iff the Machine hasnt finnished its process
//      @param bool & post_i_o, tracks if the last command was i/o
//      @param bool & current_process_done, tracks if the process at the
//             front at the front of the queue is done
//      @param uint num_slices, the number of slices given to the terminal
//POST: @return if out_bool is true return value is meaningful and is requesting
//              for the terminal to output the return value, runs a slice of the
//              program, the slice is dependent on the config file also iterates
//              slices_made once all programs have been slices through
char * Machine::sliceSim(char * input, bool & in_bool, bool & out_bool,
                         bool & done, bool & post_i_o,
                         bool & current_process_done,
                         uint num_slices) {
  PCB * current_process = getCurrentProcess();
  char * return_value;
  if(post_i_o && current_process_done) {
   //ASSERT: the prog needed i/o, it has taken it and is now done
   setFrontToBackQueue();
   post_i_o = false;
   current_process_done = false;
  }
  bool job_stepped = false;
  if(num_slices > num_slices_made) {
   return_value = stepSim(timeslice, in_bool, out_bool, done);
   job_stepped = true; // track if a job has ran this iteration
  }
  if(job_stepped) {
   //ASSERT: job has stepped this iteration and must be evaluated if it should
   //        removed, moved to the back, or stay at the front of the queue
   evaluteJobState(current_process_done, in_bool, out_bool, done);
  }
  return return_value;
}

//PRE: @param bool & current_process_done, tracks if the process at the front at
//     the front of the queue is done
//     @param bool in_bool, is true iff the Machine needs input
//     @param bool out_bool, is true iff the Machine needs to output
//     @param bool done, is true iff the Machine hasnt finnished its process
//POST:evalutes the state of the jobs and continues, rotates, or kills the jobs
//     depending on the state of the jobs
void Machine::evaluteJobState(bool & current_process_done,
                              bool in_bool, bool out_bool, bool done) {
  PCB * current_process = getCurrentProcess();
  if (current_process->getHalt() == true) {
    terminateProcess(current_process->getID());
    current_process_done = false;
  } else if( (in_bool || out_bool) && done) {
    current_process_done = true;
    //ASSERT: will be removed at the beginning of the next iteration
  } else if( done ) {
    setFrontToBackQueue();
    current_process_done = false;
  }
}

//PRE:  @param bool & done,
//      @param uint num_slices
//      should be called after running_queue is edited or a PCB has been ran
//POST: after the running_queue or PCB has been ran evalutes the state
//      of slices and sets the proper values to continue or stop
void Machine::evaluteSliceState(bool & done, uint num_slices) {
  if(num_slices > num_slices_made && done) {
   //ASSERT: the current slice iteration is done, move to the next
   done = false;
   num_slices_made++;
 } else if (num_slices == num_slices_made) {
   //ASSERT: All slicing is done
   done = true;
  }
}

//PRE: @param uint & jobs_to_go, the number of jobs compleated in the slice
//POST: imports the registers of the cpu and pc, and sets the front to the back
//      of the queue
void Machine::setFrontToBackQueue() {
  PCB * current_process = getCurrentProcess();
  current_process->setPC(cpu.getPC());
  importRegistersCPUToPCB();
  running_queue.frontToBack();
  readyCurrentProcessOnCPU();
}

//PRE:  @param char * input gets the program name from the input
//                    takes the input from the terminal
//                    must be no longer than 2 words
//                    must be a load command
//POST: @returns a dynamicly created char* of the progam name + .lce
char * Machine::getProgamName(char * input) {
  MyString string = input;                   //copies the char* into a MyString
  LList<MyString> tokens = string.split(' ');//splits the string at ' '
  MyString name = tokens.getBack();          //gets the second param
  name.addString((char*)".lce");             //adds the .lce to the program
  return name.getStringDeepCopy();
}

//PRE:  @param char * input, takes the input from the terminal
//                           must be no longer than 2 words
//                           F
//POST: loads the program into the memory location starting at 0
//(Exception((char *)"ERROR: FILE FAILED TO OPEN"));
void Machine::loadSim(char * input) {
  char * file_name = getProgamName(input); //gets the progam name with + .lce
  fstream stream (file_name, ios::in | ios::out);
  if(stream == NULL) {
    //ASSERT: The file could not be opened
    throw(Exception((char *)"ERROR: FILE FAILED TO OPEN"));
  }
  // //ASSERT: the file is can me read from
  uint length;           // holds the length of progam
  stream >> length;      // gets the length of the program
  char ch = stream.get();
  uint begining = stream.tellg();
  PCB * proccess = new PCB(file_name, nextPCBId, length, begining);
  //*(proccess->getStream());
  nextPCBId++;
  uint SP = (length + stack_size) * BYTES_IN_WORD - BYTES_IN_WORD;
  proccess->initPCB(SP);
  //load into memory
  running_queue.enqueue(proccess);
  if(running_queue.getSize() == 1) {
    readyCurrentProcessOnCPU();
  }
  if(page_table.getNumberOfFree() >= 2) {
    //ASSERT: can import both the stack page and the memory page
    page_table.insertPage(proccess, 0, true);
    int physical_number = page_table.insertPage(proccess, 0, false);
    importPage(proccess, 0, physical_number);
  } else {
    throw(Exception((char *)"ERROR: INSUFFICIENT MEMORY"));
  }

}

//PRE:  @param PCB * proccess, the pointer to the process to get
//      @param uint virtual_page_number, the virtual_page_number you wish to
//      @param uint physical_page_number, the physical_page_number to load to
//POST: imports the page if the space is sufficent
void Machine::importPage(PCB * proccess, uint virtual_page_number,
                         uint physical_page_number) {
  int offset = pagesize * BYTES_IN_WORD * virtual_page_number;
  int set_file = proccess->getStreamStart() + offset;
  uint current_line = pagesize * physical_page_number * BYTES_IN_WORD;
  (proccess->getStream())->seekp(set_file, ios::beg);
  char ch;
  for(int word_count = 0; word_count < pagesize; word_count++) {
    uint word = 0;
    //to build the word
    for (int byte_num = 0; byte_num < BYTES_IN_WORD; byte_num++) { //x00112233
      //to add the char in the correct place
      (proccess->getStream())->get(ch);
      uint byte = getBits((uint)ch, 7, 0);
      word = insertByte (word, byte, byte_num);
    }
    //printf ("%d: 0x%08X \n", current_line, word);
    memory->setAddress(current_line, word); //adds the line to memory
    current_line = (current_line + BYTES_IN_WORD);
  }
}


//PRE: @param int num_step, the number of lines to execute
//     @param bool in, iif true the program needs input
//     @param book out iif true the program needs output
//     @param done iff the progam has reached the halt statemet or reaches its
//                 num_steps
//POST:@return if out is true returns the output to the termainl
//current_process = NULL throw(Exception((char *)"ERROR: NO PROGRAM LOADED"));
char * Machine::stepSim(int num_steps, bool & in, bool & out, bool & done) {
  char * output; // holds the memory location of output only meaningful iff
                 // out = True otherwise is garbage
  PCB * current_process = getCurrentProcess();
  if(current_process != NULL) {
    while(current_process->ableToRun(num_steps) && !in && !out && !done) {
        output = executeLine(in, out);
        current_process->incrementSteps();
    }
    if(num_steps == current_process->getSteps()) {
        done = true;
        current_process->resetSteps();
    }
    if (current_process->getHalt()) {
      done = true;
      out = true;
      output = new char [DONE_MESSAGE_LENGTH];
      sprintf (output, "PCB(%d) completed. \n", current_process->getID());
    }
  } else {
    throw(Exception((char *)"ERROR: NO PROGRAM LOADED"));
  }
  return output;
}

//PRE:  @param char * input, takes the input to run
//POST: @return char*, the content of memory
//      if 1 token given, 0 - memory size
//      if 2 tokens token[1] - memory size
//      if 3 tokens token[1] - token[2]
char * Machine::memSim(char * input) {
  return memory->getOutput(input);
}

//PRE:  @param char * input, takes the input to run
//POST: @returns a char* that is properly formated
char * Machine::cpuSim() {
  return cpu.getOutput();
}

//PRE: the Machine be running
//POST: @return char* the array that displays the jobs to the user
char * Machine::jobsSim() {
  MyString string;
  for(int i = 0; running_queue.getSize() > i; i++) {
    PCB * process = running_queue.getNth(i);
    char * line = new char [MAX_JOB_LINE];
    sprintf (line, "Name(%d): %s\n", process->getID(), process->getName());
    string.addString(line);
    sprintf (line, "PC: %d\n", process->getPC());
    string.addString(line);
    if(running_queue.getSize() - 1 != i) {
      //add spacing between jobs to make more readable
      string.add('\n');
    }
    delete [] line;
  }
  if (running_queue.getSize() == 0) {
    char * line = new char [MAX_JOB_LINE];
    sprintf (line, "NO CURRENT JOBS. \n");
    string.addString(line);
  }

  return string.getStringDeepCopy();
}

//PRE:  @param char * input, takes the input to kill meaning two words
//      separated by a ' ', the first being the str kill and the second
//      being a positive intager that will reprent the PCB id that will be
//      killed, ie kill <int>
//      @param bool & output, if there is not process found, will return not
//      found
//POST: kills the program and releases the memory back to freemem and removes
//      the job from the runnin queue
char * Machine::killSim(char * input, bool & out_bool) {
  MyString string = input;
  MyString output;
  LList<MyString> tokens = string.split(' '); //splits the string at ' '
  tokens.deleteFront();
  uint id = arrayToInt(tokens.getFront().getString());
  bool found = terminateProcess(id); //removes the process, if fals
                                     //it was not found
  if (found == false) {
    //ASSERT: no process id by that uint
    char * line = new char [MAX_KILL_LINE];
    sprintf (line, "PROCESS IS NOT FOUND. \n");
    output.addString(line);
    out_bool = true;
  }
  return output.getStringDeepCopy();
}

//PRE:  the machine be started
//POST: returns the contents of the .lc_config to the terminal
char * Machine::configSim() {
  char * line = new char [MAX_CONFIG_LINE];
  MyString str;
  sprintf (line, "memory_size: %d\n", memory_size);
  str.addString(line);
  sprintf (line, "stack_size: %d\n", stack_size);
  str.addString(line);
  sprintf (line, "timeslice: %d\n", timeslice);
  str.addString(line);
  sprintf (line, "pagesize: %d\n", pagesize);
  str.addString(line);
  sprintf (line, "swapspace: %d\n", swapspace);
  str.addString(line);
  sprintf (line, "paging: %d\n", paging);
  str.addString(line);
  delete [] line;
  return str.getStringDeepCopy();
}

//PRE: takes the id of the process being removed
//POST: removes that process from the running queue and frees the memory_size that
//      it was allocating
//      @return whether the process was found or not
bool Machine::terminateProcess(uint pid) {
  bool found = false;
  int size = running_queue.getSize();
  int i = 0;
  while(!found || size < i) {
    PCB * process = running_queue.getNthQueued(i);
    if(process->getID() == pid) {
      running_queue.deleteNthQueued(i);
      //delete process; //deletes process
      found = true;
      if(i == 0) {
        //current_process was removed next process needs to be readied
        readyCurrentProcessOnCPU();
      }
    }
    i++;
  }
  return found;
}

//PRE:
//POST: cpu.registers, cpu.SP, cpu.PC now reflect their corresponding values
//      in the PCB process given to the method
void Machine::importRegistersPCBToCPU() {
  PCB * current_process = getCurrentProcess();
  for(int i = 0; i < MAX_REGISTERS; i++) {
    cpu.setRegister(i, current_process->getRegister(i));
  }
}

//PRE:
//POST: PCB.registers, PCB.SP, PCB.PC now reflect their corresponding values
//      in the cpu
void Machine::importRegistersCPUToPCB() {
  PCB * current_process = getCurrentProcess();
  for(int i = 0; i < MAX_REGISTERS; i++) {
    current_process->setRegister(i, cpu.getRegister(i));
  }
}

//PRE: Assumes that the process at the begining of the queue has not
//     been prepared on the cpu to run
//POST:copys the registers and PC of the process and the start of the queue
//     to the cpu
void Machine::readyCurrentProcessOnCPU() {
  if(running_queue.getQueueSize() != 0) {
    PCB * current_process = getCurrentProcess();
    cpu.setPC(current_process->getPC());
    importRegistersPCBToCPU();
  }
}

//======================================
// current process
//======================================

//PRE:
//POST: returns the first in the running_queue process if running_queue > 0
//      else returns NULL
PCB * Machine::getCurrentProcess() {
  PCB * current_process = NULL;
  if(running_queue.getQueueSize() != 0) {
     current_process = running_queue.getNthQueued(0);
  }
  return current_process;
}

//PRE: .lc_config must be in the same directory as the simulator
//POST: reads the .lc_config from the current directory and sets the
//      the setting in the machine to corresponding option in the config
void Machine::importConfigFile() {
	ifstream inFile(".lc_config");
	if(inFile == NULL) {
		throw(Exception((char *)".lc_config file can not be opened"));
	}
	char temp;
	while(!inFile.eof()) {
		MyString option;
		temp = inFile.get();
		while(temp != '\n' && !inFile.eof()) {
			if(!inFile.eof()) {
				option.add(temp); //adds char to mystring
				temp = inFile.get();
			}
		}
		if(!inFile.eof()) {
			//split the string by its spaces
			LList<MyString> tokens = option.split(' ');
			setConfigOption(tokens);
		}
	}
  inFile.close();
  if(memory_size % pagesize != 0 || stack_size % pagesize != 0 ||
     swapspace % pagesize != 0 || memory_size == 0 || stack_size == 0) {
		throw(Exception((char *)"ERROR: Invalid Config file"));
	}
}

//PRE:  Taking a LList of MyString objects, the LList of the must be no more
//      than 2 and the second token must be a given option for the lc2200 and
//      the first must be a be a positive intager
//POST: sets the option in the second node to the setting of the lc2200
void Machine::setConfigOption(LList<MyString> tokens) {
  if(tokens.getSize() == PARAMS_IN_CONFIG) {
    MyString token = tokens.getNth(0);
    if(token.isEqual(MyString(CONFIG_OPTIONS[MEMORY_OPTION_INDEX]))) {
      uint temp = arrayToInt(tokens.getNth(1).getString());
      if(temp > 0) {
        memory_size = temp;
      } else {
        throw(Exception((char *)"ERROR: INVALID CONFIG FILE: MEMORY <= 0"));
      }
    }
    if(token.isEqual(MyString(CONFIG_OPTIONS[STACK_OPTION_INDEX]))) {
      uint temp = arrayToInt(tokens.getNth(1).getString());
      if(temp > 0) {
        stack_size = temp;
      } else {
        throw(Exception((char *)"ERROR: INVALID CONFIG FILE: stack <= 0"));
      }
    }
    if(token.isEqual(MyString(CONFIG_OPTIONS[TIMESLICE_INDEX]))) {
      uint temp = arrayToInt(tokens.getNth(1).getString());
      if(temp > 0) {
        timeslice = temp;
      } else {
        throw(Exception((char *)"ERROR: INVALID CONFIG FILE: TIMESLICE"));
      }
    }
    if(token.isEqual(MyString(CONFIG_OPTIONS[PAGESIZE_INDEX]))) {
      uint temp = arrayToInt(tokens.getNth(1).getString());
      if(temp > 0) {
        pagesize = temp;
      } else {
        throw(Exception((char *)"ERROR: INVALID CONFIG FILE: PAGESIZE"));
      }
    }
    if(token.isEqual(MyString(CONFIG_OPTIONS[SWAPSPACE_INDEX]))) {
      uint temp = arrayToInt(tokens.getNth(1).getString());
      swapspace = temp;
    }
    if(token.isEqual(MyString(CONFIG_OPTIONS[PAGING_INDEX]))) {
      uint temp = arrayToInt(tokens.getNth(1).getString());
      paging = temp;
    }
  } else {
    throw(Exception((char *)"ERROR: Invalid Config file"));
  }
}

//======================================
// Word Getters
//======================================

//PRE:  @param int line, is the line to be executed, lenth = 4 bytes
//POST: @return int opcode from the line is executed
uint Machine::getOpcode(uint line){
  return getBits(line, OPCODE_UPPER_BIT, OPCODE_LOWER_BIT);
}

//PRE:  @param uint line, is the line to be executed, lenth = 4 bytes
//POST: @return uint regX from the line is executed
uint Machine::getRegX(uint line) {
  return getBits(line, REGX_UPPER_BIT, REGX_LOWER_BIT);
}

//PRE:  @param uint line, is the line to be executed, lenth = 4 bytes
//POST: @return uint regY from the line is executed
uint Machine::getRegY(uint line) {
  return getBits(line, REGY_UPPER_BIT, REGY_LOWER_BIT);
}

//PRE:  @param uint line, is the line to be executed, lenth = 4 bytes
//POST: @return uint regZ from the line is executed
uint Machine::getRegZ(uint line) {
  return getBits(line, REGZ_UPPER_BIT, REGZ_LOWER_BIT);
}

//PRE:  @param uint line, is the line to be executed, lenth = 4 bytes
//POST: @return uint Signed Value or Offset from the line is executed
uint Machine::getSignedOrOffset(uint line) {
  //printf("line: %08x \n", line);
  uint rv = getBits(line, SIGNED_OR_OFFSET_UPPER_BIT,
                   SIGNED_OR_OFFSET_LOWER_BIT, true);
  //ASSERT: the program must account for neg for the signed or offset so
  //        true is given as an optional parma
  return rv;
}

//PRE:
//POST: @returns the current progame line
uint Machine::getCurrentLine() {
  PCB * current_process = getCurrentProcess();
  uint address = current_process->filterPC(cpu.getPC(), pagesize, stack_size);
  return memory->getAddress(address);
}

//PRE:
//POST: @returns the previous progame line
uint Machine::getPrevLine() {
  PCB * current_process = getCurrentProcess();
  uint address = current_process->filterPC(cpu.getPC() - BYTES_IN_WORD,
                                           pagesize, stack_size);
  return memory->getAddress(address);
}

//PRE: @param uint address, the address of memory trying to be used
//POST the Method throws an error iff the memory is out of bounds
//     otherwise does nothing. if error is thrown the current_process is set
//     to null and is terminated.
//throw(Exception((char *)"ERROR: ATTEMPTING TO ACCESS MEMORY maOUT OF BOUNDS,
//PROCESS TERMINATED."));
void Machine::checkAddressOutOfBounds(uint address) {
  PCB * current_process = getCurrentProcess();
  uint upper_b = ((current_process->getLength() + stack_size) * BYTES_IN_WORD)
                    - BYTES_IN_WORD;
  if(upper_b < address) {
    PCB * current_process = getCurrentProcess();
    terminateProcess(current_process->getID());
    throw(Exception((char *)"ERROR: ATTEMPTING TO ACCESS MEMORY OUT OF BOUNDS, PROCESS TERMINATED."));
  }
}

//PRE:  @param uint reg, the re
//      @param int value
//POST: does not return, checks if the $zero register is used and is not
//      0 it throws and error
void Machine::checkZeroRegisterChange(uint reg, int value) {
  if (reg == 0 && value != 0) {
    PCB * current_process = getCurrentProcess();
    terminateProcess(current_process->getID());
    throw(Exception((char *)"ERROR: ZERO REGISTER CAN NOT BE CHANGED."));
  }
}

//======================================
// INPUT
//======================================

//PRE:  @param uint input, should be valid to be entered to a register at the
//      current line
//POST: sets the register specifed in the current line to the input taken
void Machine::giveInput(char * input) {
  uint line = getPrevLine();
  uint num = arrayToInt(input);
  in( getRegX(line), num );
}

//======================================
// R - Type Operations
//======================================

//PRE:  @param uint regX, regY, and regZ, range [0-15] inclusive
//POST: register[regX] will reflect the sum of register[regY] and
//      register[regY]
void Machine::add(uint regX, uint regY, uint regZ) {
  uint sum = cpu.getRegister(regY) + cpu.getRegister(regZ);
  checkZeroRegisterChange(regX, sum);
  cpu.setRegister(regX, sum);
}

//PRE:  @param uint regX, regY, and regZ, range [0-15] inclusive
//POST: register[regX] will reflect the ~and of register[regY] and
//      register[regY]
void Machine::nand(uint regX, uint regY, uint regZ) {
  uint not_and = ~( cpu.getRegister(regY) & cpu.getRegister(regZ) );
  checkZeroRegisterChange(regX, not_and);
  cpu.setRegister(regX, not_and);
}

//======================================
// I - Type Operations
//======================================

//PRE:  @param uint regX and regY, range [0-15] inclusive
//      @param uint num, holds uint to be added
//POST: register[regX] = register[regY] + num
void Machine::addi(uint regX, uint regY, uint num) {
  //printf ("Number: %x \n", num);
  //printf("value: %08x, %d", num, num);
  uint sum = cpu.getRegister(regY) + num;
  checkZeroRegisterChange(regX, sum);
  cpu.setRegister(regX, sum);
}

//PRE:  @param uint regX and regY, range [0-15] inclusive
//      @param uint num, holds the uint be be added to regY to solve location
//POST: loads the content register[regY]+ address and stores it to
//      register[regX]
void Machine::lw(uint regX, uint regY, uint num) {
  uint address = num + cpu.getRegister(regY);
  checkAddressOutOfBounds(address);
  //ASSERT: Address is valid
  PCB * current_process = getCurrentProcess();
  address = current_process->filterPC(address, pagesize, stack_size);
  uint content = memory->getAddress(address); //adds the line to memory
  checkZeroRegisterChange(regX, content);
  cpu.setRegister(regX, content);
}

//PRE:  @param uint regX and regY, range [0-15] inclusive
//      @param uint num, holds the uint be be added to regY to solve location
//POST: stored the content of register[regX] to register[regY]+ address
void Machine::sw(uint regX, uint regY, uint num) {
  uint address = num + cpu.getRegister(regY);
  //EDIT: check if out of bounds
  checkAddressOutOfBounds(address);
  uint content = cpu.getRegister(regX);
  //ASSERT: Address is valid
  PCB * current_process = getCurrentProcess();
  address = current_process->filterPC(address, pagesize, stack_size);
  memory->setAddress(address, content);
}

//PRE:  @param uint regX and regY, range [0-15] inclusive
//      @param uint offset, holds the signed_value or offset
//POST: if regX == regY offset added to PC else nothing
void Machine::beq(uint regX, uint regY, uint offset) {
  if ( cpu.getRegister(regX) == cpu.getRegister(regY) ) {
    //ASSERT: change pc if they are equal
    //ASSERT: can assume the address is in bounds
    checkAddressOutOfBounds(offset + cpu.getPC());
    cpu.setPC( offset + cpu.getPC() );
  }
}

//PRE:  @param uint regX and regY, range [0-15] inclusive
//      @param uint offset, holds the signed_value or offset
//POST: if regX > regY offset added to PC else nothing
void Machine::bgt(uint regX, uint regY, uint offset) {
  if ( cpu.getRegister(regX) > cpu.getRegister(regY) ) {
    //ASSERT: change pc if they are equal
    //ASSERT: can assume the address is in bounds
    checkAddressOutOfBounds(offset + cpu.getPC());
    cpu.setPC( offset + cpu.getPC() );
  }
}

//======================================
// J - Type Operations
//======================================

//PRE:  @param uint regX and regY, range [0-15] inclusive
//POST: set regX to be PC, set PC to be regY
//throw(Exception((char *)"ERROR: JALR DOES NOT TAKE $sp, PROCESS TERMINATED"));
//if above error is hit the process is terminated
void Machine::jalr(uint regX, uint regY) {
  //regX holds the value trying to jalr to, this must be tested to be
  //ASSERT: regX is not the stack pointer
  checkAddressOutOfBounds(cpu.getRegister(regX));
  //ASSERT: Address is valid
  checkZeroRegisterChange(regY, cpu.getPC());
  cpu.setRegister(regY, cpu.getPC() );
  cpu.setPC( cpu.getRegister(regX) ); //test jalr
}

//======================================
// U - Type Operations
//======================================

//PRE: @param uint regX, range [0-15] inclusive
//PRE: @param uint num, the number to be entered to regX
//POST: takes input from terminal, x and sets regX = x;
void Machine::in(uint regX, uint num) {
  checkZeroRegisterChange(regX, num);
  cpu.setRegister(regX, num);
}

//PRE:  @param uint regX, range [0-15] inclusive
//POST: pruints the content of regX to the terminal
char * Machine::out(uint regX) {
  //this will have to be edited to char * and allocated memory to it
  PCB * current_process = getCurrentProcess();
  char * output = new char [MAX_PROG_OUTPUT_SIZE];
  sprintf (output, "PCB(%d) Output: %d \n", current_process->getID(),
                                    cpu.getRegister(regX));
  return output;
}

//======================================
// L - Type Operations
//======================================

//PRE:  @param uint regX, range [0-15] inclusive
//      @param int num, holds the signed_value or offset
//POST: prints the content of regX to the terminal
void Machine::la(uint regX, int num) {
  int temp = num + cpu.getPC(); //fix to go to the current addresses
  if(temp < 0) {
    throw(Exception((char *)"ERROR: LA given incorrect address"));
  } else {
    uint address = temp; //fix to go to the current addresses
    checkAddressOutOfBounds(address);
    //ASSERT: address in bounds
    checkZeroRegisterChange(regX, address);
    cpu.setRegister(regX, address);
  }
}

//======================================
// O - Type Operations
//======================================

//PRE:  takes no params
//POST: stops the program
void Machine::halt() {
  PCB * current_process = getCurrentProcess();
  current_process->haltProgram();
}

Machine::~Machine() {
  if(memory != NULL) {
    delete memory;
    memory = NULL;
  }
}
