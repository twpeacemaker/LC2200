#include "PCB.h"
#include "constants.h"
#include <stdio.h>


//Constructor
//PRE:  @param char * name, the name of the program
//      @param int id, the unique id that is given to the PCB
//      @param uint given_length, the length of the progam
//POST: creates the object
PCB::PCB(char * given_name, int p_id, uint length) {
  name = given_name;
  program_length = length;
  steps = 0;
  halted = false;
  id = p_id;
}

//======================================
// Getters
//======================================

//PRE:
//POST: @return, uint program_length
uint PCB::getLength() const {return program_length;}


//PRE:
//POST: @return, int steps
uint PCB::getSteps() const {return steps;}


//PRE:
//POST: returns the name of the progam as a char*
char * PCB::getName() const {return name;}

//PRE:
//POST: @return, whether the program is halted or not
bool PCB::getHalt() const {return halted;}

//PRE:
//POST: @return uint id;
uint PCB::getID() const {return id;}

//======================================
// Setters
//======================================

//PRE:  int n, the length of the program
//POST: sets lenth = n;
void PCB::setLength(uint n) {program_length = n;}

//PRE:
//POST: increments the steps by 1
void PCB::incrementSteps() {steps++;}

//PRE:
//POST: sets steps to 0
void PCB::resetSteps() {steps = 0;}

//PRE:  @param int n, the number to to set to steps
//POST: sets steps = n
void PCB::setSteps(uint n) {steps = n;}

//PRE:  @param char * name, takes the array to set to the new name
//POST: sets name = new_name
void PCB::setName(char * new_name) {name = new_name;}

//PRE:
//POST: sets the program to be halted
void PCB::haltProgram() {halted = true;}

//PRE:
//POST: @return, program_start
uint PCB::getProgStartAddress() {return program_start;}

//PRE:
//POST: @return, program_end
uint PCB::getProgEndAddress() {return program_end;}

//PRE:
//POST: @return, stack_start
uint PCB::getStackStartAddress() {return stack_start;}

//PRE:
//POST: @return, stack_end
uint PCB::getStackEndAddress() {return stack_end;}

//PRE: uint p_start, program start address
//     uint p_end, program end address
//     uint s_start, stack start address
//     uint s_end, stack end address
//POST: program_start = p_start
//      program_end = p_end
//      stack_start = s_start
//      stack_end = s_end
//      registers[STACK_POINTER_INDEX] = stack_end;
void PCB::initPCB(uint p_start, uint p_end, uint s_start, uint s_end) {
  //progame address
  program_start = p_start;
  program_end = p_end;
  //stack
  stack_start = s_start;
  stack_end = s_end;
  registers[STACK_POINTER_INDEX] = stack_end;
}


//PRE:  int num_steps, the number of steps the user wanted to run the program
//POST: @return whether the program is able to run
bool PCB::ableToRun(int num_steps) {
  bool return_value = false;
  if(num_steps > steps && !halted) {
    return_value = true;
  }
  return return_value;
}

//PRE:
//POST: deletes the dynamic memory
PCB::~PCB() {
  if (name != NULL) {
    delete [] name;
    name = NULL;
  }
}
