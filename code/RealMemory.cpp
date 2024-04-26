#ifndef SOME_REAL_MEMORY_CPP
#define SOME_REAL_MEMORY_CPP
#include "RealMemory.hpp"
//#include "FuncsAndDefs.cpp"

namespace learn2024{
	RealMemory::RealMemory(){
		for (unsigned long int  b = 0; b < this->memorySz/256/8; ++b){
		//	cout << "hm.." << b  << endl;
			for (unsigned long int  i = 0; i < ONE_BLOCK_SIZE; ++i){
				for (unsigned long int  k = 0; k < ONE_WORD_SIZE; ++k){
					unsigned long int addr = b*ONE_BLOCK_SIZE*ONE_WORD_SIZE + i*ONE_WORD_SIZE + k;
					
					if (k < ONE_WORD_SIZE/2){
						this->memory[addr] = '_';
					} else {
						this->memory[addr] = '0';
					}
					
				}
		//		cout << "b:" << b << "i." << i  << endl;
			}
		//	cout << "llll" << b  << endl;
		}
		
	}
	void RealMemory::getWord(char address[ONE_WORD_SIZE], char placeForWord[ONE_WORD_SIZE])const{
		unsigned long int addr = hexToInt(address, ONE_WORD_SIZE)*ONE_WORD_SIZE;
		if (addr+7 < memorySz)
			for (int i = 0; i < ONE_WORD_SIZE; ++i){
				placeForWord[i] = memory[addr+i];
			}
		
	}
	void RealMemory::setWord(char address[ONE_WORD_SIZE], char word[ONE_WORD_SIZE]){
		unsigned long int addr = hexToInt(address, ONE_WORD_SIZE)*ONE_WORD_SIZE;
		if (addr+7 < memorySz)
			for (int i = 0; i < ONE_WORD_SIZE; ++i){
				memory[addr+i] = word[i];
			}
	}
	/*std::string RealMemory::toString(int block)const{
		unsigned long int addr = block*ONE_BLOCK_SIZE*ONE_WORD_SIZE;
		std::ostringstream oss;
		oss << "Real memory block " << block << " Info:\n";
		for (int i = 0; i < ONE_BLOCK_SIZE; ++i){
			oss << "|" << i << "|";
			for (int k = 0; k < ONE_WORD_SIZE; ++k){
				oss << memory[addr+(i*ONE_WORD_SIZE)+k];
			}
			oss << std::endl;
			
		}
		return oss.str();

	}*/
	std::string RealMemory::toString(char address[ONE_WORD_SIZE], int size)const{
	//	unsigned long int addr = block*ONE_BLOCK_SIZE*ONE_WORD_SIZE;
		std::ostringstream oss;
	//	oss << "Virtual memory block " << block << " Info:\n";
		for (int i = 0; i < size; ++i){
			for (int k = 0; k < ONE_WORD_SIZE; ++k){
				oss << address[k];
			}
			oss << "|";
			char tmp[ONE_WORD_SIZE];
			this->getWord(address, tmp);
			hexAdd(address, ONE_WORD_SIZE, 1);
			
			for (int k = 0; k < ONE_WORD_SIZE; ++k){
				oss << tmp[k];
			}
			oss << std::endl;
			
		}
		return oss.str();

	}
}


#endif // SOME_REAL_MEMORY_CPP
