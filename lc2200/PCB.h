#ifndef INCLUDED_PCB
#define INCLUDED_PCB

#include "useful_classes/MyString.h"

class PCB {
  private:
    unsigned int program_length;  //holds the length of the program
    MyString name;                //holds the name of the progame
    unsigned int steps;                    //holds the number of steps conducted on pass

  public:

    //Constructor
    //PRE:  @param char * name, the name of the program
    //POST: creates the object
    PCB(char * given_name);

    //======================================
    // Getters
    //======================================

    //PRE:
    //POST: @return, unsigned int program_length
    unsigned int getLength();

    //PRE:
    //POST: @return, int steps
    unsigned int getSteps();

    //PRE:
    //POST: returns the name of the progam as a char*
    char * getName();

    //======================================
    // Setters
    //======================================

    //PRE:  int n, the length of the program
    //POST: sets lenth = n;
    void setLength(int n);

    //PRE:
    //POST: increments the steps by 1
    void incrementSteps();

    //PRE:
    //POST: sets steps to 0
    void resetSteps();

    //PRE:  @param int n, the number to to set to steps
    //POST: sets steps = n
    void setSteps(int n);

    //PRE:  @param char * name, takes the array to set to the new name
    //POST: sets name = new_name
    void setName(char * new_name);
};
#endif
