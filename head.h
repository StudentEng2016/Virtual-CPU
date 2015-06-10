/****************************************************************************/
// Author: Kirolous Frouk
// Date  : 3/10/2015
// File Name: head.h
// This file contains all the function prototypes for this project 
// it also contains macros and masks to determine instruction type
/*****************************************************************************/
#include <stdio.h>
#include <stdlib.h> 
#include<ctype.h>
#include<string.h>
#include <stdint.h>


void split(); // Splits Instruction register 
void prompt(); //User interface
void set_sz_flags(); //Sets the Sign and Zero flags 
void WriteFile(void * memory); //Writes a file to memory 
int LoadFile(void * memory, unsigned int max);//LOads a file to memory 
void MemDump(void *memptr, unsigned offset, unsigned length);//Displays memory 
void memoryModifiy(void *memory, unsigned int offset);//Modifies memory 
void printReg();//prints the registers 
void fetch(void *memptr);//Fetches and executes the next instruction 
void trace();//fetches, executes and prints the registers 
void zeroAll();//Resets the program
void set_flags(uint32_t op1, uint32_t op2);//Sets all flags (carry,sign,zero)
void go();//Executes in a loop until the stop flag is set 
int iscarry(unsigned long op1,unsigned long op2); //Returns non-zero if the operation produces a carry
void execute(uint16_t inst);// Executes the proper instruction
void immediate(unsigned int inst);//Preforms immediate instruction
void data(unsigned int inst);//Preforms data instruction
void clean_stdin(void);//Flushes stdin
void loadstore(uint16_t inst);//Preforms Load and store instruction
void conditional(unsigned int inst);//Preforms Conditional branch instruction
void unConditional(unsigned int inst);//Preforms Unconditional branch instruction
void pushPull(uint16_t inst);//Preforms Push pull instruction
void push(uint8_t reg_num, uint32_t mem_addr,uint8_t oneByte);//Pushes one register
void pull(uint8_t reg_num, uint32_t mem_addr,uint8_t oneByte);//Pulls one register


unsigned char memory[16384];// Global variable for memory 
static const int memorySize=16384;//Size of memory 
unsigned long reg[16];//Registers ,Assumes long is 32 bits

#define lr reg[13] //Link register
#define sp reg[14]  //Stack pointer
#define pc reg[15] //Procram counter 

#define get_sp(i) i & 0x4000 // mask for sp 


//for  the flags 
unsigned static char unset = 0;
unsigned static char set = 1;

//Memory Buffer Register - buffer for all data
unsigned long MBR;

//Memory Address Register - Holds memory address
uint32_t MAR;

//Arethmetic logic unit - In my cpu i will try to use this as a storage loaction between diffrent calculations 
unsigned long alu;

//Stop flag
unsigned char stop;

//IR active flag
unsigned char ir_flag;

//	CCR	- Condition Codes - Sign, Zero and Carry flags
unsigned char sign;
unsigned char zero;
unsigned char carry;


//Instruction registers 


unsigned long IR;
uint16_t IR0;
uint16_t  IR1;
#define IR1_MASK    0x0000FFFF




/************************************Geting the instruction *************************/
#define data_instruction    0xF000     // this is a data instruction 
#define LS_instruction      0x2000      //load and store instruction 
#define IM_instruction      0x4000		//immeadiate instruction
#define Cond_branch			0x8000      //Conditional branch instruction 
#define PP_instruction      0xA000      //push or pull instruction
#define Un_cond				0xC000    //uncoditional branch instruction 
#define stop_instruction    0xE000     //stop instruction 
#define MAX32               0xFFFFFFFF  // this is the max number in 32 bytes

#define Rd    0x000F //This is a mask to be used to find rd 
#define Rn    0x00F0 //This is a mask to be used to find rn
#define shift_Rn    4 //How many units to shift to get rn 
#define MSB_check   0x80000000

// This is a technique I learned from a class mate . the code below returns non zero if its the corect instruction

#define isData(i)  ((data_instruction  & ~i) == data_instruction)  ? 1 : 0
#define isLS(i)   ((LS_instruction  & i) == LS_instruction )     ? 1 : 0
#define isIM(i)  ((IM_instruction & i) == IM_instruction)   ? 1 : 0
#define isConditional(i) ((Cond_branch & i) == Cond_branch) ? 1 : 0
#define isPP(i)   ((PP_instruction & i) == PP_instruction)     ? 1 : 0
#define isUnCond(i)   ((Un_cond & i) == Un_cond)     ? 1 : 0
#define isStop(i) ((stop_instruction & i) == stop_instruction) ? 1 : 0

#define IS_SIGN(i)      ((MSB_check & i) == MSB_check) ? 1 : 0// Check for the sign bit 
#define IS_0(i)      (i == 0) ? 1 : 0 //Check if value is zero 


#define RN(i)   ((i & Rn) >> shift_Rn) //get rn
#define RD(i)   (i & Rd) //get rd 


#define msbMask    0x80000000 // Most significant bit mask 
#define lsbMask   0x1// least significant 

#define getMsb(x)  ((msbMask & x) == msbMask) ? 1 : 0// geting the msb from a value 
#define getLsb(x)  ((lsbMask & x) == lsbMask) ? 1 : 0 //getting the lsb from a value 




