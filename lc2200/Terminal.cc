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
      cout << "LC-2200> ";
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
  MyString command = tokens.getFront();       //gets the command
  if( compareCharArray(command.getString(), COMMANDS[LOAD_NUM]) ) {
    if(tokens.getSize() == NUMBER_OF_LOAD_PARAMS) {
      load(input);
    } else {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO LOAD"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[MEM_NUM]) ) {
    if(tokens.getSize() <= NUMBER_OF_MEM_PARAMS) {
      mem(input);
    } else {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO MEM"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[CPU_NUM]) ) {
    if(tokens.getSize() == NUMBER_OF_CPU_PARAMS) {
      cpu();
    } else {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO CPU"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[STEP_NUM]) ) {
    if(tokens.getSize() == NUMBER_OF_STEP_PARAMS) {
      step(input);
    } else {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO LOAD"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[RUN_NUM]) ) {
    if(tokens.getSize() == NUMBER_OF_RUN_PARAMS) {
      run(input);
    } else {
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

// Pre: @param char * input, int input string the user specifed
// Post:
void Terminal::load(char * input) {
  cout << "load method" << endl;
}

// Pre: @param char * input, int input string the user specifed
// Post: prints to termmial the memory ranage inclusive
void Terminal::mem(char * input) {
  char * output;
  output = simulator->memSim(input);
  cout << output;
  delete [] output;
  output = NULL;

}

// Pre:
// Post: prints to termmial the the values of registers
void Terminal::cpu() {
  char * output;
  output = simulator->cpuSim();
  cout << output;
  delete [] output;
  output = NULL;

}

// Pre: @param char * input, int input string the user specifed
// Post: exe n number of lines or until the program is done
void Terminal::step(char * input) {

  MyString string = input;
  LList<MyString> tokens = string.split(' ');

  bool done = false;
  bool in; bool out;
  char output [MAX_OUTPUT_REGISTER_SIZE];
  int num_steps = array_to_int( tokens.getNth(STEP_TOKEN_N).getString() );

  while(!done){
    in = false;
    out = false;
    simulator->stepSim(num_steps, in, out, done, output);
    if(in){
      //ASSERT: recived the signal from Simulator asking for input
      input = getInput();          // gets that input needs to be delted
      simulator->giveInput(input); // sets that input to the simulator
      delete [] input;
      input = NULL;

    } else if (out){
      cout << output << endl;
    }
  }

}

// Pre: @param char * input, int input string the user specifed
// Post: runs until the program is finnished
void Terminal::run(char * input) {
  //simulator->stepRun();
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
