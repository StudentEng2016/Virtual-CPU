/****************************************************************************/
// Author: Kirolous Frouk
// Date  : 3/10/2015
// File Name: Immeadiate.c
// This file contains  the implementaion of the immeadiate instruction
/*****************************************************************************/
#include "Imediate.h"
#include "head.h"

/****************************************************************************/
// Function: void immediate(unsigned int inst)
// 
//This function takes an instruction compares it with masks and preforms the coreect operation 
/*****************************************************************************/
void immediate(unsigned int inst)
{
	unsigned int  code = IMM_GET_OPCODE(inst);
	uint8_t rd = RD(inst); //getting rd from the instruction 
	uint16_t imm = IMM(inst);
	switch(code) {
	case MOV_IMM:
		alu = imm;		
		set_sz_flags();
		reg[rd] = alu;	
		break;

	case CMP_IMM:
		alu=reg[rd]& ~(imm + 1); 
		set_flags(reg[rd],imm);
		break;

	case ADD_IMM:
		alu=reg[rd]+imm; 
		set_flags(reg[rd],imm);
		reg[rd]=alu;
		break;
	case SUB_IMM:
		alu=reg[rd]+(~imm+1); 
		set_flags(reg[rd],~(imm+1));
		reg[rd]=alu;
		break;
	}


	return;
}