/****************************************************************************/
// Author: Kirolous Frouk
// Date  : 3/26/2015
// File Name: Immeadiate.h
// This file contains all the masks and macros used for the Immediate instruction.
/*****************************************************************************/
#define MOV_IMM     0x4000
#define CMP_IMM     0x5000
#define ADD_IMM     0x6000
#define SUB_IMM     0x7000

#define IMM_VAL     0x0FF0
#define IMM_VAL_SHIFT    4  


#define IMM(i)  ((i & IMM_VAL) >> IMM_VAL_SHIFT)
#define IMM_OPCODE  0x7000
#define IMM_GET_OPCODE(x)   (IMM_OPCODE & x)

