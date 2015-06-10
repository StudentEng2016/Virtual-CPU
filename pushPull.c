/****************************************************************************/
// Author: Kirolous Frouk
// Date  : 4/27/2015
// File Name: pushPull.c
// This file contains  the implementaion of the Push  and Pull instruction
/*****************************************************************************/
#include "pushPull.h"
#include "head.h"
uint8_t reg_mask_set[] = {  //Masks sed to check which bits are set in the instruction
	PP_REG_1, PP_REG_2,
	PP_REG_3, PP_REG_4,
	PP_REG_5, PP_REG_6,
	PP_REG_7, PP_REG_8,
	PP_REG_9, PP_REG_10,
	PP_REG_11, PP_REG_12,
	PP_REG_13, PP_REG_14,
	PP_REG_15, PP_REG_16
};
void pushPull(uint16_t inst) 
{
	int8_t i, j;              //counters used in loops
	uint8_t set_reg = PP_GET_REG(inst); 
	/*
	PUSH
	*/
	if((!PP_L_bit(inst))&& ( PP_H_bit(inst) ) ) 
	{
		if(PP_R_bit(inst)){//push lr
			sp = (sp - sizeof(sp));
			push(lr,sp,0);}

		if(PP_H_bit(inst)){//Push high registers 
			for(i = HIGH_REG_MAX, j = 0; i >= (LOW_REG+1); i--)
				if(reg_mask_set[j++] & set_reg) {
					sp = (sp - sizeof(sp));
					push(i,sp,0);
				}}
	}	

	else if ((!PP_H_bit(inst)) && (!PP_L_bit(inst) )){//Push lower registers 
		if(PP_R_bit(inst)){
			sp = (sp - sizeof(sp));
			push(lr,sp,0);}
		for(i = LOW_REG; i >= 0; i--){
			if(reg_mask_set[i] & set_reg) {
				sp = (sp - sizeof(sp));
				push(i,sp,0);
			}
		}
	}

	/*
	PULL
	*/
	else if((PP_L_bit(inst) ) && (PP_H_bit(inst))) {
		if(PP_R_bit(inst))//pull PC
		{
			pull(pc,sp,0);
			sp = (sp + sizeof(sp));
		}
		if(PP_H_bit(inst))//PULL High registers
		{
			j = HIGH_REG_MAX;
			for(i = LOW_REG+1  ; i <= HIGH_REG_MAX; i++)
			{
				if(reg_mask_set[j] & set_reg) 
				{
					pull(i,sp,0);
					sp = (sp + sizeof(uint32_t));
				}
				j= j-1;
			}
		}
	}
	else if ((PP_L_bit(inst) ) &&(!PP_H_bit(inst) ))//Pull Low registers
	{	
		if(PP_R_bit(inst))//PUll pc
		{
			pull(pc,sp,0);
			sp = (sp + sizeof(sp));
		}
		for(i = 0; i <= LOW_REG; i++)
		{
			if(reg_mask_set[i] & set_reg)
			{
				pull(i,sp,0);
				sp = (sp + sizeof(sp));
			}
		}
	}



	return;
}

/*
Push
If oneByte =1 push one byte
if oneByte =0 push 4 bytes
reg_num = what register to use
mem_addr = what memory address to use
*/
void push(uint8_t reg_num, uint32_t mem_addr,uint8_t oneByte) 
{
	if(oneByte == 0){
		int i;
		MAR =mem_addr;
		memory[MAR +0] =BYTE_4(reg[reg_num]);
		memory[MAR +1] =BYTE_3(reg[reg_num]);
		memory[MAR +2] =BYTE_2(reg[reg_num]);
		memory[MAR +3] =BYTE_1(reg[reg_num]);
	}
	else if(oneByte == 1){//Push one byte 
		MAR =mem_addr;
		memory[MAR +0] =BYTE_1(reg[reg_num]);
	}
	return;
}
/*
Pull
If oneByte =1 pull one byte
if oneByte =0 pull 4 bytes
reg_num = what register to use
mem_addr = what memory address to use
*/
void pull(uint8_t reg_num, uint32_t mem_addr,uint8_t oneByte)
{	

	if(oneByte ==0){
		MAR =mem_addr;
		reg[reg_num]=(memory[MAR +0]) ;
		reg[reg_num]=(reg[reg_num] << BYTE) ;

		reg[reg_num]|=(memory[MAR +1]) ;
		reg[reg_num]=(reg[reg_num] << BYTE) ;

		reg[reg_num]|=(memory[MAR +2]) ;
		reg[reg_num]=(reg[reg_num] << BYTE) ;

		reg[reg_num] |= (memory[MAR +3] );
		;}
	else if (oneByte ==1 )//Pull one byte
	{
		MAR =mem_addr;
		reg[reg_num] = (memory[MAR +0] );
	}


	return;
}