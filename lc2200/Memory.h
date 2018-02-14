#ifndef INCLUDED_MEMORY
#define INCLUDED_MEMORY

#include "constants.h"
#include "useful_classes/MyString.h"
#include "useful_functions/char_arrays.h"
#include "Exception.h"

class Memory {

  // Class Invariant (CI): facilitates the management of memory for the
  // machine this object must have a pointed to the assigned memory of the
  // terminal and a size that aligns the the size of mem. the memory expects
  // all addresses to multibles of 4 and returns the correct address of memory

  private:

    uint * memory;
    uint   size;

    //PRE: @param int index, takes the index of memory, index > 0 < size
    //POST: @return char* creates a string that represents the proper string
    //      to be printed as one column to the terminal ie '0: 0x00000000 0'
    char * getMemCommandCol(int index);

  public:

    // Default Constructor
    // Pre :
    // Post: created an array of memory of size DEFAULT_MEM
    Memory();

    // Constructor
    // Pre : @param uint memory_size, size of int, must be postitive
    // Post: created an array of memory of size n
    Memory(uint memory_size);

    //PRE:  @param int address, address of memory
    //POST: @return memory[address]
    uint getAddress(uint address) const;

    //PRE:  @param int index, address of memory
    //      @param int word,  the word of memory to be inserted
    //POST: memory[index] = word
    void setAddress(uint address, uint word);

    //PRE:  @param char * input, takes the input from the terminal, input should
    //      be formated as mem <uint1> <uint2> where both uints are optional,
    //      uint1 > uint2, uint2 < memory size, and uint1 > 0. uint1 and uint2
    //      must
    //      be a factor of 4. the uints represents inclusively the mem address
    //POST: @return the array to sent to the terminal to display, the output
    //      will be properly formated 4 rows of memory address at a time with
    //      the
    //      location of each address leading it. if uint1 and uint2 are not
    //      included
    //      all of mem is printed, if uint2 is not included output will be int1
    //      to
    //      mem_size. if uint1 and uint2 are included output will represent
    //      memory
    //      address from uint1 to uint2 inclusively
    char * getOutput(char * input);

    //PRE: @param char * input, takes the input from the terminal
    //     @param uint & lower_bound, is the lower requested by user
    //     @param uint & upper_bound, is the upper requested by user
    //POST:changes the upper and lower bound to correspond with the input
    //     request
    //throw(Exception((char *)"PARAMETERS ARE INCORRECT"));
    void getUpperLowerBound(char * input, uint & lower_bound,
                            uint & upper_bound);


    //PRE:
    //POST: @return, int the size of current memory
    int getSize() const;

    //PRE:
    //POST: @return, what the stack pointer should be initlized to
    int getLastAddress() const;

    // Destructor
    // Pre :
    // Post: releases all dynamic memory
    ~Memory();



};

#endif
