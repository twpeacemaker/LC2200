#include "constants.h"
#include "Terminal.h"
#include "Exception.h"
#include "useful_classes/MyString.h"
#include "Simulator.h"

#include "useful_functions/char_arrays.h"

#include <fstream>
#include <iostream>
using namespace std;

// Default Constructor
// Pre:
// Post:
Terminal::Terminal() {
  running = false;
  simulator = new Simulator();
}

// Constructor
// Pre:  @param char * memory_size, the memory size to send to the simulator
// Post: makes the simulator and sets the memory size
Terminal::Terminal(char * memory_size_char) {
  int memory_size = array_to_int(memory_size_char);
  running = false;
  //Assert: check to make sure memory / 4
  simulator = new Simulator(memory_size);


}

// Pre:
// Post: makes the simulator to be Default size
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
      char * output = simulator->runCommand(input, in, out, done);
      if(in){
        //ASSERT: recived the signal from Simulator asking for input
        char * input_term;
        input_term = getInput();          // gets that input needs to be delted
        simulator->giveInput(input_term); // sets that input to the simulator
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
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO LOAD"));
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


// Pre:
// Post: @return a array of characters that was given from input
char * Terminal::getInput() {
  char * input = new char [MAX_INPUT_SIZE]; //fix to be char []
  bool valid_input = false;
  while(!valid_input){
    cout << "Input: ";
    cin.getline(input, MAX_INPUT_SIZE);
    MyString string = input;
    LList<MyString> tokens = string.split(' ');
    if(tokens.getSize() == 1){
      //ASSERT: the input is only one word
      valid_input = true;
    }else{
      cout << "ERROR: INCORRECT INPUT SIZE" << endl;
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
