#include "Simulator.h"
#include "CPU.h"
#include "Memory.h"
#include "constants.h"
#include "Exception.h"
#include <stdio.h>


#include "useful_functions/bit_manipulation.h"
#include "useful_functions/char_arrays.h"

// Default Constructor
// Pre :
// Post: initlizes the Simulator class
Simulator::Simulator() {
  memory = new Memory(); //DEFAULT_MEM
}


// Pre : @param unsigned int memory_size inits the size of memory
//       memory size is % 4
// Post: initlizes the Simulator class
Simulator::Simulator(unsigned int memory_size) {
  memory = new Memory( (memory_size / BYTES_IN_WORD)); ////if is specified
}

//PRE:
//POST:
void Simulator::executeLine(bool & in_bool, bool & out_bool, char output[]) {
  int line = getCurrentLine(); //fetch: gets the current line
  cpu.incrementPC();           //once the line is fetched the PC is incremented

  int opcode = getOpcode(line); //decode: determines opcode being called
  switch(opcode) { //execute: sends to the correct opcode
    case ADD:
      add( getRegX(line), getRegY(line), getRegZ(line) );
      break;
    case NAND:
      nand( getRegX(line), getRegY(line), getRegZ(line) );
      break;
    case ADDI:
      addi( getRegX(line), getRegY(line), getSignedOrOffset(line) );
      break;
    case LW:
      lw( getRegX(line), getRegY(line), getSignedOrOffset(line) );
      break;
    case SW:
      sw( getRegX(line), getRegY(line), getSignedOrOffset(line) );
      break;
    case BEQ:
      beq( getRegX(line), getRegY(line), getSignedOrOffset(line) );
      break;
    case JALR:
      jalr( getRegX(line), getRegY(line) );
      break;
    case HALT:
      halt();
      break;
    case IN:
      in_bool = true; //signal to say the simulator needs input
      break;
    case OUT:
      out_bool = true;//signal to say the simulator needs output
      out( getRegX(line), output ); //builds the output
      break;
    case LA:
      la( getRegX(line), getSignedOrOffset(line));
      break;
    case BGT:
      bgt( getRegX(line), getRegY(line), getSignedOrOffset(line) );
      break;
    default:
      cerr << "default \n";
      break;
  }
}

//PRE: @param int num_step, the number of lines to execute
//     @param bool in, iif true the program needs input
//     @param book out iif true the program needs output
//     @param done iff the progam has reached the halt statemetn
//     @param char* output the output if out is true
//POST:runs n steps of the currently loaded program
void Simulator::stepSim(int & num_steps, bool & in, bool & out, bool & done, char * output) {
  while(num_steps > 0) {
    //cout << num_steps << endl;
    executeLine(in, out, output);
    num_steps--;
  }
  done = true;
}

//PRE:  @param char * input, takes the input to run
//      @param char * output, takes the output to be build up
//POST: @print the content of memory
//      if 1 token given, 0 - memory size
//      if 2 tokens token[1] - memory size
//      if 3 tokens token[1] - token[2]
void memSim(char * input, char * output) {

    output = memory.getStatus(input);
}

//======================================
// Word Getters
//======================================

//PRE:  @param int line, is the line to be executed, lenth = 4 bytes
//POST: @return int opcode from the line is executed
int Simulator::getOpcode(int line){
  return getBits(line, OPCODE_UPPER_BIT, OPCODE_LOWER_BIT);
}

//PRE:  @param int line, is the line to be executed, lenth = 4 bytes
//POST: @return int regX from the line is executed
int Simulator::getRegX(int line) {
  return getBits(line, REGX_UPPER_BIT, REGX_LOWER_BIT);
}

//PRE:  @param int line, is the line to be executed, lenth = 4 bytes
//POST: @return int regY from the line is executed
int Simulator::getRegY(int line) {
  return getBits(line, REGY_UPPER_BIT, REGY_LOWER_BIT);
}

//PRE:  @param int line, is the line to be executed, lenth = 4 bytes
//POST: @return int regZ from the line is executed
int Simulator::getRegZ(int line) {
  return getBits(line, REGZ_UPPER_BIT, REGZ_LOWER_BIT);
}

//PRE:  @param int line, is the line to be executed, lenth = 4 bytes
//POST: @return int Signed Value or Offset from the line is executed
int Simulator::getSignedOrOffset(int line) {
  return getBits(line, SIGNED_OR_OFFSET_UPPER_BIT, SIGNED_OR_OFFSET_LOWER_BIT);
}

//PRE:
//POST: @returns the current progame line
int Simulator::getCurrentLine() {
  //return memory->getIndex(cpu.getPC());
  return 0xA0000000;
}

//PRE:
//POST: @returns the previous progame line
int Simulator::getPrevLine() {
  //return memory->getIndex(cpu.getPC() - 1);
  return 0xA0000000;
}

//======================================
// INPUT
//======================================

//PRE:  @param int input, should be valid to be entered to a register at the
//      current line
//POST: sets the register specifed in the current line to the input taken
void Simulator::giveInput(char * input) {
  int line = getPrevLine();
  int num = array_to_int(input);
  in( getRegX(line), num );


}

//======================================
// R - Type Operations
//======================================

//PRE:  @param int regX, regY, and regZ, range [0-15] inclusive
//POST: register[regX] will reflect the sum of register[regY] and
//      register[regY]
void Simulator::add(int regX, int regY, int regZ) {
  int sum = cpu.getRegister(regY) + cpu.getRegister(regZ);
  cpu.setRegister(regX, sum);
  //printf("regX(%d) = regY(%d) + regZ(%d)  \n", regX, regY, regZ);
}

//PRE:  @param int regX, regY, and regZ, range [0-15] inclusive
//POST: register[regX] will reflect the ~and of register[regY] and
//      register[regY]
void Simulator::nand(int regX, int regY, int regZ) {
  int not_and = ~( cpu.getRegister(regY) & cpu.getRegister(regZ) );
  cpu.setRegister(regX, not_and);
}

//======================================
// I - Type Operations
//======================================

//PRE:  @param int regX and regY, range [0-15] inclusive
//      @param int num, holds int to be added
//POST: register[regX] = register[regY] + num
void Simulator::addi(int regX, int regY, int num) {
  int sum = cpu.getRegister(regY) + num;
  cpu.setRegister(regX, sum);
}

//PRE:  @param int regX and regY, range [0-15] inclusive
//      @param int num, holds the int be be added to regY to solve location
//POST: loads the content register[regY]+ address and stores it to
//      register[regX]
void Simulator::lw(int regX, int regY, int num) {

}

//PRE:  @param int regX and regY, range [0-15] inclusive
//      @param int num, holds the int be be added to regY to solve location
//POST: stored the content of register[regX] to register[regY]+ address
void Simulator::sw(int regX, int regY, int num) {

}

//PRE:  @param int regX and regY, range [0-15] inclusive
//      @param int offset, holds the signed_value or offset
//POST: if regX == regY offset added to PC else nothing
void Simulator::beq(int regX, int regY, int offset) {

}

//PRE:  @param int regX and regY, range [0-15] inclusive
//      @param int offset, holds the signed_value or offset
//POST: if regX > regY offset added to PC else nothing
void Simulator::bgt(int regX, int regY, int offset) {

}

//======================================
// J - Type Operations
//======================================

//PRE:  @param int regX and regY, range [0-15] inclusive
//POST: set regX to be PC, set PC to be regY
void Simulator::jalr(int regX, int regY) {

}

//======================================
// U - Type Operations
//======================================

//PRE: @param int regX, range [0-15] inclusive
//PRE: @param int num, the number to be entered to regX
//POST: takes input from terminal, x and sets regX = x;
void Simulator::in(int regX, int num) {
    //cout << "REG: " << regX << " = " << num << endl;
    cpu.setRegister(regX, num);
}

//PRE:  @param int regX, range [0-15] inclusive
//      @param int & output, makes the output to send to the termainal
//POST: prints the content of regX to the terminal
void Simulator::out(int regX, char output[]) {
   sprintf (output, "%d", cpu.getRegister(regX));
}

//======================================
// L - Type Operations
//======================================

//PRE:  @param int regX, range [0-15] inclusive
//      @param int offset, holds the signed_value or offset
//POST: prints the content of regX to the terminal
void Simulator::la(int regX, int offset) {

}

//======================================
// O - Type Operations
//======================================

//PRE:  takes no params
//POST: stops the program
void Simulator::halt() {

}
