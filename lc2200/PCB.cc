#include "PCB.h"


//PRE:
//POST:
PCB::PCB() {

}

//Constructor
//PRE:  @param char * name, the name of the program
//      @param uint given_length, the length of the progam
//POST: creates the object
PCB::PCB(char * given_name, uint length) {
  name = given_name;
  program_length = length;
  steps = 0;
}

//======================================
// Getters
//======================================

//PRE:
//POST: @return, uint program_length
uint PCB::getLength() {return program_length;}

//PRE:
//POST: @return, int steps
uint PCB::getSteps() {return steps;}


//PRE:
//POST: returns the name of the progam as a char*
char * PCB::getName() {return name;}

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
//POST: deletes the dynamic memory
PCB::~PCB() {
  if (name != NULL) {
    delete [] name;
    name = NULL;
  }
}
