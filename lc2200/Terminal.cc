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
    bool post_i_o = false;
    bool current_process_done = false;
    bool set_slice_made = false;
    while(!done) {
      in = false;
      out = false;
      char * output = machine.runCommand(input, in, out, done, post_i_o,
                                         current_process_done, set_slice_made);
      if(in){
        //ASSERT: recived the signal from Machine asking for input
        char * input_term;
        input_term = getInput();          // gets that input needs to be delted
        machine.giveInput(input_term); // sets that input to the Machine
        delete [] input_term;
        input_term = NULL;
        post_i_o = true;
      } else if (out){
        cout << output;
        delete [] output;
        output = NULL;
        post_i_o = true;
      } else {
        post_i_o = false;
      }
    }
  }

}

//PRE:  @param LList<MyString> tokens, the separed tokens for the program
//POST: validates that the commands are correct and that the command is not
//      the exit command, if the exit command is given thent the program is
//      exited
//throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO {{command}}"));
void Terminal::validateInput(LList<MyString> tokens) {
  MyString command = tokens.getFront();       //gets the command
  //================== Machine Commands ================================
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
  } else if( compareCharArray(command.getString(), COMMANDS[FREEMEM_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_FREEMEM_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO FREEMEM"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[JOBS_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_JOBS_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO JOBS"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[KILL_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_KILL_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO KILL"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[EXIT_NUM]) ) {
    if(tokens.getSize() == NUMBER_OF_EXIT_PARAMS) {
      exit();
    } else {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO EXIT"));
    }
  }else if( compareCharArray(command.getString(), COMMANDS[CONFIG_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_CONFIG_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO CONFIG_NUM"));
    }
  }
  //================== File System Commands ================================
  else if( compareCharArray(command.getString(), COMMANDS[FORMAT_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_FORMAT_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO FORMAT"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[PWD_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_PWD_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO PWD"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[LS_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_LS_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO LS"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[CD_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_CD_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO CD"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[MKDIR_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_MKDIR_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO MKDIR"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[RMDIR_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_RMDIR_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO RMDIR"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[DISPLAYINODE_NUM])){
    if(tokens.getSize() != NUMBER_OF_DISPLAYINODE_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO DISPLAYINODE_NUM"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[CP_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_CP_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO CP"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[CAT_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_CAT_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO CAT"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[RM_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_RM_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO RM"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[DU_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_DU_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO DU"));
    }
  } else if( compareCharArray(command.getString(), COMMANDS[DEFRAG_NUM]) ) {
    if(tokens.getSize() != NUMBER_OF_DEFRAG_PARAMS) {
      throw(Exception((char *)"INVALID NUMBER OF PARAMS GIVEN TO DEFRAG_NUM"));
    }
  }
  else {
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
    uint id = machine.getCurrentProcessID();
    cout << "PCB(" << id << ") " << "Input: ";
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
