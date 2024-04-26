#ifndef SOME_VIRTUAL_MEMORY_CPP
#define SOME_VIRTUAL_MEMORY_CPP
#include "VirtualMemory.hpp"
//#include "FuncsAndDefs.cpp"

namespace learn2024{
	VirtualMemory::VirtualMemory(RealMemory *rmem, const char pagingBlock[ONE_WORD_SIZE]){
		this->realMemory = rmem;
		for (int i = 0; i < ONE_WORD_SIZE; ++i){
			this->pagingAddress[i] = pagingBlock[i];
		}
		/*
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
		}*/
		
	}
//	void VirtualMemory::setVirtualBlockStart
	void VirtualMemory::getWord(char address[VM_ADDRESS_SIZE], char placeForWord[ONE_WORD_SIZE])const{
		long int blockNr = hexToInt(address, 2);
		long int wordInBlockNr = hexToInt(&address[2], 2);
		if (this->pagingAddress[2] == '1'){
			cout << "problem: paging block in SWAP \n";
			int a = 2/0;
		}
		char tmp[ONE_WORD_SIZE];
		simpleCharCopy(this->pagingAddress, tmp, ONE_WORD_SIZE);
		
		hexAdd(tmp, ONE_WORD_SIZE, blockNr);
	
		this->realMemory->getWord(tmp, tmp);
		
		
		if (tmp[2] == '1'){
			cout << "problem: needed block in SWAP \n";
			int a = 2/0;
		}
		hexAdd(tmp, ONE_WORD_SIZE, wordInBlockNr);
		
		this->realMemory->getWord(tmp, placeForWord);
		/*cout << "O:";
		for (int i = 0; i < ONE_WORD_SIZE; ++i){
			cout << placeForWord[i];
		}
		cout << endl;*/
	/*	
		unsigned long int addr = hexToInt(address, VM_ADDRESS_SIZE)*ONE_WORD_SIZE;
		if (addr+7 < memorySz)
			for (int i = 0; i < ONE_WORD_SIZE; ++i){
				placeForWord[i] = memory[addr+i];
			} */
		
	}
	void VirtualMemory::setWord(char address[VM_ADDRESS_SIZE], char word[ONE_WORD_SIZE]){
		long int blockNr = hexToInt(address, 2);
		long int wordInBlockNr = hexToInt(&address[2], 2);
		if (this->pagingAddress[2] == '1'){
			cout << "problem: paging block in SWAP \n";
			int a = 2/0;
		}
		char tmp[ONE_WORD_SIZE];
		simpleCharCopy(this->pagingAddress, tmp, ONE_WORD_SIZE);
		
		hexAdd(tmp, ONE_WORD_SIZE, blockNr);
		this->realMemory->getWord(tmp, tmp);
		
		if (tmp[2] == '1'){
			cout << "problem: needed block in SWAP \n";
			int a = 2/0;
		}
		hexAdd(tmp, ONE_WORD_SIZE, wordInBlockNr);
		
		this->realMemory->setWord(tmp, word);
		/*
		unsigned long int addr = hexToInt(address, VM_ADDRESS_SIZE)*ONE_WORD_SIZE;
		if (addr+7 < memorySz)
			for (int i = 0; i < ONE_WORD_SIZE; ++i){
				memory[addr+i] = word[i];
			}*/
	}
	void VirtualMemory::moveBlock(char oldAddress[ONE_WORD_SIZE], char newAddress[ONE_WORD_SIZE], int blockNr){
		
		if (newAddress[6] == '0' && newAddress[7] == '0' && oldAddress[6] == '0' && oldAddress[7] == '0'){
			/*for (int i = 0; i < 8; ++i){
				cout << oldAddress[i];
			}
			cout << " to ";
			for (int i = 0; i < 8; ++i){
				cout << newAddress[i];
			}
			cout << endl;*/
			char curOldAddress[] = "00000000";
			char curNewAddress[] = "00000000";
			simpleCharCopy(oldAddress, curOldAddress, ONE_WORD_SIZE);
			simpleCharCopy(newAddress, curNewAddress, ONE_WORD_SIZE);
			char tmp[] = "00000000";
			unsigned long int oldBlockID = hexToInt(oldAddress, ONE_WORD_SIZE-2);
			unsigned long int newBlockID = hexToInt(newAddress, ONE_WORD_SIZE-2);
		//	if (this->realMemory->memory[newBlockID] == '0'){
				for (int i = 0; i < ONE_BLOCK_SIZE; ++i){
					this->realMemory->getWord(curOldAddress, tmp);
					this->realMemory->setWord(curNewAddress, tmp);
					hexAdd(curOldAddress, ONE_WORD_SIZE, 1);
					hexAdd(curNewAddress, ONE_WORD_SIZE, 1);
				}
				simpleCharCopy(this->pagingAddress, tmp, ONE_WORD_SIZE);
				
				hexAdd(tmp, ONE_WORD_SIZE, blockNr);
			//	tmp[0] = 'L';
			//	tmp[1] = 'A';
				this->realMemory->setWord(tmp, newAddress);
				cout << "move block " << blockNr << " from " << oldAddress << " to " << newAddress << " pagingChanged at: " << tmp << endl;
			
			//	this->realMemory->memory[newBlockID] = '1';
			//	this->realMemory->memory[oldBlockID] = '0';
		//	} else {
			/*	cout << "problem: bad adress for new block.";
				int a = 2/0;*/
		//	}
			
		} else {
			cout << "problem: bad adresses for blocks.";
			cout << "addressOld:";
			for (int i = 0; i < 8; ++i){
				cout << oldAddress[i];
			}
			cout << "addressNew:";
			for (int i = 0; i < 8; ++i){
				cout << newAddress[i];
			}
			int a = 2/0;
		}
		
		
	}
	
	std::string VirtualMemory::toString(char address[VM_ADDRESS_SIZE], int size)const{
	//	unsigned long int addr = block*ONE_BLOCK_SIZE*ONE_WORD_SIZE;
		std::ostringstream oss;
	//	oss << "Virtual memory block " << block << " Info:\n";
		for (int i = 0; i < size; ++i){
			for (int k = 0; k < VM_ADDRESS_SIZE; ++k){
				oss << address[k];
			}
			oss << "|";
			char tmp[ONE_WORD_SIZE];
			this->getWord(address, tmp);
			hexAdd(address, VM_ADDRESS_SIZE, 1);
			
			for (int k = 0; k < ONE_WORD_SIZE; ++k){
				oss << tmp[k];
			}
			oss << std::endl;
			
		}
		return oss.str();

	}
}


#endif // SOME_VIRTUAL_MEMORY_CPP
