


#ifndef SOME_FUNCS_AND_DEFS_HPP
#define SOME_FUNCS_AND_DEFS_HPP


#define VM_ADDRESS_SIZE 4
#define ONE_WORD_SIZE 8
#define ONE_BLOCK_SIZE 256
#define STACK_ADDR "f000"
#define LAST_STACK_ADDR "ffff"
#define CODE_SEG_START_ADDR "8000"
#define DATA_SEG_START_ADDR "0000"


namespace learn2024{
	void simpleCharCopy(char source[], char destination[], int size);
	unsigned long int hexToInt(char hex[], int hexSize);

	void intToHex(unsigned long int num, int hexSize, char placeForHex[]);
	bool hexLess(char num1[], char num2[], int size);
	bool hexEqual(char num1[], char num2[], int size);
	void hexAdd(char hex[], int hexSize, int num);
}
#ifdef DEBUG_1233546_CUSTOM_PROJECT
#include "FuncsAndDefs.cpp"
#endif // DEBUG

#endif