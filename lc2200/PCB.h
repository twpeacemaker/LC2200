#ifndef INCLUDED_PCB
#define INCLUDED_PCB
#include "constants.h"
#include "CPU.h"
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
    uint PC;

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

    //PRE:
    //POST: @return the value at the register[SP]
    uint getSP() const;

    //PRE:
    //POST: @return the value of PC
    uint getPC() const;

    //PRE:  @param int index, index of register [0-15] inclusive
    //POST: @return register[index]
    uint getRegister(uint index) const;


    //======================================
    // Setters
    //======================================

    //PRE: @param int value, the value you want register[index] to be
    //POST: register[index] = value
    //throw(Exception((char *)"ERROR: ZERO REGISTER CAN NOT BE CHANGED."));
    void setRegister(uint index, uint value);

    //PRE: @param int value, the value you want to be set to PC
    //POST: PC = value;
    void setPC(uint value);

    //PRE: @param int value, the value you want to be set to SP
    //POST: register[SP] = value
    void setSP(uint value);

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


    //PRE: @param uint p_start, program start address
    //     @param uint p_end, program end address
    //     @param uint s_start, stack start address
    //     @param uint s_end, stack end address
    //     @param uint SP, where the register SP will be set to
    //POST: program_start = p_start
    //      program_end = p_end
    //      stack_start = s_start
    //      stack_end = s_end
    //      registers[STACK_POINTER_INDEX] = stack_end;
    void initPCB(uint p_start, uint p_end, uint s_start, uint s_end, uint SP);

    //PRE:  @param uint PC, the relitive pc, assumes in bounds of the program
    //POST: @return, return_value gets the address from the machine and calculates
    //               the effective address of memory
    uint filterPC(uint PC);


    //PRE:
    //POST: deletes the dynamic memory
    ~PCB();
};
#endif
