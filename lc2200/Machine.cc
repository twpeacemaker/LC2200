#include "Machine.h"
#include "CPU.h"
#include "Memory.h"
#include "constants.h"
#include "Exception.h"
#include "PCB.h"
#include <stdio.h>
#include <fstream>
using namespace std;
#include "useful_classes/LList.h"
#include "useful_classes/MyString.h"
#include "useful_functions/bit_manipulation.h"
#include "useful_functions/char_arrays.h"

// Default Constructor
// Pre :
// Post: initlizes the Machine class
Machine::Machine() {
  memory = new Memory(); //DEFAULT_MEM
  current_process = NULL;
}


// Pre : @param uint memory_size inits the size of memory
// Post: initlizes the Machine class
Machine::Machine(uint memory_size) {
  memory = new Memory( memory_size ); ////if is specified
  current_process = NULL;

}

//PRE:  @param bool & in_bool, if true the Machine needs input
//      @param bool & out_bool, if true the Machine is requesting to output
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

//PRE:  @param char * input, the number
//      @param bool & in_bool, is true iff the Machine needs input
//      @param bool & out_bool,is true iff the Machine needs to output
//      @param bool $ done, is true iff the Machine has hit the halt statement
//POST: @return if out_bool is true return value is meaningful and is requesting
//              for the terminal to output the return value
char * Machine::runCommand(char * input, bool & in_bool, bool & out_bool,
                           bool & done) {
  char * return_value;
  MyString string = input;                    //copies the char* uinto a MyString
  LList<MyString> tokens = string.split(' '); //splits the string at ' '
  MyString command = tokens.getFront();       //gets the command
  if( compareCharArray(command.getString(), COMMANDS[LOAD_NUM]) ) {
    loadSim(input);
    out_bool = false;
    done = true;
  }
  else if( compareCharArray(command.getString(), COMMANDS[MEM_NUM]) ) {
    return_value = memSim(input);
    out_bool = true;
    done = true;
  }
  else if( compareCharArray(command.getString(), COMMANDS[CPU_NUM]) ) {
    return_value = cpuSim();
    out_bool = true;
    done = true;
  }
  else if( compareCharArray(command.getString(), COMMANDS[STEP_NUM]) ) {
    int num_steps = arrayToInt( tokens.getNth(STEP_TOKEN_N).getString() );
    return_value = stepSim(num_steps, in_bool, out_bool, done);
  }
  else if( compareCharArray(command.getString(), COMMANDS[RUN_NUM]) ) {
    if(current_process->getHalt() == false) {
      //ASSERT: the program has not hit a halt statement run another step of
      //        the program
      return_value = stepSim(1, in_bool, out_bool, done);
      done = false;
    } else {
      //ASSERT: the program has hit its halt statement and now is done
      done = true;
    }
  }
  return return_value;
}

//PRE:  @param char * input gets thr program name from the input
//                    takes the input from the terminal
//                    must be no longer than 2 words
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
//POST: loads the program into the memory location starting at 0
void Machine::loadSim(char * input) {
  char * file_name = getProgamName(input); //gets the progam name with + .lce
  ifstream inFile(file_name); //openfile stream
  if(inFile == NULL) {
    //ASSERT: The file could not be opened
    throw(Exception((char *)"ERROR: FILE FAILED TO OPEN"));
  }
  //ASSERT: the file is can me read from
  uint length;           // holds the length of progam
  inFile >> length;      // gets the length of the program
  char ch;               // will hold each charater
  uint current_line = 0; // of memory
  inFile.get(ch);        //gets the new line character
  for(int word_count = 0; word_count < length; word_count++) {
    uint word = 0;        //0x00000000
    //to build the word
    for (int byte_num = 0; byte_num < BYTES_IN_WORD; byte_num++) { //x00112233
      //to add the char in the correct place
      inFile.get(ch);
      uint byte = getBits((uint)ch, 7, 0);
      word = insertByte (word, byte, byte_num);
    }
    memory->setIndex(current_line, word); //adds the line to memory
    current_line = (current_line + BYTES_IN_WORD);
  }
  inFile.close(); // close the filestream
  current_process = new PCB(file_name, length);
  cpu.setPC(0);
  cpu.setSP(memory->getLastAddress());
}

//PRE: @param int num_step, the number of lines to execute
//     @param bool in, iif true the program needs input
//     @param book out iif true the program needs output
//     @param done iff the progam has reached the halt statemetn
//POST:@return if out is true returns the output to the termainl
char * Machine::stepSim(int num_steps, bool & in, bool & out, bool & done) {
  char * output; // holds the memory location of output only meaningful iff
                 // out = True otherwise is garbage
  if(current_process != NULL) {
    while(current_process->ableToRun(num_steps) && !in && !out && !done) {
        output = executeLine(in, out);
        current_process->incrementSteps();
    }
    if(num_steps == current_process->getSteps()) {
        done = true;
        current_process->resetSteps();
    } if (current_process->getHalt()) {
      done = true;
      out = true;
      output = new char [DONE_MESSAGE_LENGTH];
      sprintf (output, "Process completed. \n"); //PID will have to use this
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
  return memory->getIndex(cpu.getPC());
}

//PRE:
//POST: @returns the previous progame line
uint Machine::getPrevLine() {
  return memory->getIndex(cpu.getPC() - BYTES_IN_WORD);
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

  cpu.setRegister(regX, sum);
}

//PRE:  @param uint regX, regY, and regZ, range [0-15] inclusive
//POST: register[regX] will reflect the ~and of register[regY] and
//      register[regY]
void Machine::nand(uint regX, uint regY, uint regZ) {
  uint not_and = ~( cpu.getRegister(regY) & cpu.getRegister(regZ) );
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
  cpu.setRegister(regX, sum);
}

//PRE:  @param uint regX and regY, range [0-15] inclusive
//      @param uint num, holds the uint be be added to regY to solve location
//POST: loads the content register[regY]+ address and stores it to
//      register[regX]
void Machine::lw(uint regX, uint regY, uint num) {
  uint address = num + cpu.getRegister(regY);
  uint content = memory->getIndex(address); //adds the line to memory
  cpu.setRegister(regX, content);
}

//PRE:  @param uint regX and regY, range [0-15] inclusive
//      @param uint num, holds the uint be be added to regY to solve location
//POST: stored the content of register[regX] to register[regY]+ address
void Machine::sw(uint regX, uint regY, uint num) {
  uint address = num + cpu.getRegister(regY);
  uint content = cpu.getRegister(regX);
  memory->setIndex(address, content);
}

//PRE:  @param uint regX and regY, range [0-15] inclusive
//      @param uint offset, holds the signed_value or offset
//POST: if regX == regY offset added to PC else nothing
void Machine::beq(uint regX, uint regY, uint offset) {
  if ( cpu.getRegister(regX) == cpu.getRegister(regY) ) {
    //ASSERT: change pc if they are equal
    cpu.setPC( offset + cpu.getPC() );
  } //assert else do nothing
}

//PRE:  @param uint regX and regY, range [0-15] inclusive
//      @param uint offset, holds the signed_value or offset
//POST: if regX > regY offset added to PC else nothing
void Machine::bgt(uint regX, uint regY, uint offset) {
  if ( cpu.getRegister(regX) > cpu.getRegister(regY) ) {
    //ASSERT: change pc if they are equal
    cpu.setPC( offset + cpu.getPC() );
  }
}

//======================================
// J - Type Operations
//======================================

//PRE:  @param uint regX and regY, range [0-15] inclusive
//POST: set regX to be PC, set PC to be regY
void Machine::jalr(uint regX, uint regY) {
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
    cpu.setRegister(regX, num);
}

//PRE:  @param uint regX, range [0-15] inclusive
//POST: pruints the content of regX to the terminal
char * Machine::out(uint regX) {
  //this will have to be edited to char * and allocated memory to it
  char * output = new char [MAX_PROG_OUTPUT_SIZE];
  sprintf (output, "%d \n", cpu.getRegister(regX));
  return output;
}

//======================================
// L - Type Operations
//======================================

//PRE:  @param int regX, range [0-15] inclusive
//      @param int offset, holds the signed_value or offset
//POST: prints the content of regX to the terminal
void Machine::la(uint regX, uint num) {
  uint address = num + cpu.getPC(); //fix to go to the current addresses
  cpu.setRegister(regX, address);
}

//======================================
// O - Type Operations
//======================================

//PRE:  takes no params
//POST: stops the program
void Machine::halt() {
  current_process->haltProgram();
}
