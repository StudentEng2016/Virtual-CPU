/****************************************************************************/
// Author: Kirolous Frouk
// Date  : 4/26/2015
// File Name: pushPull.h
// This file contains all the masks and macros used for the push and pull instruction.
/*****************************************************************************/
#define PP_OP_L     0x0800  //load store bit 1=load 0 =store
#define PP_OP_H     0x0400  // high reg or low reg 1= high 0 = low 
#define PP_OP_R     0x0100  //Extra push or pull 
#define PP_OPCODE   0x0F00// geting the op bits 
#define PP_REG      0x00FF  //masking the register list

//********************Masks used to find which registers to push or pull********************
#define PP_REG_1    0x01    // 00000001 
#define PP_REG_2    0x02    // 00000010 
#define PP_REG_3    0x04    // 00000100 
#define PP_REG_4    0x08    // 00001000 
#define PP_REG_5    0x10    // 00010000 
#define PP_REG_6    0x20    // 00100000 
#define PP_REG_7    0x40    // 01000000 
#define PP_REG_8    0x80    // 10000000 


#define PP_REG_9    0x01    // 00000001 
#define PP_REG_10    0x02   // 00000010
#define PP_REG_11   0x04    // 00000100 
#define PP_REG_12   0x08    // 00001000 
#define PP_REG_13   0x10    // 00010000 
#define PP_REG_14   0x20    // 00100000 
#define PP_REG_15   0x40    // 01000000 
#define PP_REG_16   0x80    // 10000000 

#define LOW_REG     7   //This is the max for the low registers it is used in loops
#define HIGH_REG    8   //This is the min for the high registers it is used in loops
#define HIGH_REG_MAX    15 //This is the max for the high registers it is used in loops
//***********************Code below is use to get specific bytes*********************
#define BYTE        8
#define BYTE_1(x)   (0xFF & x) 
#define BYTE_2(x)   ((0xFF00 & x) >> BYTE)
#define BYTE_3(x)   ((0xFF0000 & x) >> (BYTE * 2))
#define BYTE_4(x)   ((0xFF000000 & x) >> (BYTE * 3))
//*****************************************************************************

//***********************Code below gets diffrent parts of the pp instruction ******************
#define PP_GET_OPCODE(x)    (PP_OPCODE & x)
#define PP_GET_REG(x)       (PP_REG & x)
#define PP_get_l(i)   (PP_GET_OPCODE(i) & PP_OP_L)
#define PP_get_h(i)   (PP_GET_OPCODE(i) & PP_OP_H)
#define PP_get_r(i)   (PP_GET_OPCODE(i) & PP_OP_R)


#define PP_L_bit(i)  (PP_get_l(i) == PP_OP_L) ? 1 : 0
#define PP_H_bit(i)  (PP_get_h(i) == PP_OP_H) ? 1 : 0
#define PP_R_bit(i) (PP_get_r(i) == PP_OP_R) ? 1 : 0
//*************************************************************************************
