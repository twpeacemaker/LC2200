#ifndef INCLUDED_MEMORY
#define INCLUDED_MEMORY
#include "constants.h"

class Memory {

  // Class Invariant (CI):

  private:

    unsigned int * memory;
    unsigned int   size;

  public:

    // Default Constructor
    // Pre :
    // Post: created an array of memory of size DEFAULT_MEM
    Memory();

    // Constructor
    // Pre : @param unsigned int memory_size, size of int, must be postitive
    // Post: created an array of memory of size n
    Memory(unsigned int memory_size);

    //PRE:  @param int index, index of memory
    //POST: @return memory[index]
    int getIndex(int index);

    //PRE:  @param int index, index of memory
    //      @param int word,  the word of memory to be inserted
    //POST: memory[index] = word
    void setIndex(int index, int word);

    //PRE:  @param char * input, takes the input from the terminal
    //      @param char * output, takes the output to be build up
    //POST: @return the array to sent to the terminal to display
    char * getOutput(char * input);

    //PRE: @param char * input, takes the input from the terminal
    //     @param int & lower_bound, is the lower requested by user
    //     @param int & upper_bound, is the upper requested by user
    //POST:
    void getUpperLowerBound(char * input, int & lower_bound, int & upper_bound);

    // Destructor
    // Pre :
    // Post: releases all dynamic memory
    ~Memory();

};

#endif
