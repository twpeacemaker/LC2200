#ifndef INCLUDED_PCB
#define INCLUDED_PCB
#include "constants.h"
#include "CPU.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

#include "useful_classes/LList.h"
#include "PageInfo.h"


class PCB {

  // Class Invariant (CI): the name will be the name of the file that was loaded
  // and will always be given a value, steps will track the number of steps
  // in the current session of steps. halted will only be true if the
  // program has reached the halt statement. the program lenth > 0 and will
  // represent the amount of lines in the process. program_start, program_end,
  // stack_start, and stack_end will all hold the physical address of mem
  // that the prog starts and ends and where the stack starts and ends. prog
  // start will be > 0 and < prog end. prog end will not be greater than
  // the amount of memory. stack start < end and < 0. stack end will not be
  // < amount of memory. registers[MAX_REGISTERS] will store the registers
  // for the program $zero will always remain 0 and $sp will hold the relitive
  // address not the physical, id will be unqiue and not used by any other
  // proccess, PC will hold the relitive PC of when the program end its least
  // pass as the current process. for each page info in page_table, it is
  // also in the machines page table, and for each pageinfo in machine it is
  // also in pagetable

  private:

    char * name;
    uint steps;
    bool halted;


    uint program_length;
    uint registers[MAX_REGISTERS];
    uint id;
    uint PC;

    fstream * file_stream;
    uint program_stream_start;

    LList<PageInfo*> page_table;

  public:

    //Constructor
    //PRE:  @param char * name, the name of the program
    //      @param int id, the unique id that is given to the PCB
    //      @param uint given_length, the length of the progam
    //      @param fstream & stream, the file stream of the object
    //      @param uint prog_stream_start, tracks where the prog starts
    //
    //POST: creates the object
    PCB(char * given_name, int p_id, uint length, uint prog_stream_start);

    //PRE:  @param PageInfo * page, the page to be added to the pagetable
    //POST: adds the page to the page table
    void addPage(PageInfo * page);

    //======================================
    // Getters
    //======================================


    //PRE:
    //POST: @return, uint program_stream_start
    uint getStreamStart() const;

    //PRE:
    //POST: @return, uint program_length
    uint getLength() const;

    //PRE:
    //POST: @return, int steps
    uint getSteps() const;

    //PRE:
    //POST: returns fstream & file_stream
    fstream * getStream();

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

    //PRE: @param uint SP, where the register SP will be set to
    //POST: registers[STACK_POINTER_INDEX] = stack_end;
    void initPCB(uint SP);

    //PRE:  @param uint PC, the relitive pc, assumes in bounds of the program
    //      @param uint page_size, the size of the page
    //      @param uint stack_size, the size of stack
    //POST: @return, return_value gets the address from the machine and calculates
    //               the effective address of memory
    uint filterPC(uint PC, uint page_size, uint stack_size);

    friend ostream & operator <<(ostream & str, const PCB * M);


    //PRE:
    //POST: deletes the dynamic memory
    ~PCB();
};
#endif
