#include "constants.h"
#include "Memory.h"

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

// Destructor
// Pre :
// Post: releases all dynamic memory
Memory::~Memory() {
  if (memory != NULL) {
    delete [] memory;
  }
}
