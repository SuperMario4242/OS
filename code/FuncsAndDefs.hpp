


#ifndef SOME_FUNCS_AND_DEFS_HPP
#define SOME_FUNCS_AND_DEFS_HPP


#define VM_ADDRESS_SIZE 4
#define ONE_WORD_SIZE 8
#define ONE_BLOCK_SIZE 256
#define STACK_ADDR "f000"
#define LAST_STACK_ADDR "ffff"
#define CODE_SEG_START_ADDR "8000"
#define DATA_SEG_START_ADDR "0000"

#define CD_SRC_USER_MEM 1
#define CD_SRC_SWAP 2
#define CD_SRC_KEYBOARD 3
#define CD_SRC_SUPERVISOR 4
#define CD_SRC_HDD 5

#define CD_DES_USER_MEM 1
#define CD_DES_SWAP 2
#define CD_DES_CONSOLE 3
#define CD_SRC_SUPERVISOR 4

#define PI_WRITE_TO_CONSOLE_CODE 2
#define PI_READ_FROM_KEYBOARD 1


namespace learn2024{
	void simpleCharCopy(char source[], char destination[], int size);
	unsigned long int hexToInt(char hex[], int hexSize);
//	bool isithex(char num[8],int size );
	
	void intToHex(unsigned long int num, int hexSize, char placeForHex[]);
	bool hexLess(char num1[], char num2[], int size);
	bool hexEqual(char num1[], char num2[], int size);
	void hexAdd(char hex[], int hexSize, int num);
	bool isithex(char num[], int size);
}
#ifdef DEBUG_1233546_CUSTOM_PROJECT
#include "FuncsAndDefs.cpp"
#endif // DEBUG

#endif