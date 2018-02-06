#ifndef INCLUDED_CONSTANTS
#define INCLUDED_CONSTANTS




static char REGISTER_NAMES[][6] =
{
	"$zero", "$at", "$v0", "$a0", "$a1", "$a2",
	"$t0"  , "$t1", "$t2", "$s0", "$s1", "$s2",
	"$k0"  , "$sp", "$fp", "$ra"
};

typedef unsigned int uint;

#define MAX_INPUT_SIZE 80
#define MAX_PROG_OUTPUT_SIZE 30

//default config
#define DEFAULT_MEM 1024
#define DEFAULT_STACK 64

#define NUMBER_OF_COLS_IN_MEM 4
#define COL_ONE_MEM 1
#define COL_TWO_MEM 2
#define COL_THREE_MEM 3
#define MAX_COL_MEM 40

#define MAX_COL_CPU 40
#define NUMBER_OF_COLS_IN_CPU 4


//bit manipulation
#define MAX_BYTE_SIZE 0x000000FF
#define BYTES_IN_WORD 4
#define BITS_IN_BYTES 8
#define WORD_SIZE 		32

//char arrays
#define AOFFSET 10

#define MAX_OUTPUT_REGISTER_SIZE 5


#define OPCODE_UPPER_BIT 31
#define OPCODE_LOWER_BIT 28

#define REGX_UPPER_BIT 27
#define REGX_LOWER_BIT 24

#define REGY_UPPER_BIT 23
#define REGY_LOWER_BIT 20


#define REGZ_UPPER_BIT 3
#define REGZ_LOWER_BIT 0


#define SIGNED_OR_OFFSET_UPPER_BIT 19
#define SIGNED_OR_OFFSET_LOWER_BIT 0

#define STACK_POINTER_INDEX 13

enum opcodes
{
	ADD,
	NAND,
	ADDI,
	LW,
	SW,
	BEQ,
	JALR,
	HALT,
	IN = 9,
	OUT,
	LA = 12,
	BGT
};

static char COMMANDS[][6] =
{
"load",
"mem",
"cpu",
"step",
"run",
"exit"
};

#define LOAD_NUM 	0
#define MEM_NUM 	1
#define CPU_NUM 	2
#define STEP_NUM 	3
#define RUN_NUM 	4
#define EXIT_NUM 	5

#define NUMBER_OF_LOAD_PARAMS 2
#define NUMBER_OF_MEM_PARAMS 	3
#define NUMBER_OF_CPU_PARAMS 	1
#define NUMBER_OF_STEP_PARAMS 2
#define NUMBER_OF_RUN_PARAMS 	1
#define NUMBER_OF_EXIT_PARAMS 1

#define STEP_TOKEN_N 1


// #define LOAD_NUM 0
// #define MEM_NUM  1
// #define CPU_NUM  2
// #define STEP_NUM 3
// #define RUN_NUM  4
// #define EXIT_NUM 5
//
// #define LOAD_TOKENS 2
// #define MEM_TOKENS  3
// #define CPU_TOKENS  1
// #define STEP_TOKENS 2
// #define RUN_TOKENS  1
// #define EXIT_TOKENS 1
// #define KILL_TOKENS 2

//register
#define MAX_REGISTERS 16

//opcode config
#define R_TYPE 4
#define I_TYPE 4
#define J_TYPE 3
#define U_TYPE 2
#define L_TYPE 3
#define O_TYPE 1

#define NUMBER_OF_OPCODES 13
#define ADD_ARGUMENT   		R_TYPE // 0
#define NAND_ARGUMENT  		R_TYPE // 1
#define ADDI_ARGUMENT  		I_TYPE // 2
#define LW_ARGUMENT    		I_TYPE // 3
#define SW_ARGUMENT   		I_TYPE // 4
#define BEQ_ARGUMENT  		I_TYPE // 5
#define JALR_ARGUMENT 		J_TYPE // 6
#define HALT_ARGUMENT 		O_TYPE // 7
#define IN_ARGUMENT   		U_TYPE // 9
#define OUT_ARGUMENT  		U_TYPE // 10
#define LA_ARGUMENT   		L_TYPE // 12
#define BGT_ARGUMENT  		I_TYPE // 13
#define EMPTY_ARGUMENT    0

static int OPCODES_ARGUMENTS[] =
{
	ADD_ARGUMENT,  // 0
	NAND_ARGUMENT, // 1
	ADDI_ARGUMENT, // 2
	LW_ARGUMENT,   // 3
	SW_ARGUMENT,   // 4
	BEQ_ARGUMENT,  // 5
	JALR_ARGUMENT, // 6
	HALT_ARGUMENT, // 7
	EMPTY_ARGUMENT,// 8
	IN_ARGUMENT,   // 9
	OUT_ARGUMENT,  // 10
	EMPTY_ARGUMENT,// 11
	LA_ARGUMENT,   // 12
	BGT_ARGUMENT   // 13
};



#endif
