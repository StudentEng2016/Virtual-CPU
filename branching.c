/****************************************************************************/
// Author: Kirolous Frouk
// Date  : 4/10/2015
// File Name: branching.c
// This file contains  the implementaion of the uncondtional anc coditional branches 
/*****************************************************************************/
#include "head.h"
#include "branch.h"

/****************************************************************************/
// Function: conditional(unsigned int inst)
// 
//This function takes an instruction compares it with masks and preforms the coreect operation 
/*****************************************************************************/
void conditional(unsigned int inst)
{
	int8_t newPC = conditional_addr(inst); // makeing the relative address only 8 bits 
	switch(Conditional_op_code(inst)) {
	case c_EQ://zero set 
		if(zero)
			pc += newPC;
		break;
	case c_NE://zero clear
		if(!zero)
			pc += newPC;
		break;
	case c_CS://carry set
		if(carry)
			pc += newPC;
		break;
	case c_CC://carry clear
		if(!carry)
			pc += newPC;
		break;
	case c_MI: //sign set
		if(sign)
			pc += newPC;
		break;
	case c_PL://sign clear
		if(!sign)
			pc += newPC;
		break;
	case c_HI:// carry set and sign clear 
		if(carry && !sign)
			pc += newPC;
		break;
	case c_LS://carry clear or zero set 
		if(!carry || zero)
			pc += newPC;
		break;
	case c_AL://always branch
		pc += newPC;
		break;
	}

	return;
}
/****************************************************************************/
// Function: unConditional(unsigned int inst)
// 
//This function takes an instruction compares it with masks and preforms the coreect operation 
/*****************************************************************************/
void unConditional(unsigned int inst)
{
	int16_t newPC=unCond_offset(inst);


	if(is_unCond_BRA(inst)) {//Always branch
		pc = newPC;
		return;
	}


	if(is_unCond_BRL(inst)) { //Always branch but store the old pc in lr
		lr=pc;
		pc=newPC;
		return;
	}

}

