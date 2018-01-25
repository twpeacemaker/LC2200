#ifndef INCLUDED_CPU
#define INCLUDED_CPU

#include "constants.h"

#include <iostream>
using namespace std;

class CPU {
  // Class Invariant (CI):

 private:

      int PC;
      int registers[MAX_REGISTERS];

 public:

     // Constructor
     //PRE:
     //POST:
     CPU();

     //PRE:
     //POST: @return int PC, the value that PC contains
     int getPC();

     //PRE:  @param unsigned int new_PC, new_PC >= 0
     //POST: PC = new_PC
     void setPC(unsigned int new_PC);

     //PRE:
     //POST: PC += PC + bytes in a word
     void incrementPC();

     //PRE:  @param int index, index of register [0-15] inclusive
     //POST: @return register[index]
     int getRegister(int index);

     //PRE:  @param int index, index of registers [0-15] inclusive
     //      @param int value, the value you want register[index] to be
     //POST: register[index] = value
     void setRegister(int index, int value);

     //PRE:
     //POST: @return the value at the register[SP]
     int getSP();

     //PRE: @param int value, the value you want to be set to SP
     //POST: register[SP] = value
     void setSP(int value);


     ~CPU();

};

#endif
