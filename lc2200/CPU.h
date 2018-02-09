#ifndef INCLUDED_CPU
#define INCLUDED_CPU

#include "constants.h"
#include "Exception.h"
#include <iostream>
#include "useful_classes/MyString.h"
using namespace std;

#include <iostream>
using namespace std;

class CPU {

  // Class Invariant (CI): the obejct has a set of registers which register[0]
  // always have to be equal to 0 and which pc % 4 = 0 stack pointer must
  // be set to the correct address of memory when the process is loaded

 private:

      uint PC;
      uint registers[MAX_REGISTERS];

 public:

     // Constructor
     //PRE:
     //POST:
     CPU();

     //PRE:
     //POST: @return int PC, the value that PC contains
     uint getPC();

     //PRE:  @param uint new_PC, new_PC >= 0
     //POST: PC = new_PC
     void setPC(uint new_PC);

     //PRE:
     //POST: PC += PC + bytes in a word
     void incrementPC();

     //PRE:  @param int index, index of register [0-15] inclusive
     //POST: @return register[index]
     uint getRegister(uint index);

     //PRE:  @param int index, index of registers [0-15] inclusive
     //      @param int value, the value you want register[index] to be
     //POST: register[index] = value
     void setRegister(uint index, uint value);

     //PRE:
     //POST: @return the value at the register[SP]
     uint getSP();

     //PRE: @param int value, the value you want to be set to SP
     //POST: register[SP] = value
     void setSP(uint value);

     //PRE:  @param char * input, takes the input from the terminal
     //POST: @return the array to sent to the terminal to display
     char * getOutput();


     ~CPU();

};

#endif
