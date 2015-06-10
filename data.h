/****************************************************************************/
// Author: Kirolous Frouk
// Date  : 4/10/2015
// File Name: data.h
// This file contains all the masks and macros used for the data instruction.
/*****************************************************************************/

#define d_operationMask         0x0F00 // the mask used to locate the operation bits 
#define d_operationShift		8 
#define d_operation(i)   (d_operationMask & i) >> d_operationShift //returs the operation with in an instruction 

#define d_and     0x00 //0000
#define d_eor     0x01 //0001
#define d_sub     0x02 //0010 
#define d_sxb     0x03 //0011
#define d_add     0x04 //0100
#define d_adc     0x05 //0101
#define d_lsr     0x06 //0110
#define d_lsl     0x07 //0111
#define d_tst     0x08 //1000
#define d_teq     0x09 //1001
#define d_cmp     0x0A //1010
#define d_ror     0x0B //1011
#define d_orr     0x0C //1100
#define d_mov     0x0D //1101
#define d_bic     0x0E //1110
#define d_mvn     0x0F //1111

