/****************************************************************************/
// Author: Kirolous Frouk
// Date  : 4/26/2015
// File Name: loadStore.c
// This file contains  the implementaion of the Load and store instruction
/*****************************************************************************/
#include "head.h"
#include "loadStore.h"

void loadstore(uint16_t inst)
{
	//geting rn and rd
	uint8_t rn = RN(inst);
	uint8_t rd = RD(inst);

	if(get_L_bit(inst))//LOAD
	{
		if(!get_B_bit(inst)){
			pull(rd,reg[rn],0);}
		else{
			pull(rd,reg[rn],1);// Load one byte
		}
	}

	else //Store
	{
		if(!get_B_bit(inst)) {
			push(rd,reg[rn],0);
		}
		else{
			push(rd,reg[rn],1);}
	}

	return;
}