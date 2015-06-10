/****************************************************************************/
// Author: Kirolous Frouk
// Date  : 4/1/2015
// File Name: data.c
// This file contains  the implementaion of the data instruction
/*****************************************************************************/
#include "head.h"
#include "data.h"
/****************************************************************************/
// Function: void data(unsigned int inst)
// 
//This function takes an instruction compares it with masks and preforms the coreect operation 
/*****************************************************************************/
void data(unsigned int inst)
{
	//get rn and rd 
	uint8_t rd = RD(inst);
	uint8_t rn = RN(inst);
	unsigned int operation = d_operation(inst); //geting the data operation 
	int i;
	char tmp;//Used for SXB
	switch(operation)
	{
	case d_and:
		alu=reg[rd] & reg[rn];
		set_sz_flags();
		reg[rd]=alu;
		
		break;
	case d_eor:
		alu=reg[rd] ^ reg[rn];
		set_sz_flags();
		reg[rd]=alu;
		
		break;
	case d_sub:
		alu=reg[rd]+(~reg[rn])+1; 
		set_flags(reg[rd],reg[rn]);
		reg[rd]=alu;
		break;
	case d_sxb:
		tmp = reg[rn];
		 alu = ((signed long)tmp);  
		  set_sz_flags();
         reg[rd] = alu;
		
		break;
	case d_add:
		alu=reg[rd] + reg[rn];
		set_flags(reg[rd],reg[rn]);
		reg[rd]=alu;
		
		break;
	case d_adc:
		alu = reg[rd]+reg[rn]+ carry;
		set_flags(reg[rd],reg[rn]);
		 reg[rd] = alu;
		 
		break;
	case d_lsr:
		alu=reg[rd] >> reg[rn]-1;
		 if(getLsb(alu)){
			 carry=1;}

		 alu = (alu >> 1);
		 set_sz_flags();
		reg[rd]=alu;
		
		break;
	case d_lsl:
		alu = reg[rd] << reg[rn] - 1;
		if(getMsb(alu)){
			carry=1;}
		set_sz_flags();
		reg[rd]=alu;
		
		break;
	case d_tst:
		alu=reg[rd] & reg[rn];
		set_sz_flags();
		break;
	case d_teq:
		alu=reg[rd] ^ reg[rn];
		set_sz_flags();
		break;
	case d_cmp:
		alu=reg[rd] - (~reg[rn])+1;
		set_flags(reg[rd],reg[rn]);
		break;
	case d_ror:
		alu = reg[rd];		
		for(i = 0; i < reg[rn]; i++)
			{
				 if(getLsb(alu))
                carry=1;

				 alu = (alu >> 1);
				carry = reg[rd] & 0x0001;
				if(carry)
					alu |= msbMask;
			}
		set_sz_flags();
			reg[rd] = alu;
			
		break;
	case d_orr:
		alu=reg[rd] | reg[rn];
		set_sz_flags();
		reg[rd]=alu;
		
		break;
	case d_mov:
		alu=reg[rn];
		set_sz_flags();
		reg[rd]=alu;
		
		break;
	case d_bic:
		alu=reg[rd] & (~reg[rn]);
		set_sz_flags();
		reg[rd]=alu;
		
		break;
	case d_mvn:
		alu=(~reg[rn]);
		set_sz_flags();
		reg[rd]=alu;
		
		break;

	default:
				
			perror("Data switch failed");
	
		break;
	}


}