#include "Terminal.h"
#include "constants.h"
#include "Exception.h"
#include "useful_classes/MyString.h"
#include "Machine.h"
#include "useful_functions/char_arrays.h"
#include <fstream>
#include <iostream>
using namespace std;

// Default Constructor
// Pre:
// Post:
Terminal::Terminal() {
  running = false;
  machine = Machine();
}

// Constructor
// Pre:  @param char * memory_size, the memory size to send to the Machine
//      memory_size > 0
// Post: makes the Machine and sets the memory size
//throw(Exception((char *)"INVALID MEMORY PARAMETER, N > 0"));
Terminal::Terminal(char * memory_size_char) {
  int memory_size = arrayToInt(memory_size_char);
  if(memory_size > 0) {
    running = false;
    machine = Machine(memory_size);
  } else {
    throw(Exception((char *)"INVALID MEMORY PARAMETER, N > 0"));
  }

}

// Pre:
// Post: runs until the program is ended
void Terminal::start() {
  running = true;
  while (running == true) {
    try{
      //cout << "> ";
      cout << "> ";
      char input [MAX_INPUT_SIZE];
      cin.getline(input, MAX_INPUT_SIZE);
      runCommand(input);
    } catch(Exception e){
      e.handle();
    }
  }
}

//PRE:  @param char * input, int input string the user specifed
//POST: decodes the input, assures it has the proper number of parameters and
//      sends it to the appropriate function
void Terminal::runCommand(char * input) {
  MyString string = input;
  LList<MyString> tokens = string.split(' '); //splits the string at ' '
  validateInput(tokens);
  if(running == true) {
    //Assert: have not hit the exit command and the command
    //        has the correct number of inputs
    bool done = false;
    bool in;
    bool out;
    while(!done) {
      in = false;
      out = false;
      char * output = machine.runCommand(input, in, out, done);
      if(in){
        //ASSERT: recived the signal from Machine asking for input
        char * input_term;
        input_term = getInput();          // gets that input needs to be delted
        machine.giveInput(input_term); // sets that input to the Machine
        delete [] input_term;
        input_term = NULL;

      } else if (out){
        cout << output;
        delete [] output;
        output = NULL;
      }
    }
  }

}

//PRE:  @param LList<MyString> tokens, the separed tokens for the program
//POST: validates that the commands are correct and that the command is not
//      the exit command, if the exit command is given thent the program is
//      exited
//throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO LOAD"));
//throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO MEM"));
//throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO CPU"));
//throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO RUN"));
//throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO EXIT"));
//throw(Exception((char *)"INVALID COMMAND GIVEN"));
void Terminal::validateInput(LList<MyString> tokens) {
  MyString command = tokens.getFront();       //gets the command
  if( compareCharArray(command.getString(), COMMANDS[LOAD_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_LOAD_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO LOAD"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[MEM_NUM]) ) {
    if(tokens.getSize() > NUMBER_OF_MEM_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO MEM"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[CPU_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_CPU_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO CPU"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[STEP_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_STEP_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO STEP"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[RUN_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_RUN_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO RUN"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[EXIT_NUM]) ) {
    if(tokens.getSize() == NUMBER_OF_EXIT_PARAMS) {
      exit();
    } else {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO EXIT"));
    }
  } else {
    throw(Exception((char *)"INVALID COMMAND GIVEN"));
  }
}


// Pre:  takes input from the terminal, number should be a int
// Post: @return a array of characters that was given from input if the input
//       is not an valid input(int) it will re-ask the user until valid
//       int input is given
char * Terminal::getInput() {
  char * input = new char [MAX_INPUT_SIZE]; //fix to be char []
  bool valid_input = false;
  while(!valid_input){
    cout << "Input: ";
    cin.getline(input, MAX_INPUT_SIZE);
    MyString string = input;
    LList<MyString> tokens = string.split(' ');
    try{
      if(tokens.getSize() == 1){ //EDIT FOR INVALID INPUT
        arrayToInt(tokens.getFront().getString());
        //ASSERT: the input is only one word
        valid_input = true;
      }else{
        cerr << "ERROR: INCORRECT INPUT SIZE" << endl;
        valid_input = false;
      }
    } catch(Exception e){
      valid_input = false;
      e.handle();
    }
  }
  return input;
}


// Pre:
// Post: exits the terminal
void Terminal::exit() {
  running = false;
}


//Destructor
// Pre:
// Post:
Terminal::~Terminal() {
  
}
