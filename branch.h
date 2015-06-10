/****************************************************************************/
// Author: Kirolous Frouk
// Date  : 4/16/2015
// File Name: branch.h
// This file contains all the masks used for the branching instructions.
// Both Conditional and Un conditional branche masks and macros are in this file.
/*****************************************************************************/

/*********************************Conditional branching***********************/
#define c_EQ	 0x000 //0000 equal
#define c_NE     0x100 //0001 Not equal
#define c_CS     0x200 //0010 Unsigned higher or same 
#define c_CC     0x300 //0011 Unsigned lower
#define c_MI     0x400 //0100 negative
#define c_PL     0x500 //0101 positive
#define c_HI     0x800 //1000 Unsigned higher
#define c_LS     0x900 //1001 Unsigned lower or same 
#define c_AL     0xE00 //1110 Always


#define conditional_op 0x0F00  // the mask to get the condition code
#define Conditional_op_code(i)  (conditional_op & i) // A simple and is used to get the code 

#define conditional_addr_mask   0x00FF //Address mask
#define conditional_addr(i)    (conditional_addr_mask & i)  // A simple and is used to get the address 


/*******Unconditional Branch********/
#define BRA      0xC000 // Mask to branch 
#define BRL      0xD000 // Mask to branch with link 
#define unCond_addrMask   0x0FFF  //Address mask
#define unCond_offset(i)    (unCond_addrMask & i) //get the address

// Macros that test against the mask 
//True =1 false =0
#define is_unCond_BRA(i)    ((BRA & i) == BRA) ? 1 : 0
#define is_unCond_BRL(i)    ((BRL & i) == BRL) ? 1 : 0 