#ifndef INCLUDED_PCB
#define INCLUDED_PCB
#include "constants.h"
#include <stdio.h>

class PCB {
  private:

    char * name;        //holds the name of the progame
    uint steps;           //holds the number of steps conducted on pass
    bool halted;

    //holds the length of the program
    uint program_length;
    //progame address
    uint program_start;
    uint program_end;
    //stack
    uint stack_start;
    uint stack_end;
    uint registers[MAX_REGISTERS];
    uint id;

  public:

    //Constructor
    //PRE:  @param char * name, the name of the program
    //      @param int id, the unique id that is given to the PCB
    //      @param uint given_length, the length of the progam
    //POST: creates the object
    PCB(char * given_name, int p_id, uint length);

    //======================================
    // Getters
    //======================================

    //PRE:
    //POST: @return, uint program_length
    uint getLength() const;

    //PRE:
    //POST: @return, int steps
    uint getSteps() const;

    //PRE:
    //POST: @return, whether the program is halted or not
    bool getHalt() const;

    //PRE:
    //POST: returns the name of the progam as a char*
    char * getName() const;

    //PRE:
    //POST: @return uint id;
    uint getID() const;

    //PRE:
    //POST: @return, program_start
    uint getProgStartAddress();

    //PRE:
    //POST: @return, program_end
    uint getProgEndAddress();

    //PRE:
    //POST: @return, stack_start
    uint getStackStartAddress();

    //PRE:
    //POST: @return, stack_end
    uint getStackEndAddress();


    //======================================
    // Setters
    //======================================

    //PRE:  int n, the length of the program
    //POST: sets lenth = n;
    void setLength(uint n);

    //PRE:
    //POST: increments the steps by 1
    void incrementSteps();

    //PRE:
    //POST: sets steps to 0
    void resetSteps();

    //PRE:  @param int n, the number to to set to steps
    //POST: sets steps = n
    void setSteps(uint n);

    //PRE:  @param char * name, takes the array to set to the new name
    //POST: sets name = new_name
    void setName(char * new_name);

    //PRE:
    //POST: sets the program to be halted
    void haltProgram();

    //PRE:  int num_steps, the number of steps the user wanted to run the
    //      program
    //POST: @return whether the program is able to run
    bool ableToRun(int num_steps);


    //PRE: uint p_start, program start address
    //     uint p_end, program end address
    //     uint s_start, stack start address
    //     uint s_end, stack end address
    //POST: program_start = p_start
    //      program_end = p_end
    //      stack_start = s_start
    //      stack_end = s_end
    void initPCB(uint p_start, uint p_end, uint s_start, uint s_end);


    //PRE:
    //POST: deletes the dynamic memory
    ~PCB();
};
#endif
