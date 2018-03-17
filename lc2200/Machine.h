#ifndef INCLUDED_Machine
#define INCLUDED_Machine

#include "CPU.h"
#include "Memory.h"
#include "constants.h"
#include "Exception.h"
#include "PCB.h"
#include "Freemem.h"
#include <stdio.h>
#include <fstream>
using namespace std;
#include "useful_classes/LList.h"
#include "useful_classes/MyString.h"
#include "useful_classes/Queue.h"
#include "useful_functions/bit_manipulation.h"
#include "useful_functions/char_arrays.h"

class Machine {

  // Class Invariant (CI): must point to a valid memory object and must have
  // have valid cpu that facilitate the memory, pc, registers for the Machine
  // the machine processes in a fetch, decode, execute cycle. will contain a
  // running queue, and a freemem LList that will hold at least one
  // object, this list will hold all the free memory that is usable to the
  // machine. nextPCBId will be incremented every time assigned to PCB and no
  // process will be given the same id, stack_size will always be > memory_size
  // mem_management will be that value 0 or 1, 0 will follow the first fit
  // memory management policy and 1 will denote best fit policy. .lc_config
  // will be read and will populate the values of mem_management, memory_size,
  // and stack_size. timeslice will be a positive intager that will be greater
  // than zero

  private:

    CPU cpu;
    Memory * memory;
    uint memory_size;
    uint stack_size;
    uint mem_management;
    Queue<PCB*> running_queue;
    uint nextPCBId;
    LList<Freemem*> freemem;

    uint timeslice;

    bool timesliceing;
    uint num_slices_made;
    uint jobs_to_go;




    //======================================
    // Word Getters
    //======================================

    //PRE:  @param uint line, is the line to be executed, lenth = 4 bytes
    //POST: @return uint opcode from the line is executed
    uint getOpcode(uint line);

    //PRE:  @param uint line, is the line to be executed, lenth = 4 bytes
    //POST: @return uint regX from the line is executed
    uint getRegX(uint line);

    //PRE:  @param uint line, is the line to be executed, lenth = 4 bytes
    //POST: @return uint regY from the line is executed
    uint getRegY(uint line);

    //PRE:  @param uint line, is the line to be executed, lenth = 4 bytes
    //POST: @return uint regZ from the line is executed
    uint getRegZ(uint line);

    //PRE:  @param uint line, is the line to be executed, lenth = 4 bytes
    //POST: @return uint Signed Value or Offset from the line is executed
    uint getSignedOrOffset(uint line);

    //PRE:
    //POST: @returns the current progame line
    uint getCurrentLine();

    //PRE:
    //POST: @returns the previous progame line
    uint getPrevLine();

    //PRE: @param uint address, the address of memory trying to be used
    //POST the Method throws an error iff the memory is out of bounds
    //     otherwise does nothing. if error is thrown the current_process is set
    //     to null and is terminated.
    //     throw(Exception((char *)"ERROR: ATTEMPTING TO ACCESS MEMORY OUT OF
    //                              BOUNDS, PROCESS TERMINATED."));
    void checkAddressOutOfBounds(uint address);

    //PRE:  @param uint reg, the re
    //      @param int value
    //POST: does not return, checks if the $zero register is used and is not
    //      0 it throws and error
    void checkZeroRegisterChange(uint reg, int value);

    //PRE: takes the id of the process being removed
    //POST: removes that process from the running queue and frees the memory that
    //      it was allocating
    //      @return whether the process was found or not
    bool terminateProcess(uint pid);

    //======================================
    // R - Type Operations
    //======================================

    //PRE:  @param uint regX, regY, and regZ, range [0-15] inclusive
    //POST: register[regX] will reflect the sum of register[regY] and
    //      register[regY]
    void add(uint regX, uint regY, uint regZ);

    //PRE:  @param uint regX, regY, and regZ, range [0-15] inclusive
    //POST: register[regX] will reflect the ~and of register[regY] and
    //      register[regY]
    void nand(uint regX, uint regY, uint regZ);

    //======================================
    // I - Type Operations
    //======================================

    //PRE:  @param uint regX and regY, range [0-15] inclusive
    //      @param uint num, holds uint to be added
    //POST: register[regX] = register[regY] + num
    void addi(uint regX, uint regY, uint num);

    //PRE:  @param uint regX and regY, range [0-15] inclusive
    //      @param uint num, holds the uint be be added to regY to solve
    //      location
    //POST: loads the content register[regY]+ address and stores it to
    //      register[regX]
    void lw(uint regX, uint regY, uint num);

    //PRE:  @param uint regX and regY, range [0-15] inclusive
    //      @param uint num, holds the uint be be added to regY to solve
    //      location
    //POST: stored the content of register[regX] to register[regY]+ address
    void sw(uint regX, uint regY, uint num);

    //PRE:  @param uint regX and regY, range [0-15] inclusive
    //      @param uint offset, holds the signed_value or offset
    //POST: if regX == regY offset added to PC else nothing
    void beq(uint regX, uint regY, uint offset);

    //PRE:  @param uint regX and regY, range [0-15] inclusive
    //      @param uint offset, holds the signed_value or offset
    //POST: if regX > regY offset added to PC else nothing
    void bgt(uint regX, uint regY, uint offset);

    //======================================
    // J - Type Operations
    //======================================

    //PRE:  @param uint regX and regY, range [0-15] inclusive
    //POST: set regX to be PC, set PC to be regY
    //throw(Exception((char *)"ERROR: JALR DOES NOT TAKE $sp,
    //                         PROCESS TERMINATED"));
    //if above error is hit the process is terminated
    void jalr(uint regX, uint regY);

    //======================================
    // U - Type Operations
    //======================================

    //PRE: @param uint regX, range [0-15] inclusive
    //PRE: @param uint num, the number to be entered to regX
    //POST: takes input from terminal, x and sets regX = x;
    void in(uint regX, uint num);

    //PRE:  @param uint regX, range [0-15] inclusive
    //POST: prints the content of regX to the terminal
    char * out(uint regX);

    //======================================
    // L - Type Operations
    //======================================

    //PRE:  @param uint regX, range [0-15] inclusive
    //      @param int num, holds the signed_value or offset
    //POST: prints the content of regX to the terminal
    void la(uint regX, int num);


    //======================================
    // O - Type Operations
    //======================================

    //PRE:  takes no params
    //POST: stops the program
    void halt();

    //PRE:  @param char * input gets the program name from the input
    //                    takes the input from the terminal
    //                    must be no longer than 2 words
    //                    must be a load command
    //POST: @returns a dynamicly created char* of the progam name + .lce
    char * getProgamName(char * input);

    //PRE: .lc_config must be in the same directory as the simulator
    //POST: reads the .lc_config from the current directory and sets the
    //      the setting in the machine to corresponding option in the config
    void importConfigFile();

    //PRE:  Taking a LList of MyString objects, the LList of the must be no more
    //      than 2 and the second token must be a given option for the lc2200 and
    //      the first must be a be a positive intager
    //POST: sets the option in the second node to the setting of the lc2200
    void setConfigOption(LList<MyString> tokens);

    //PRE: @param ifstream & inFile takes the correctly formated file with the
    //     length read from the file and the next thing to be read is the first
    //     byte of memorys
    //     @param uint start_address, the address to load the first word
    //     @param int length the length of the file
    //     assumes that the start till the length is allocated to the program
    //     assumes the inFile is open and it will be closes after this function
    //POST:reads the file into the address starting at start address and ending
    //     at the address (start + length)
    void importProgFile(ifstream & inFile, uint start_address, int length);

    //======================================
    // contex switching
    //======================================

    //PRE:  @param PCB * process, must be init
    //POST: cpu.registers, cpu.SP, cpu.PC now reflect their corresponding values
    //      in the PCB process given to the method
    void importRegistersPCBToCPU();

    //PRE:  @param PCB * process, must be init
    //POST: PCB.registers, PCB.SP, PCB.PC now reflect their corresponding values
    //      in the cpu
    void importRegistersCPUToPCB();

    //PRE:
    //POST: imports the registers of the cpu and pc, and sets the front to the back
    //      of the queue
    void setFrontToBackQueue();

    //======================================
    // current process
    //======================================


    //PRE:
    //POST: returns the first in the running_queue process if running_queue > 0
    //      else returns NULL
    PCB * getCurrentProcess();

  //======================================
  // freemem handling methods
  //======================================

  //PRE: @param, uint & prog_start, holds the location of the start of prog
  //      after return
  //     @param, uint & prog_end, holds the location of the end of prog after
  //             return
  //     @param, uint length, the length of the prog wanting to be added
  //     @param, uint & stack_start, holds the location of the start of stack
  //             after return
  //     @param, uint & stack_end, holds the location of the end of stack
  //             afterreturn
  //POST: uint & prog_start, uint & prog_end, uint & stack_start,
  //      uint & stack_end are only meanful if error is not thrown
  //throw(Exception((char *)"ERROR: OUT OF MEMORY"));
  void getProgamBounds(uint & prog_start, uint & prog_end,
                       uint length, uint & stack_start,
                       uint & stack_end);

 //PRE:  @param uint & start, holds the location of the start of prog after
 //      return
 //      @param uint & end,holds the location of the end of prog after return
 //      @param uint size the length of the prog wanting to be added to memory
 //      @param bool & error, tracks if an error occurs
 //POST: uint start, uint end are meaning fill iif there is not an error thrown
 void getMemLocations(uint & start, uint & end, uint size,
                               bool & error);

  //PRE: @param, uint & start, where the prog will start
  //     @param, uint & end,   where the prog will end
  //     @param, uint size,    the size of the program
  //POST: start and end will be meaning full and will indicate where the prog
  //      should go iff the program does not through an error. the method finds
  //      the first memory location the size will fit in
  void firstFit(uint & start, uint & end, uint size);

  //PRE: @param, uint & start, where the prog will start
  //     @param, uint & end,   where the prog will end
  //     @param, uint size,    the size of the program
  //POST: start and end will be meaning full and will indicate where the prog
  //      should go iff the program does not through an error. the method finds
  //      the best memory location the size will fit in
  void bestFit(uint & start, uint & end, uint size);

  //PRE: uint new_start, the new start of the freemem
  //     int free_mem_index, the freemem object that is being dealloacted
  //POST:if all the freemem is used it is delete, else it is made smallers
  void allocateMem(uint new_start, int free_mem_index);

  //PRE:  @param uint free_start, the
  //      @param uint free_end,
  //POST: adds the new memory that has been freed to the machine
  void deallocateMem(uint start, uint end);


  //PRE:  free mem is populated with size > 1
  //POST: freemem has to objects that are directl adj to each other meaning,
  //      mem 0 - 4 and 8 - 12 is added to gether to be to 0 - 12.
  void joinFreemem();

  //PRE: Assumes that the process at the begining of the queue has not
  //     been prepared on the cpu to run
  //POST:copys the registers and PC of the process and the start of the queue
  //     to the cpu
  void readyCurrentProcessOnCPU();

  //PRE:  @param char * input, takes the input from the terminal
  //                           must be no longer than 2 words
  //                           F
  //POST: loads the program into the memory location starting at 0
  //(Exception((char *)"ERROR: FILE FAILED TO OPEN"));
  void loadSim(char * input);

  //PRE:  @param char * input, takes the input to run
  //POST: @return char*, the content of memory
  //      if 1 token given, 0 - memory size
  //      if 2 tokens token[1] - memory size
  //      if 3 tokens token[1] - token[2]
  char * memSim(char * input);

  //PRE:  @param char * input, takes the input to run
  //POST: @returns a char* that is properly formated
  char * cpuSim();

  //PRE: @param int num_step, the number of lines to execute
  //     @param bool in, iif true the program needs input
  //     @param book out iif true the program needs output
  //     @param done iff the progam has reached the halt statemetn
  //POST:@return if out is true returns the output to the termainl
  //current_process = NULL throw(Exception((char *)"ERROR: NO PROGRAM
  //                                                LOADED"));
  char * stepSim(int num_steps, bool & in, bool & out, bool & done);

  //PRE: the Machine be running
  //POST: @returns the contents of the freemem llist from 0 - n
  char * freememSim();

  //PRE: the Machine be running
  //POST: @return char* the array that displays the jobs to the user
  char * jobsSim();

  //PRE:  @param char * input, takes the input to kill meaning two words
  //      separated by a ' ', the first being the str kill and the second
  //      being a positive intager that will reprent the PCB id that will be
  //      killed, ie kill <int>
  //      @param bool & out_bool, if there is not process found, will return not
  //      found
  //POST: kills the program and releases the memory back to freemem and removes
  //      the job from the runnin queue
  char * killSim(char * input, bool & out_bool);

  //PRE:  the machine be started
  //POST: returns the contents of the .lc_config to the terminal
  char * configSim();

  //PRE:  @param bool & in_bool, iif true the Machine needs input
  //      @param bool & out_bool, iif true the Machine is requesting to output
  //                              to the terminal
  //POST: @return iif out_bool is true is the return meaningful, the output
  //      reprents the output to send to the terminal
  char * executeLine(bool & in_bool, bool & out_bool);

  public:

    // Default Constructor
    // Pre :
    // Post: initlizes the Machine class
    Machine();


    //PRE:  the running_queue must have a process enqueue
    //POST: @return ID of the first process in the running queue
    uint getCurrentProcessID();


    //PRE:  @param char * input, the number
    //      @param bool & in_bool, is true iff the Machine needs input
    //      @param bool & out_bool, is true iff the Machine needs to output
    //      @param bool $ done, is true iff the Machine has hit the halt statement
    //      @param bool & post_i_o, tracks if the last command was i/o
    //      @param bool & current_process_done, tracks if the process at the
    //             front at the front of the queue is done
    //      @param bool & set_steps_made, if the steps made has been inited
    //POST: @return if out_bool is true return value is meaningful and is requesting
    //              for the terminal to output the return value
    char * runCommand(char * input, bool & in_bool, bool & out_bool,
                      bool & done, bool & post_i_o,
                      bool & current_process_done,
                      bool & set_steps_made);


    //PRE:  @param char * input, the number
    //      @param bool & in_bool, is true iff the Machine needs input
    //      @param bool & out_bool, is true iff the Machine needs to output
    //      @param bool $ done, is true iff the Machine has hit the halt
    //             statement
    //      @param bool & post_i_o, tracks if the last command was i/o
    //      @param bool & current_process_done, tracks if the process at the
    //             front at the front of the queue is done
    //      @param bool & set_steps_made, if the steps made has been inited
    //      @param uint num_slices, the number of slices given to the terminal
    //POST: @return if out_bool is true return value is meaningful and is
    //              requestingfor the terminal to output the return value,
    //              runs slice of the program, the slice is dependent on the
    //              config file
    char * sliceSim(char * input, bool & in_bool, bool & out_bool,
                    bool & done, bool & post_i_o,
                    bool & current_process_done,
                    bool & set_steps_made, uint num_slices);


    //======================================
    // INPUT
    //======================================

    //PRE:  @param char * input, takes the input to run
    //POST: @return char*, the content of memory
    //      if 1 token given, 0 - memory size
    //      if 2 tokens token[1] - memory size
    //      if 3 tokens token[1] - token[2]
    void giveInput(char * input);






    ~Machine();


};

#endif
