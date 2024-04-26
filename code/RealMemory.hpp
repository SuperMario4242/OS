


#ifndef SOME_REAL_MEMORY_HPP
#define SOME_REAL_MEMORY_HPP
#include "RM.hpp"


namespace learn2024{
	class RealMemory {
	public:
	//	RealMemory *rmem;
	//	char pagingAddress[8];
		
		const int memorySz = (256 + 256 + 2)*ONE_BLOCK_SIZE*ONE_WORD_SIZE; // 256*256*8
		char memory[1052672];// (256 + 256 + 2)*ONE_BLOCK_SIZE*ONE_WORD_SIZE
	public:
		RealMemory();
		void getWord(char address[8], char placeForWord[8])const;
		void setWord(char address[8], char word[8]);
		std::string toString(char address[ONE_WORD_SIZE], int size)const;
	};
}

#ifdef DEBUG_1233546_CUSTOM_PROJECT
#include "RealMemory.cpp"
#endif // DEBUG
#endif

