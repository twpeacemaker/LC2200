#ifndef INCLUDED_TERMINAL
#define INCLUDED_TERMINAL

#include "constants.h"
#include "Terminal.h"
#include "Exception.h"
#include "Simulator.h"

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

    // Pre:
    // Post: @return a array of characters that was given from input
    char * getInput();

    // Pre: @param char * input, int input string the user specifed
    // Post:
    void load(char * input);

    // Pre: @param char * input, int input string the user specifed
    // Post: prints to termmial the memory ranage inclusive
    void mem(char * input);

    // Pre: @param char * input, int input string the user specifed
    // Post: prints to termmial the the values of registers
    void cpu();

    // Pre: @param char * input, int input string the user specifed
    // Post: exe n number of lines or until the program is done
    void step(char * input);

    // Pre: @param char * input, int input string the user specifed
    // Post: runs until the program is finnished
    void run(char * input);

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
