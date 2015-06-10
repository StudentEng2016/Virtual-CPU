/****************************************************************************/
// Author: Kirolous Frouk
// Date  : 4/24/2015
// File Name: loadStore.h
// This file contains all the masks and macros used for the Load and store instruction.
/*****************************************************************************/
#define LS_L_MASK   0x0800  // 1000 
#define LS_B_MASK   0x0400  //0100 

#define get_L_bit(i)   ((LS_L_MASK & i) == LS_L_MASK) ? 1 : 0 //gets the l bit in the load an store instruction 
#define get_B_bit(i)  ((LS_B_MASK & i) == LS_B_MASK) ? 1 : 0//gets the B bit in the load an store instruction 
#define BYTE_MASK   0xFF