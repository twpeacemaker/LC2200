#ifndef INCLUDED_SIMULATOR
#define INCLUDED_SIMULATOR

#include "Simulator.h"
#include "CPU.h"
#include "Memory.h"
#include "constants.h"
#include "Exception.h"
#include <stdio.h>
#include "PCB.h"

class Simulator {

  // Class Invariant (CI):

  private:

    CPU cpu;
    Memory * memory;       // holds the pointer to memory
    PCB * current_process; // holds the information about the currently loaded
                           // program

    //======================================
    // Word Getters
    //======================================

    //PRE:  @param int line, is the line to be executed, lenth = 4 bytes
    //POST: @return int opcode from the line is executed
    int getOpcode(int line);

    //PRE:  @param int line, is the line to be executed, lenth = 4 bytes
    //POST: @return int regX from the line is executed
    int getRegX(int line);

    //PRE:  @param int line, is the line to be executed, lenth = 4 bytes
    //POST: @return int regY from the line is executed
    int getRegY(int line);

    //PRE:  @param int line, is the line to be executed, lenth = 4 bytes
    //POST: @return int regZ from the line is executed
    int getRegZ(int line);

    //PRE:  @param int line, is the line to be executed, lenth = 4 bytes
    //POST: @return int Signed Value or Offset from the line is executed
    int getSignedOrOffset(int line);

    //PRE:
    //POST: @returns the current progame line
    int getCurrentLine();

    //PRE:
    //POST: @returns the previous progame line
    int getPrevLine();

    //======================================
    // R - Type Operations
    //======================================

    //PRE:  @param int regX, regY, and regZ, range [0-15] inclusive
    //POST: register[regX] will reflect the sum of register[regY] and
    //      register[regY]
    void add(int regX, int regY, int regZ);

    //PRE:  @param int regX, regY, and regZ, range [0-15] inclusive
    //POST: register[regX] will reflect the ~and of register[regY] and
    //      register[regY]
    void nand(int regX, int regY, int regZ);

    //======================================
    // I - Type Operations
    //======================================

    //PRE:  @param int regX and regY, range [0-15] inclusive
    //      @param int num, holds int to be added
    //POST: register[regX] = register[regY] + num
    void addi(int regX, int regY, int num);

    //PRE:  @param int regX and regY, range [0-15] inclusive
    //      @param int num, holds the int be be added to regY to solve location
    //POST: loads the content register[regY]+ address and stores it to
    //      register[regX]
    void lw(int regX, int regY, int num);

    //PRE:  @param int regX and regY, range [0-15] inclusive
    //      @param int num, holds the int be be added to regY to solve location
    //POST: stored the content of register[regX] to register[regY]+ address
    void sw(int regX, int regY, int num);

    //PRE:  @param int regX and regY, range [0-15] inclusive
    //      @param int offset, holds the signed_value or offset
    //POST: if regX == regY offset added to PC else nothing
    void beq(int regX, int regY, int offset);

    //PRE:  @param int regX and regY, range [0-15] inclusive
    //      @param int offset, holds the signed_value or offset
    //POST: if regX > regY offset added to PC else nothing
    void bgt(int regX, int regY, int offset);

    //======================================
    // J - Type Operations
    //======================================

    //PRE:  @param int regX and regY, range [0-15] inclusive
    //POST: set regX to be PC, set PC to be regY
    void jalr(int regX, int regY);

    //======================================
    // U - Type Operations
    //======================================

    //PRE: @param int regX, range [0-15] inclusive
    //PRE: @param int num, the number to be entered to regX
    //POST: takes input from terminal, x and sets regX = x;
    void in(int regX, int num);

    //PRE:  @param int regX, range [0-15] inclusive
    //POST: prints the content of regX to the terminal
    void out(int regX, char output[]);

    //======================================
    // L - Type Operations
    //======================================

    //PRE:  @param int regX, range [0-15] inclusive
    //      @param int offset, holds the signed_value or offset
    //POST: prints the content of regX to the terminal
    void la(int regX, int offset);

    //======================================
    // O - Type Operations
    //======================================

    //PRE:  takes no params
    //POST: stops the program
    void halt();



  public:

    // Default Constructor
    // Pre :
    // Post: initlizes the Simulator class
    Simulator();

    // Pre : @param uint memory_size inits the size of memory
    // Post: initlizes the Simulator class
    Simulator(uint memory_size);

    //PRE:
    //POST:
    void executeLine(bool & in, bool & out, char output[]);

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
    void stepSim(int & num_steps, bool & in, bool & out, bool & done, char output[]);

    //PRE:
    //POST:
    void runSim();


};

#endif
