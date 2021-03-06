#ifndef INCLUDED_TERMINAL
#define INCLUDED_TERMINAL

#include "constants.h"
#include "Exception.h"
#include "useful_classes/MyString.h"
#include "Machine.h"
#include "useful_functions/char_arrays.h"
#include <fstream>
#include <iostream>
using namespace std;

class Terminal {

  // Class Invariant (CI): must start the progame to start the terminal.
  // the terminal facilitate INPUT and OUTPUT to and from the Machine and
  // ends the progame on the command exit. 

  private:

    bool running;          // whether the terminal is runnning
    Machine machine; // pointer to the Machine

    //PRE:  @param char * input, int input string the user specifed
    //POST: decodes the input, assures it has the proper number of parameters
    //      and sends it to the appropriate function
    void runCommand(char * input);

    //PRE:  @param LList<MyString> tokens, the separed tokens for the program
    //POST: validates that the commands are correct and that the command is not
    //      the exit command, if the exit command is given thent the program is
    //      exited
    //throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO LOAD"));
    //throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO MEM"));
    //throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO CPU"));
    //throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO RUN"));
    //throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO EXIT"));
    void validateInput(LList<MyString> tokens);

    // Pre:
    // Post: @return a array of characters that was given from input if the
    //       input
    //       is not an valid input it will re-ask the user until valid input is
    //       taken
    char * getInput();

    // Pre:
    // Post: exits the terminal
    void exit();



  public:

    // Default Constructor
    // Pre:
    // Post: makes the Machine to be Default size
    Terminal();

    // Constructor
    // Pre:  @param char * memory_size, the memory size to send to the Machine
    // Post: makes the Machine and sets the memory size
    Terminal(char * memory_size_char);

    // Pre:
    // Post: runs until the program is ended
    void start();

    //Destructor
    // Pre:
    // Post:
    ~Terminal();



};

#endif
