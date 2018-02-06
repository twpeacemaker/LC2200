#ifndef INCLUDED_TERMINAL
#define INCLUDED_TERMINAL

#include "constants.h"
#include "Terminal.h"
#include "Exception.h"
#include "Simulator.h"
#include "useful_classes/MyString.h"

#include <fstream>
#include <iostream>
using namespace std;

class Terminal {

  // Class Invariant (CI):

  private:

    bool running;          // whether the terminal is runnning
    Simulator * simulator; // pointer to the simulator

    // Pre: @param char user_input[], the input given by the user
    // Post:
    void runCommand(char * input);

    //PRE:  @param LList<MyString> tokens, the separed tokens for the program
    //POST: validates that the commands are correct and that the command is not
    //      the exit command, if the exit command is given thent the program is
    //      exited
    void validateInput(LList<MyString> tokens);

    // Pre:
    // Post: @return a array of characters that was given from input
    char * getInput();

    // Pre:
    // Post: exits the terminal
    void exit();



  public:

    // Default Constructor
    // Pre:
    // Post: makes the simulator to be Default size
    Terminal();

    // Constructor
    // Pre:  @param char * memory_size, the memory size to send to the simulator
    // Post: makes the simulator and sets the memory size
    Terminal(char * memory_size_char);

    // Pre:
    // Post: begins the termial and runs till exit is typed
    void start();

    //Destructor
    // Pre:
    // Post:
    ~Terminal();



};

#endif
