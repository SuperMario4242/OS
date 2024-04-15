


#ifndef SOME_VIRTUAL_MEMORY_HPP
#define SOME_VIRTUAL_MEMORY_HPP
#include "RM.hpp"


namespace learn2024{
	class VirtualMemory {
	private:
		const int memorySz = 256*ONE_BLOCK_SIZE*ONE_WORD_SIZE; // 256*256*8
		char memory[524288];// ONE_WORD_SIZE*256*ONE_BLOCK_SIZE];
	public:
		VirtualMemory();
		void getWord(char address[4], char placeForWord[8]);
		void setWord(char address[4], char word[8]);
		std::string toString(int block)const;
	};
}

#ifdef DEBUG_1233546_CUSTOM_PROJECT
#include "VirtualMemory.cpp"
#endif // DEBUG
#endif

