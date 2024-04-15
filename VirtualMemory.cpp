#ifndef SOME_VIRTUAL_MEMORY_CPP
#define SOME_VIRTUAL_MEMORY_CPP
#include "VirtualMemory.hpp"
#include "FuncsAndDefs.cpp"

namespace learn2024{
	VirtualMemory::VirtualMemory(){
		for (unsigned long int  b = 0; b < 256; ++b){
			for (unsigned long int  i = 0; i < ONE_BLOCK_SIZE; ++i){
				for (unsigned long int  k = 0; k < ONE_WORD_SIZE; ++k){
					unsigned long int addr = b*ONE_BLOCK_SIZE*ONE_WORD_SIZE + i*ONE_WORD_SIZE + k;
					if (b == 255){
						this->memory[addr] = 'L';
					} else 
						if (k < ONE_WORD_SIZE/2){
							this->memory[addr] = '_';
						} else {
							this->memory[addr] = ('0' + (b % 10));
						}
					
				}
			}
		}
		
	}
	void VirtualMemory::getWord(char address[VM_ADDRESS_SIZE], char placeForWord[ONE_WORD_SIZE]){
		unsigned long int addr = hexToInt(address, VM_ADDRESS_SIZE)*ONE_WORD_SIZE;
		if (addr+7 < memorySz)
			for (int i = 0; i < ONE_WORD_SIZE; ++i){
				placeForWord[i] = memory[addr+i];
			}
		
	}
	void VirtualMemory::setWord(char address[VM_ADDRESS_SIZE], char word[ONE_WORD_SIZE]){
		unsigned long int addr = hexToInt(address, VM_ADDRESS_SIZE)*ONE_WORD_SIZE;
		if (addr+7 < memorySz)
			for (int i = 0; i < ONE_WORD_SIZE; ++i){
				memory[addr+i] = word[i];
			}
	}
	std::string VirtualMemory::toString(int block)const{
		unsigned long int addr = block*ONE_BLOCK_SIZE*ONE_WORD_SIZE;
		std::ostringstream oss;
		oss << "Virtual memory block " << block << " Info:\n";
		for (int i = 0; i < ONE_BLOCK_SIZE; ++i){
			oss << "|" << i << "|";
			for (int k = 0; k < ONE_WORD_SIZE; ++k){
				oss << memory[addr+(i*ONE_WORD_SIZE)+k];
			}
			oss << std::endl;
			
		}
		return oss.str();

	}
}


#endif // SOME_VIRTUAL_MEMORY_CPP
