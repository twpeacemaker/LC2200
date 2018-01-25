#include "Simulator.h"
#include "CPU.h"
#include "constants.h"

#include "useful_functions/bit_manipulation.cc"

// Default Constructor
// Pre :
// Post: initlizes the Simulator class
Simulator::Simulator() {

}

//PRE:  @param int line, is the line to be executed
//POST:
void Simulator::executeLine(int line) {
  //printf("Execute Line: %#08x \n", line);
  int opcode = getOpcode(line);
  switch(opcode) {
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
      in( getRegX(line) );
      break;
    case OUT:
      out( getRegX(line) );
      break;
    case LA:
      la( getRegX(line), getSignedOrOffset(line));
      break;
    case BGT:
      bgt( getRegX(line), getRegY(line), getSignedOrOffset(line) );
      break;
    default:
      cerr << "default \n";
      break;
  }
}

//======================================
// Word Getters
//======================================

//PRE:  @param int line, is the line to be executed, lenth = 4 bytes
//POST: @return int opcode from the line is executed
int Simulator::getOpcode(int line){
  return getBits(line, OPCODE_UPPER_BIT, OPCODE_LOWER_BIT);
}

//PRE:  @param int line, is the line to be executed, lenth = 4 bytes
//POST: @return int regX from the line is executed
int Simulator::getRegX(int line) {
  return getBits(line, REGX_UPPER_BIT, REGX_LOWER_BIT);
}

//PRE:  @param int line, is the line to be executed, lenth = 4 bytes
//POST: @return int regY from the line is executed
int Simulator::getRegY(int line) {
  return getBits(line, REGY_UPPER_BIT, REGY_LOWER_BIT);
}

//PRE:  @param int line, is the line to be executed, lenth = 4 bytes
//POST: @return int regZ from the line is executed
int Simulator::getRegZ(int line) {
  return getBits(line, REGZ_UPPER_BIT, REGZ_LOWER_BIT);
}

//PRE:  @param int line, is the line to be executed, lenth = 4 bytes
//POST: @return int Signed Value or Offset from the line is executed
int Simulator::getSignedOrOffset(int line) {
  return getBits(line, SIGNED_OR_OFFSET_UPPER_BIT, SIGNED_OR_OFFSET_LOWER_BIT);
}

//======================================
// R - Type Operations
//======================================

//PRE:  @param int regX, regY, and regZ, range [0-15] inclusive
//POST: register[regX] will reflect the sum of register[regY] and
//      register[regY]
void Simulator::add(int regX, int regY, int regZ) {
  int sum = cpu.getRegister(regY) + cpu.getRegister(regZ);
  cpu.setRegister(regX, sum);

    //printf("regX(%d) = regY(%d) + regZ(%d)  \n", regX, regY, regZ);
}

//PRE:  @param int regX, regY, and regZ, range [0-15] inclusive
//POST: register[regX] will reflect the ~and of register[regY] and
//      register[regY]
void Simulator::nand(int regX, int regY, int regZ) {
  int not_and = ~( cpu.getRegister(regY) & cpu.getRegister(regZ) );
  cpu.setRegister(regX, not_and);
}

//======================================
// I - Type Operations
//======================================

//PRE:  @param int regX and regY, range [0-15] inclusive
//      @param int num, holds int to be added
//POST: register[regX] = register[regY] + num
void Simulator::addi(int regX, int regY, int num) {
  int sum = cpu.getRegister(regY) + num;
  cpu.setRegister(regX, sum);
}

//PRE:  @param int regX and regY, range [0-15] inclusive
//      @param int num, holds the int be be added to regY to solve location
//POST: loads the content register[regY]+ address and stores it to
//      register[regX]
void Simulator::lw(int regX, int regY, int num) {

}

//PRE:  @param int regX and regY, range [0-15] inclusive
//      @param int num, holds the int be be added to regY to solve location
//POST: stored the content of register[regX] to register[regY]+ address
void Simulator::sw(int regX, int regY, int num) {

}

//PRE:  @param int regX and regY, range [0-15] inclusive
//      @param int offset, holds the signed_value or offset
//POST: if regX == regY offset added to PC else nothing
void Simulator::beq(int regX, int regY, int offset) {

}

//PRE:  @param int regX and regY, range [0-15] inclusive
//      @param int offset, holds the signed_value or offset
//POST: if regX > regY offset added to PC else nothing
void Simulator::bgt(int regX, int regY, int offset) {

}

//======================================
// J - Type Operations
//======================================

//PRE:  @param int regX and regY, range [0-15] inclusive
//POST: set regX to be PC, set PC to be regY
void Simulator::jalr(int regX, int regY) {

}

//======================================
// U - Type Operations
//======================================

//PRE:  @param int regX, range [0-15] inclusive
//POST: takes input from terminal, x and sets regX = x;
void Simulator::in(int regX) {

}

//PRE:  @param int regX, range [0-15] inclusive
//POST: prints the content of regX to the terminal
void Simulator::out(int regX) {

}

//======================================
// L - Type Operations
//======================================

//PRE:  @param int regX, range [0-15] inclusive
//      @param int offset, holds the signed_value or offset
//POST: prints the content of regX to the terminal
void Simulator::la(int regX, int offset) {

}

//======================================
// O - Type Operations
//======================================

//PRE:  takes no params
//POST: stops the program
void Simulator::halt() {

}
