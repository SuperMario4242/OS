


#ifndef SOME_VIRTUAL_MEMORY_HPP
#define SOME_VIRTUAL_MEMORY_HPP
#include "RM.hpp"


namespace learn2024{
	class VirtualMemory {
	public:
		RealMemory *realMemory;
		char pagingAddress[8];
		
	//	const int memorySz = 256*ONE_BLOCK_SIZE*ONE_WORD_SIZE; // 256*256*8
	//	char memory[524288];// ONE_WORD_SIZE*256*ONE_BLOCK_SIZE];
	public:
		VirtualMemory(RealMemory *rmem, const char pagingBlock[ONE_WORD_SIZE]);
		void getWord(char address[4], char placeForWord[8]) const;
		void setWord(char address[4], char word[8]);
		void moveBlock(char oldAddress[ONE_WORD_SIZE], char newAddress[ONE_WORD_SIZE], int blockNr);
		std::string toString(char address[VM_ADDRESS_SIZE], int size)const;
	};
}

#ifdef DEBUG_1233546_CUSTOM_PROJECT
#include "VirtualMemory.cpp"
#endif // DEBUG
#endif

