#include "constants.h"
#include <iostream>
#include "CPU.h"
#include "useful_classes/MyString.h"
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
  PC += 1;
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


//PRE:
//POST: @return the array to sent to the terminal to display
char * CPU::getOutput() {
  MyString string;
  char * pc_line = new char [MAX_COL_CPU];
  sprintf (pc_line, " PC: %d \n", PC * BYTES_IN_WORD);
  string.addString(pc_line);
  delete [] pc_line;

  for (int i = 0; i < MAX_REGISTERS; i++) {
    char * col = new char [MAX_COL_CPU];
    sprintf (col, " %s: 0x%#08x (%d) ", REGISTER_NAMES[i], registers[i], registers[i]);
    string.addString(col);
    if((i + 1) % NUMBER_OF_COLS_IN_CPU == 0) {
      string.add('\n');
    }
    delete [] col;
  }
  return string.getStringDeepCopy(); // edit it be a deep
}

CPU::~CPU() {

}
