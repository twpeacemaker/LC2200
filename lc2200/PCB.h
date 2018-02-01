#ifndef INCLUDED_PCB
#define INCLUDED_PCB
#include "constants.h"
#include "useful_classes/MyString.h"

class PCB {
  private:
    uint program_length;  //holds the length of the program
    MyString name;        //holds the name of the progame
    uint steps;           //holds the number of steps conducted on pass

  public:

    //Constructor
    //PRE:  @param char * name, the name of the program
    //POST: creates the object
    PCB(char * given_name);

    //======================================
    // Getters
    //======================================

    //PRE:
    //POST: @return, uint program_length
    uint getLength();

    //PRE:
    //POST: @return, int steps
    uint getSteps();

    //PRE:
    //POST: returns the name of the progam as a char*
    char * getName();

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
};
#endif
