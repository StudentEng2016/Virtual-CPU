/****************************************************************************/
// Author: Kirolous Frouk
// Date  : 1/26/2015
// File Name: main.c
// This file contains Cleanstdin,go,loadfile,main,memdump ,memory Modify ,Prompt ,Write file
/*****************************************************************************/
#include "head.h"

/*
Main function is only used to call propmpt
*/
int main()
{
	printf("Name:  Kirolous Frouk\t\tMemory:  16k Bytes\n");
	prompt();
}
/*
Since fflush could not flush stdin ,this wa an alterneative
*/
void clean_stdin(void)
{
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}
/*
Executes in a loop until athe stop instruction is found 
*/
void go()
{
	while(!stop)
	{
		fetch(memory);
	}
}
/*
Main menu of the program
*/
void prompt()
{
	char input[128];
	char input2[128];
	unsigned value1,value2,value3; 
	unsigned int filelen=NULL;
	char PromptInput=NULL;
	zeroAll();//reset the variables when program starts 
	printf("d\tdump memory\ng\tgo - run the entire program\nl\tload a file into memory	(Allows you to specify the file name.)\nm\tmemory modify\nq\tquit\nr\tdisplay registers\nt\ttrace - execute one instruction \nw\twrite file\nz\treset all registers to zero\n?, h\tdisplay list of commands\n\n");
	while (1)
	{	
		printf("KiroPrompt$>");
		scanf(" %c",&PromptInput);
		PromptInput=tolower(PromptInput);//Case insensitive
		switch(PromptInput)
		{
		case 'd':
			printf("Please input an offset:\t");
			clean_stdin();
			fgets(input,sizeof(input)-1,stdin);
			sscanf(input,"%x ",&value1);
			printf("Please input length of dump:\t");
			fgets(input2,sizeof(input2)-1,stdin);
			sscanf(input2,"%x ",&value2);
			MemDump(memory,value1 ,value2);
			break;
		case 'g':
				go();
				printf("Program has executed \n");
			break;
		case 'l':
			filelen=LoadFile(memory,memorySize);
			printf("The amount of bytes read are in decimal:%d\n",filelen);
			printf("The amount of bytes read are in hex:%x\n",filelen);
			break;
		case 'm':
			printf("Please input an offset:\t");
			clean_stdin();
			fgets(input,sizeof(input)-1,stdin);
			sscanf(input,"%x",&value3);
			memoryModifiy(memory,value3);
			break;
		case 'q':
			return ;
			break;
		case 'r':
			printReg();
			break;
		case 't':
			trace();
			break;
		case 'w':
			WriteFile(memory);
			break;
		case 'z':
			zeroAll();
			break;
		case 'h':
		case '?':
			printf("d\tdump memory\ng\tgo - run the entire program\nl\tload a file into memory	(Allows you to specify the file name.)\nm\tmemory modify\nq\tquit\nr\tdisplay registers\nt\ttrace - execute one instruction \nw\twrite file\nz\treset all registers to zero\n?, h\tdisplay list of commands\n\n");
			break;
		default:
			printf("Invalid option \n");
			break;

		}
	}


}
/*
Writes memory in to a file . the amount of bytes is specified by the user 
*/
void WriteFile(void * memory)
{
	FILE *f;
	char PromptInput[128];
	int Bytes;
	clean_stdin();
	printf("Please enter a filename: ");
	fgets(PromptInput,sizeof(PromptInput),stdin) ;
	PromptInput[strlen(PromptInput)-1]='\0';
	printf("\nPlease enter # of bytes to write: ");
	scanf(" %d",&Bytes);
	clean_stdin();
	if (Bytes>memorySize)//Checks if the user is trying to write more than memory 
	{
		printf("Number of bytes is greater than memory\n *****File was not writen*****\n ");
		return;
	}
	if( Bytes < 0 )//Checks for an invalid value 
	{
		printf("File was not writen user entered an invalid value\n");
		return;
	}
	f = fopen(PromptInput, "wb");//Opens the file in byte mode 
	if (f == NULL)  { printf("Error opening file!\n"); perror("WriteFile");}
	fwrite(memory , 1 , Bytes ,f );
	fclose(f);
	return;
}
/*
Loads content of a file in memory 
*/
int LoadFile(void * memory, unsigned int max)
{
	FILE *fileptr;
	char name[128];
	char choice=NULL;//choice for read mode 
	unsigned int filelen;
	unsigned int Afilelen;//Actual file length
	clean_stdin();
	printf("Please enter a filename:");
	fgets(name,sizeof(name),stdin);
	name[strlen(name)-1]='\0';
	if((fileptr = fopen(name,"rb")) == NULL){
		printf("*******Error opening file*******\n");
		perror("LoadFile");
		return 0;
	}
	fseek(fileptr, 0, SEEK_END);  //Find end of file
	Afilelen = ftell(fileptr);  
	fseek(fileptr, 0, SEEK_SET);         // Jump back to the beginning of the file*/
	fread(memory, max, 1, fileptr); // Read in the entire file
	filelen = ftell(fileptr);  
	if (Afilelen>max)
	{
		printf("\n****************The file was truncated********************\n");
	}
	fclose(fileptr); // Close the file
	return filelen; 
}
/*
displays memory .The user chosses an ofset and lenght of dump 
*/
void MemDump(void *memptr, unsigned offset, unsigned length)
{
	unsigned int counter=0;
	unsigned int count_2=0;
	unsigned int row_length = 16;
	printf("**********************************Memory Dump********************************\n");
	if (offset+length >memorySize)
	{
		printf("Cannot dump .Invalid value\n");// stop larger than mem dumps
		return;
	}
	for(counter = offset; counter < (offset + length); counter += row_length) 
	{
		/******************************************************** Prints hex data*************************************/
		printf("%4.4x\t", counter);


		for(count_2 = counter; count_2 < (counter + row_length); count_2++) 
		{
			printf("%2.2x ", *((unsigned char *) memptr + count_2));
			if(count_2 == (offset + length))
				break;
		}
		/******************************************************** Prints hex end *************************************/

		printf("\n\t");
		/******************************************************** Prints mem*************************************/
		for(count_2 = counter; count_2 < (counter + row_length); count_2++)
		{
			if(isprint((int) *((unsigned char *) memptr + count_2)))
			{
				printf(" %c ", *((unsigned char *) memptr + count_2));
			}
			else
				printf(" . ");
			/******************************************************** Prints mem end*************************************/

			if(count_2 == (offset + length))
				break;
		}

		printf("\n");


		if(count_2 == length) //ends the function
			break;
	}
	printf("************************************END*************************************\n");
	return;

}
/*
Modifing memory 
the user enters an offset
the user is not allowed to enter any thing but a hex digit 
*/
void memoryModifiy(void *memory,unsigned int offset)
{
	unsigned int value=0;
	unsigned int temp_value=0;
	unsigned int counter = offset;
	unsigned int count=0;
	unsigned int count2=0;
	char input[10];
	unsigned int buff;
	printf("**********************Memory Modify ENTER \".\" TO EXIT*************************\n");
	while(value !='.')
	{
		printf("%04x %02x>\t", counter,*((unsigned char *) memory + counter));
		//clean_stdin();
		fgets(input,4,stdin);
		input[strlen(input)-1]='\0';

		if(strcmp(input, ".") == 0){
			return;
		}
		if(counter > memorySize)
		{
			printf("Cannot modify memory above 4000H\n");
			return;
		}

		for(count2=0;input[count2]!='\0';count2++){count++;}	 
		if(count==1)
		{
			if((isxdigit (input[0])!=0 )){
				sscanf(input, "%2x", &buff);
				*((unsigned char *) memory + counter) = ((unsigned char) buff );

				counter++;
			}
		}
		else if(count==2)
		{

			count=0;

			if((isxdigit (input[0])!=0 )&& (!isxdigit(input[1]!=0 )))
			{  
				sscanf(input, "%2x", &buff);
				*((unsigned char *) memory + counter) = ((unsigned char) buff );

				counter++;
			}

			else
			{				
				printf("Invalid input was entered please try again\n");		
			}
		}
		else
		{
			count=0;
			printf("Invalid input was entered please try again\n");		
		}

	}
	return;
}


