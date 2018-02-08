#ifndef INCLUDED_Machine
#define INCLUDED_Machine

#include "Machine.h"
#include "CPU.h"
#include "Memory.h"
#include "constants.h"
#include "Exception.h"
#include <stdio.h>
#include "PCB.h"

class Machine {

  // Class Invariant (CI):

  private:

    CPU cpu;
    Memory * memory;       // holds the pointer to memory
    PCB * current_process; // holds the information about the currently loaded
                           // program

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
    //      @param uint num, holds the uint be be added to regY to solve location
    //POST: loads the content register[regY]+ address and stores it to
    //      register[regX]
    void lw(uint regX, uint regY, uint num);

    //PRE:  @param uint regX and regY, range [0-15] inclusive
    //      @param uint num, holds the uint be be added to regY to solve location
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
    //      @param uint offset, holds the signed_value or offset
    //POST: prints the content of regX to the terminal
    void la(uint regX, uint offset);

    //======================================
    // O - Type Operations
    //======================================

    //PRE:  takes no params
    //POST: stops the program
    void halt();

    //PRE:  @param char * input gets thr program name from the input
    //POST: @returns a dynamicly created char* of the progam name
    char * getProgamName(char * input);


  public:

    // Default Constructor
    // Pre :
    // Post: initlizes the Machine class
    Machine();

    // Pre : @param uint memory_size inits the size of memory
    // Post: initlizes the Machine class
    Machine(uint memory_size);

    //PRE:
    //POST: @return iif out_bool is true is the return meaningful
    char * executeLine(bool & in_bool, bool & out_bool);

    //PRE:  @param char * input, the number
    //POST:
    char * runCommand(char * input, bool & in_bool, bool & out_bool, bool & done);

    //======================================
    // INPUT
    //======================================

    //PRE:  @param char * input, should be valid to be entered to a register at the
    //      current line
    //POST: sets the register specifed in the current line to the input taken
    void giveInput(char * input);

    //PRE:  @param char * input, takes the input from the terminal
    //                           must be no longer than 2 words
    //POST: loads the program into the memory location starting at 0
    void loadSim(char * input);

    //PRE:  @param char * input, takes the input to run
    //POST: @print the content of memory
    //      if 1 token given, 0 - memory size is printed
    //      if 2 tokens token[1] - memory size is printed
    //      if 3 tokens token[1] - token[2] is printed
    char * memSim(char * input);

    //PRE:  @param char * input, takes the input to run
    //POST: @returns a char* that is properly formated
    char * cpuSim();

    //PRE:
    //POST:
    char * stepSim(int num_steps, bool & in, bool & out, bool & done);

    //PRE:
    //POST:
    void runSim();


};

#endif
