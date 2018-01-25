#ifndef INCLUDED_SIMULATOR
#define INCLUDED_SIMULATOR

#include "CPU.h"
#include "constants.h"

class Simulator {

  // Class Invariant (CI):

  private:

    CPU cpu;

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

    //PRE:  @param int regX, range [0-15] inclusive
    //POST: takes input from terminal, x and sets regX = x;
    void in(int regX);

    //PRE:  @param int regX, range [0-15] inclusive
    //POST: prints the content of regX to the terminal
    void out(int regX);

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

    //PRE:  @param int line, is the line to be executed
    //POST:
    void executeLine(int line);

    // //PRE:
    // //POST:
    // void load();
    //
    // //PRE:
    // //POST:
    // void cpu();
    //
    // //PRE:
    // //POST:
    // void step();
    //
    // //PRE:
    // //POST:
    // void run();
    //
    // //PRE:
    // //POST:
    // void exit();

};

#endif
