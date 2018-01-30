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
  memory = new unsigned int[DEFAULT_MEM];
  size   = DEFAULT_MEM;
}

// Constructor
// Pre : @param unsigned int memory_size, size of int, must be postitive and %4
// Post: created an array of memory of size n
Memory::Memory(unsigned int memory_size) {
    memory = new unsigned int[memory_size];
    size   = memory_size;
}

//PRE:  @param int index, index of memory
//POST: @return memory[index]
int Memory::getIndex(int index) {
  return memory[index];

}

//PRE:  @param int index, index of memory
//      @param int word,  the word of memory to be inserted
//POST: memory[index] = word
void Memory::setIndex(int index, int word) {
  memory[index] = word;
}

//PRE:  @param char * input, takes the input from the terminal
//      @param char * output, takes the output to be build up
//POST: @return the array to sent to the terminal to display
char * Memory::getOutput(char * input) {
  //removes the command from the list
  int lower_bound = 0;
  int upper_bound = size;
  getUpperLowerBound(input, lower_bound, upper_bound); // all are validated
  MyString string;
  char * temp;
  for (int i = lower_bound; i <= upper_bound; i = i + NUMBER_OF_COLS_IN_MEM) {
    if (i <= upper_bound) {
      temp = getMemCommandCol(i);
      string.addString(temp);
      delete [] temp;
      temp = NULL;
    } if (i + COL_ONE_MEM <= upper_bound) {
      temp = getMemCommandCol(i + COL_ONE_MEM);
      string.addString(temp);
      delete [] temp;
      temp = NULL;
    } if (i + COL_TWO_MEM <= upper_bound) {
      temp = getMemCommandCol(i + COL_TWO_MEM);
      string.addString(temp);
      delete [] temp;
      temp = NULL;
    } if (i + COL_THREE_MEM <= upper_bound) {
      temp = getMemCommandCol(i + COL_THREE_MEM);
      string.addString(temp);
      delete [] temp;
      temp = NULL;
    }
    string.add('\n'); // adds the new line character
  }
  return string.getStringDeepCopy();
}

//PRE: @param int index, takes the index of memory
//POST:@return char* creates appropriate string to add to the cols
char * Memory::getMemCommandCol(int index) {
  char * temp = new char[MAX_COL_MEM];
  sprintf (temp, " %d: 0x%#08x %d ", index * BYTES_IN_WORD, memory[index], memory[index]);
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
    //first token to the end of memory
    if ( lower_bound >= (size * BYTES_IN_WORD) ) {
      throw(Exception((char *)"LOWER BOUND IS GREATER THAN SIZE"));
    } else if (lower_bound % 4 != 0) {
      throw(Exception((char *)"LOWER BOUND IS NOT A FACTOR OF 4"));
    } else if (lower_bound < 0) {
      throw(Exception((char *)"LOWER BOUND IS MUST BE GREATER THAN 0"));
    } else {
      lower_bound = array_to_int(tokens.getFront().getString()) / BYTES_IN_WORD;
    }
  } else if(tokens.getSize() > 1) {
    if (lower_bound >= (size * BYTES_IN_WORD)||upper_bound >= BYTES_IN_WORD) {
      throw(Exception((char *)"PARAMETER IS GREATER THAN SIZE"));
    } else if (lower_bound > upper_bound) {
      throw(Exception((char *)"LOWER BOUND IS GREATER THAN SIZE"));
    } else if(0 > lower_bound) {
      throw(Exception((char *)"LOWER BOUND IS LESS THAN 0"));
    } else if (upper_bound % 4 != 0) {
      throw(Exception((char *)"LOWER BOUND IS NOT A FACTOR OF 4"));
    } else if (lower_bound % 4 != 0) {
      throw(Exception((char *)"UPPER BOUND IS NOT A FACTOR OF 4"));
    } else {
      lower_bound = array_to_int(tokens.getFront().getString()) / BYTES_IN_WORD;
      upper_bound = array_to_int(tokens.getBack().getString())  / BYTES_IN_WORD;
    }
  }
}

// Destructor
// Pre :
// Post: releases all dynamic memory
Memory::~Memory() {
  if (memory != NULL) {
    delete [] memory;
  }
}
