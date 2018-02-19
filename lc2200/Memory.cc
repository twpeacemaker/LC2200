#include "Memory.h"
#include "constants.h"
#include "useful_classes/MyString.h"
#include "useful_functions/char_arrays.h"
#include "Exception.h"


#include <iostream>
using namespace std;



// Constructor
// Pre : @param uint memory_size, size of int, must be postitive and %4
// Post: created an array of memory of size n
Memory::Memory(uint memory_size) {
    memory = new uint[memory_size];
    size   = memory_size;
}

//PRE:  @param uint address, address of memory
//POST: @return memory[address]
uint Memory::getAddress(uint address) const {
  return memory[address / BYTES_IN_WORD];
}

//PRE:  @param uint index, address of memory
//      @param uint word,  the word of memory to be inserted
//POST: memory[index] = word
void Memory::setAddress(uint address, uint word) {
  memory[address / BYTES_IN_WORD] = word;
}

//PRE:  @param char * input, takes the input from the terminal, input should
//      be formated as mem <uint1> <uint2> where both uints are optional,
//      uint1 > uint2, uint2 < memory size, and uint1 > 0. uint1 and uint2 must
//      be a factor of 4. the uints represents inclusively the mem address
//POST: @return the array to sent to the terminal to display, the output
//      will be properly formated 4 rows of memory address at a time with the
//      location of each address leading it. if uint1 and uint2 are not included
//      all of mem is printed, if uint2 is not included output will be int1 to
//      mem_size. if uint1 and uint2 are included output will represent memory
//      address from uint1 to uint2 inclusively
char * Memory::getOutput(char * input) {
  //removes the command from the list
  uint lower_bound = 0;
  uint upper_bound = (size - 1) * BYTES_IN_WORD;
  getUpperLowerBound(input, lower_bound, upper_bound); // all are validated
  MyString string;                                     // string to be created
  char * temp;
  for (int i = (lower_bound / BYTES_IN_WORD);
       i <= (upper_bound / BYTES_IN_WORD); i++) {
    temp = getMemCommandCol(i);
    string.addString(temp);
    delete [] temp;
    if((i + 1) % NUMBER_OF_COLS_IN_MEM == 0 ||
       i == (upper_bound / BYTES_IN_WORD)) {
      string.add('\n');
    }
  }
  return string.getStringDeepCopy();
}

//PRE: @param int index, takes the index of memory, index > 0 < size
//POST: @return char* creates a string that represents the proper string
//      to be printed as one column to the terminal ie 0: 0x00000000 0
char * Memory::getMemCommandCol(int index) {
  char * temp = new char[MAX_COL_MEM];
  sprintf (temp, " %d: 0x%08X %d ", index * BYTES_IN_WORD, memory[index],
           memory[index]);
  return temp;
}

//PRE: @param char * input, takes the input from the terminal
//     @param uint & lower_bound, is the lower requested by user
//     @param uint & upper_bound, is the upper requested by user
//POST:changes the upper and lower bound to correspond with the input request
//throw(Exception((char *)"PARAMETERS ARE INCORRECT"));
void Memory::getUpperLowerBound(char * input, uint & lower_bound,
                                uint & upper_bound) {
  MyString string = input;
  LList<MyString> tokens = string.split(' '); //splits the string at ' '
  tokens.deleteFront();
  //ASSERT: tokens size is no more than 2
  if (tokens.getSize() == 1) {
    //first token to the end of memory
    lower_bound = arrayToInt(tokens.getFront().getString());
    if (lower_bound >= (size * BYTES_IN_WORD) || lower_bound % 4 != 0 ||
        lower_bound < 0) {
      throw(Exception((char *)"PARAMETERS ARE INCORRECT"));
    }
  } else if(tokens.getSize() > 1) {
      lower_bound = arrayToInt(tokens.getFront().getString());
      upper_bound = arrayToInt(tokens.getBack().getString());
      if (lower_bound >= (size * BYTES_IN_WORD) ||
          upper_bound >= (size * BYTES_IN_WORD) ||
          lower_bound % 4 != 0 ||
          upper_bound % 4 != 0 ||
          lower_bound < 0 ||
          lower_bound > upper_bound) {
        throw(Exception((char *)"PARAMETERS ARE INCORRECT"));
      }
    }
}

//PRE:
//POST: @return, the size of current memory
int Memory::getSize() const{
  return size;
}

//PRE:
//POST: @return, what the stack pointer should be initlized to
int Memory::getLastAddress() const {
  return (size - 1) * BYTES_IN_WORD;
}



// Destructor
// Pre :
// Post: releases all dynamic memory
Memory::~Memory() {
  if (memory != NULL) {
    delete [] memory;
    memory = NULL;
  }
}
