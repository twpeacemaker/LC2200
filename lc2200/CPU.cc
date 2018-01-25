#include "constants.h"
#include <iostream>
#include "CPU.h"
using namespace std;


// Constructor
//PRE:
//POST:
CPU::CPU() {
  registers[0] = 0;
  PC = 0;
}

//PRE:
//POST: @return int PC, the value that PC contains
int CPU::getPC() {
  return PC;
}

//PRE:  @param unsigned int new_PC, new_PC >= 0
//POST: PC = new_PC
void CPU::setPC(unsigned int new_PC) {
  PC = new_PC;
}

//PRE:
//POST: PC += PC + bytes in a word
void CPU::incrementPC() {
  PC += BYTES_IN_WORD;
}

//PRE:  @param int index, index of register [0-15] inclusive
//POST: @return register[index]
int CPU::getRegister(int index) {
  return registers[index];
}

//PRE:  @param int index, index of registers [0-15] inclusive
//      @param int value, the value you want register[index] to be
//POST: register[index] = value
void CPU::setRegister(int index, int value) {
  registers[index] = value;
}

//PRE:
//POST: @return the value at the register[SP]
int CPU::getSP() {
  return registers[STACK_POINTER_INDEX];
}

//PRE: @param int value, the value you want to be set to SP
//POST: register[SP] = value
void CPU::setSP(int value) {
  registers[STACK_POINTER_INDEX] = value;
}

CPU::~CPU() {

}
