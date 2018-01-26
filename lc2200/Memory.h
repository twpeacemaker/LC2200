#ifndef INCLUDED_MEMORY
#define INCLUDED_MEMORY

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

};

#endif
