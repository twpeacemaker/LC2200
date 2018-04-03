#include "PCB.h"
#include "constants.h"
#include <stdio.h>
#include "CPU.h"
#include <iostream>
#include <fstream>
using namespace std;

#include "useful_classes/LList.h"



//Constructor
//PRE:  @param char * name, the name of the program
//      @param int id, the unique id that is given to the PCB
//      @param uint given_length, the length of the progam
//      @param fstream & stream, the file stream of the object
//POST: creates the object
PCB::PCB(char * given_name, int p_id, uint length, uint prog_stream_start) {
  name = given_name;
  program_length = length;
  steps = 0;
  halted = false;
  id = p_id;
  PC = 0;
  registers[0] = 0;
  file_stream = new fstream (given_name, ios::in | ios::out);
  program_stream_start = prog_stream_start;
}

//PRE:  @param PageInfo * page, the page to be added to the pagetable
//POST: adds the page to the page table
void PCB::addPage(PageInfo * page) {
  page_table.addBack(page);
}

//======================================
// Getters
//======================================

//PRE:
//POST: @return, uint program_stream_start
uint PCB::getStreamStart() const {
  return program_stream_start;
}

//PRE:
//POST: @return, uint program_length
uint PCB::getLength() const {return program_length;}

//PRE:
//POST: returns fstream & file_stream
fstream * PCB::getStream() {return file_stream;}

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


//PRE:
//POST: @return the value at the register[SP]
uint PCB::getSP() const {
  return registers[STACK_POINTER_INDEX];
}


//PRE:
//POST: @return the value of PC
uint PCB::getPC() const {
  return PC;
}

//PRE:  @param int index, index of register [0-15] inclusive
//POST: @return register[index]
uint PCB::getRegister(uint index) const {
  return registers[index];
}

//======================================
// Setters
//======================================

//PRE:  @param int index, index of registers [0-15] inclusive
//      @param int value, the value you want register[index] to be
//POST: register[index] = value
//throw(Exception((char *)"ERROR: ZERO REGISTER CAN NOT BE CHANGED."));
void PCB::setRegister(uint index, uint value) {
  registers[index] = value;

}

//PRE: @param int value, the value you want to be set to PC
//POST: PC = value;
void PCB::setPC(uint value) {
  PC = value;
}

//PRE: @param int value, the value you want to be set to SP
//POST: register[SP] = value
void PCB::setSP(uint value) {
  registers[STACK_POINTER_INDEX] = value;
}

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


//PRE: @param uint SP, where the register SP will be set to
//POST: registers[STACK_POINTER_INDEX] = stack_end;
void PCB::initPCB(uint SP) {
  PC = 0;
  registers[STACK_POINTER_INDEX] = SP;
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

//PRE:  @param uint PC, the relitive pc, assumes in bounds of the program
//      @param uint page_size, the size of the page
//      @param uint stack_size, the size of the stack
//POST: @return, return_value gets the address from the machine and calculates
//               the effective address of memory
uint PCB::filterPC(uint PC, uint page_size, uint stack_size) {
  uint return_value;
  uint location = PC / BYTES_IN_WORD;
  uint stack = false;
  if(location >= program_length) {
    stack = true;
  }
  uint virtual_page_number;
  if(stack) {
    location = (location - (program_length - 1)) - stack_size;
  }
  virtual_page_number = location / page_size;
  PageInfo * page;
  bool found = false;
  int i = 0;
  while(i < page_table.getSize() && !found) {
    page = page_table.getNth(i);
    if(page->getVirtualPage() == virtual_page_number && page->getStack() == stack) {
      found = true;
    }
    i++;
  }
  if(!found) {

  } else {
    uint page_line = (location % page_size) * BYTES_IN_WORD;
    return_value = ((page->getPhysicalPage() * page_size) * BYTES_IN_WORD);
    if (stack) {
      return_value = return_value + ((page_size - 1) * BYTES_IN_WORD);
    } else {
      return_value += page_line;
    }
  }
  return return_value;
}


ostream & operator <<(ostream & str, const PCB * M){

  if(M == NULL) {
    str << "is null";
  } else {
    for(int i = 0; i < MAX_REGISTERS; i++) {
      cout << "(" << i << ") "  << M->getRegister(i) << endl;
    }
  }
  return (str);
}

//PRE:
//POST: deletes the dynamic memory
PCB::~PCB() {
  if (name != NULL) {
    delete [] name;
    name = NULL;
  }
}
