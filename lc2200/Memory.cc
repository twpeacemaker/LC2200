#include "constants.h"
#include "Memory.h"
#include "useful_classes/MyString.h"
#include "useful_functions/char_arrays.h"
#include "Exception.h"


#include <iostream>
using namespace std;

// Default Constructor
// Pre :
// Post: created an array of memory of size DEFAULT_MEM,
Memory::Memory() {
  memory = new uint[DEFAULT_MEM];
  size   = DEFAULT_MEM;
}

// Constructor
// Pre : @param uint memory_size, size of int, must be postitive and %4
// Post: created an array of memory of size n
Memory::Memory(uint memory_size) {
    memory = new uint[memory_size];
    size   = memory_size;
}

//PRE:  @param int index, index of memory
//POST: @return memory[index]
int Memory::getIndex(int index) {
  return memory[index / BYTES_IN_WORD];
}

//PRE:  @param int index, index of memory
//      @param int word,  the word of memory to be inserted
//POST: memory[index] = word
void Memory::setIndex(int index, int word) {
  memory[index / BYTES_IN_WORD] = word;
}

//PRE:  @param char * input, takes the input from the terminal
//      @param char * output, takes the output to be build up
//POST: @return the array to sent to the terminal to display
char * Memory::getOutput(char * input) {
  //removes the command from the list
  int lower_bound = 0;
  int upper_bound = (size - 1) * BYTES_IN_WORD;
  getUpperLowerBound(input, lower_bound, upper_bound); // all are validated
  MyString string;                                     // string to be created
  char * temp;
  for (int i = (lower_bound / BYTES_IN_WORD); i <= (upper_bound / BYTES_IN_WORD); i++) {
    temp = getMemCommandCol(i);
    string.addString(temp);
    delete [] temp;
    if((i + 1) % NUMBER_OF_COLS_IN_MEM == 0 || i == (upper_bound / BYTES_IN_WORD)) {
      string.add('\n');
    }
  }
  return string.getStringDeepCopy();
}

//PRE: @param int index, takes the index of memory
//POST:@return char* creates appropriate string to add to the cols
char * Memory::getMemCommandCol(int index) {
  char * temp = new char[MAX_COL_MEM];
  sprintf (temp, " %d: 0x%08X %d ", index * BYTES_IN_WORD, memory[index], memory[index]);
  return temp;
}

//PRE: @param char * input, takes the input from the terminal
//     @param int & lower_bound, is the lower requested by user
//     @param int & upper_bound, is the upper requested by user
//POST:
void Memory::getUpperLowerBound(char * input, int & lower_bound, int & upper_bound) {
  MyString string = input;
  LList<MyString> tokens = string.split(' '); //splits the string at ' '
  tokens.deleteFront();
  //ASSERT: tokens size is no more than 2
  if (tokens.getSize() == 1) {
    //3
    //first token to the end of memory
    lower_bound = array_to_int(tokens.getFront().getString());
    if (lower_bound >= (size * BYTES_IN_WORD) ||
        lower_bound % 4 != 0 ||
        lower_bound < 0) {
      throw(Exception((char *)"PARAMETERS ARE INCORRECT"));
    }


  } else if(tokens.getSize() > 1) {
      lower_bound = array_to_int(tokens.getFront().getString());
      upper_bound = array_to_int(tokens.getBack().getString());
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
int Memory::getSize() {
  return size;
}

//PRE:
//POST: @return, what the stack pointer should be initlized to
int Memory::getLastAddress() {
  return (size - 1) * BYTES_IN_WORD;
}



// Destructor
// Pre :
// Post: releases all dynamic memory
Memory::~Memory() {
  if (memory != NULL) {
    delete [] memory;
  }
}
