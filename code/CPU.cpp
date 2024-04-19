#ifndef SOME_CPU_CPP
#define SOME_CPU_CPP
#include "CPU.hpp"
namespace learn2024{
	int CPU::programCounterSize = 4;
	int CPU::programPointerSize = 8;
	int CPU::stackPointerSize = 4;
	CPU::CPU(){
		CPU(NULL);
	}
	CPU::CPU(VirtualMemory *memory){
		this->commands.cpu = this;
		this->memory = memory;
		//char tmp[programCounterSize+1] = "0000";
		for (int i = 0; i < programCounterSize; ++i){
			this->registers.PC[i] = '0';
		}
		//char tmp2[programPointerSize+1] = "00000000";
		for (int i = 0; i < programPointerSize; ++i){
			this->registers.PTR[i] = '0';
		}
		//char tmp3[stackPointerSize+1] = "0000";
		for (int i = 0; i < stackPointerSize; ++i){
			this->registers.SP[i] = '0';
		}
		this->registers.status.zero = 0;
		this->registers.status.carry = 0;

		this->registers.TI = 0;
		this->registers.PI = 0;
		this->registers.SI = 0;

	}

	std::string CPU::toString()const{

		std::ostringstream oss;
		oss << "CPU Info:\n";
		oss << "Program Counter: ";
		for (int i = 0; i < programCounterSize; ++i)
			oss << (char)(registers.PC[i]);
		oss << "\nProgram Pointer: ";
		for (int i = 0; i < programPointerSize; ++i)
			oss << (char)(registers.PTR[i]);
		oss << "\nStack Pointer: ";
		for (int i = 0; i < stackPointerSize; ++i)
			oss << (char)(registers.SP[i]);
		oss << "\nStatus:\n";
		oss << "   Zero: " << (int)(registers.status.zero) << "\n";
		oss << "   Carry: " << (int)(registers.status.carry) << "\n";
		oss << "Timer Interrupt: " << (int)(registers.TI) << "\n";
		oss << "Program Interrupt: " << (int)(registers.PI) << "\n";
		oss << "System Interrupt: " << (int)(registers.SI) << "\n";
		return oss.str();

	}

	void CPU::Commands::cmdADDs(){
		char tempStackPointer[VM_ADDRESS_SIZE];
	//	SP;
		simpleCharCopy(cpu->registers.SP, tempStackPointer, VM_ADDRESS_SIZE);
		char word1[ONE_WORD_SIZE];
		cpu->memory->getWord(tempStackPointer, word1);
												// TODO add hex check
													// TODO add hex compare
		hexAdd(tempStackPointer, VM_ADDRESS_SIZE, -1); // TODO (TO_CHECK) <-- attention will be required
		
		char word2[ONE_WORD_SIZE];
		cpu->memory->getWord(tempStackPointer, word2);
		
		unsigned long int n1 = hexToInt(word1, ONE_WORD_SIZE);
		unsigned long int n2 = hexToInt(word2, ONE_WORD_SIZE);
		
		unsigned long int result = n1 + n2;
	//	std::cout << "ADDs: " << n1 << " + " << n2 << std::endl;
		if (result < n1){
			cpu->registers.status.carry = 1;
		} else {
			cpu->registers.status.carry = 0;
		}
		if (result == 0){
			cpu->registers.status.zero = 1;
		} else {
			cpu->registers.status.zero = 0;
		}
		intToHex(result, ONE_WORD_SIZE, word1);
		cpu->memory->setWord(cpu->registers.SP, word1);
		
	}
	void CPU::Commands::cmdSUBs(){
		char tempStackPointer[VM_ADDRESS_SIZE];
		simpleCharCopy(cpu->registers.SP, tempStackPointer, VM_ADDRESS_SIZE);
		char word1[ONE_WORD_SIZE];
		cpu->memory->getWord(tempStackPointer, word1);
										// TODO add hex check
													// TODO add hex compare
		hexAdd(tempStackPointer, VM_ADDRESS_SIZE, -1); // TODO (TO_CHECK) <-- attention will be required
		
		char word2[ONE_WORD_SIZE];
		cpu->memory->getWord(tempStackPointer, word2);
		
		unsigned long int n1 = hexToInt(word1, ONE_WORD_SIZE);
		unsigned long int n2 = hexToInt(word2, ONE_WORD_SIZE);
		
		unsigned long int result = n2 - n1;
		
		if (n2 < n1){
			cpu->registers.status.carry = 1;
		} else {
			cpu->registers.status.carry = 0;
		}
		if (result == 0){
			cpu->registers.status.zero = 1;
		} else {
			cpu->registers.status.zero = 0;
		}
		intToHex(result, ONE_WORD_SIZE, word1);
		cpu->memory->setWord(cpu->registers.SP, word1);
	}
	void CPU::Commands::cmdMULs(){
		char tempStackPointer[VM_ADDRESS_SIZE];
		simpleCharCopy(cpu->registers.SP, tempStackPointer, VM_ADDRESS_SIZE);
		char word1[ONE_WORD_SIZE];
		cpu->memory->getWord(tempStackPointer, word1);
										// TODO add hex check
													// TODO add hex compare
		hexAdd(tempStackPointer, VM_ADDRESS_SIZE, -1); // TODO (TO_CHECK) <-- attention will be required
		
		char word2[ONE_WORD_SIZE];
		cpu->memory->getWord(tempStackPointer, word2);
		
		unsigned long int n1 = hexToInt(word1, ONE_WORD_SIZE);
		unsigned long int n2 = hexToInt(word2, ONE_WORD_SIZE);
		
		unsigned long int result = n2 * n1;
		if (n1 != 0 && n2 > ULONG_MAX / n1) {		
			cpu->registers.status.carry = 1;
		} else {
			cpu->registers.status.carry = 0;
		}
		if (result == 0){
			cpu->registers.status.zero = 1;
		} else {
			cpu->registers.status.zero = 0;
		}
		intToHex(result, ONE_WORD_SIZE, word1);
		cpu->memory->setWord(cpu->registers.SP, word1);
	}
	void CPU::Commands::cmdDIVs(){
		char tempStackPointer[VM_ADDRESS_SIZE];
		simpleCharCopy(cpu->registers.SP, tempStackPointer, VM_ADDRESS_SIZE);
		char word1[ONE_WORD_SIZE];
		cpu->memory->getWord(tempStackPointer, word1);
										// TODO add hex check
													// TODO add hex compare
		hexAdd(tempStackPointer, VM_ADDRESS_SIZE, -1); // TODO (TO_CHECK) <-- attention will be required
		
		char word2[ONE_WORD_SIZE];
		cpu->memory->getWord(tempStackPointer, word2);
		
		unsigned long int n1 = hexToInt(word1, ONE_WORD_SIZE);
		unsigned long int n2 = hexToInt(word2, ONE_WORD_SIZE);
		
		unsigned long int resultDivision = n2 / n1;
		unsigned long int resultRemainder = n2 % n1;
		
		/*if (n2 < n1){
			cpu->registers.status.carry = 1;
		} else {
			cpu->registers.status.carry = 0;
		}*/
		if (resultDivision == 0){
			cpu->registers.status.zero = 1;
		} else {
			cpu->registers.status.zero = 0;
		}
		intToHex(resultRemainder, ONE_WORD_SIZE, word1);
		intToHex(resultDivision, ONE_WORD_SIZE, word2);
		cpu->memory->setWord(cpu->registers.SP, word1);
		cpu->memory->setWord(tempStackPointer, word2);
	}
	
	void CPU::Commands::cmdPSHa(char arg[4]){
		// TODO add hex compare
		if (!hexEqual(cpu->registers.SP, LAST_STACK_ADDR, VM_ADDRESS_SIZE)){
		//	
			char wordToPush[ONE_WORD_SIZE];
			cpu->memory->getWord(arg, wordToPush);
			
			hexAdd(cpu->registers.SP, VM_ADDRESS_SIZE, 1);
			cpu->memory->setWord(cpu->registers.SP, wordToPush);
		} else {
			// TODO call interrupt with stack overflow
		}
	}
	void CPU::Commands::cmdPSH (char arg[4]){
		// TODO add hex compare
		if (!hexEqual(cpu->registers.SP, LAST_STACK_ADDR, VM_ADDRESS_SIZE)){
		//	
			char wordToPush[ONE_WORD_SIZE];
			for (int i = 0; i < ONE_WORD_SIZE; ++i){
				if (i < ONE_WORD_SIZE - VM_ADDRESS_SIZE){
					wordToPush[i] = '0';
				} else {
					wordToPush[i] = arg[i - (ONE_WORD_SIZE - VM_ADDRESS_SIZE)];
				}
			}
			
			hexAdd(cpu->registers.SP, VM_ADDRESS_SIZE, 1);
			cpu->memory->setWord(cpu->registers.SP, wordToPush);
		} else {
			// TODO call interrupt with stack overflow
		}
	}
	void CPU::Commands::cmdPOP (char arg[4]){
		// TODO add hex compare
		if (!hexEqual(cpu->registers.SP, LAST_STACK_ADDR, VM_ADDRESS_SIZE)){
		//	
			char wordToPush[ONE_WORD_SIZE];
			cpu->memory->getWord(cpu->registers.SP, wordToPush);
			
			hexAdd(cpu->registers.SP, VM_ADDRESS_SIZE, -1);
			cpu->memory->setWord(arg, wordToPush);
		} else {
			// TODO call interrupt with stack overflow
		}
	}
	
	void CPU::Commands::cmdAND(){
		char tempStackPointer[VM_ADDRESS_SIZE];

		simpleCharCopy(cpu->registers.SP, tempStackPointer, VM_ADDRESS_SIZE);

		char word1[ONE_WORD_SIZE];
		cpu->memory->getWord(tempStackPointer, word1);
		if (isithex(word1,ONE_WORD_SIZE)){
			cpu->registers.SI = 1;
		}
		hexAdd(tempStackPointer, VM_ADDRESS_SIZE, -1); // TODO (TO_CHECK) <-- attention will be required
		
		char word2[ONE_WORD_SIZE];
		cpu->memory->getWord(tempStackPointer, word2);
		if (isithex(word2,ONE_WORD_SIZE)){
			cpu->registers.SI = 1;
		}
		unsigned long int n1 = hexToInt(word1, ONE_WORD_SIZE);
		unsigned long int n2 = hexToInt(word2, ONE_WORD_SIZE);
		
		unsigned long int result = n1&n2;

		intToHex(result, ONE_WORD_SIZE, word1);
		cpu->memory->setWord(cpu->registers.SP, word1);
	}
	void CPU::Commands::cmdOR(){
		char tempStackPointer[VM_ADDRESS_SIZE];

		simpleCharCopy(cpu->registers.SP, tempStackPointer, VM_ADDRESS_SIZE);

		char word1[ONE_WORD_SIZE];
		cpu->memory->getWord(tempStackPointer, word1);
		if (isithex(word1,ONE_WORD_SIZE)){
			cpu->registers.SI = 1;
		}
		hexAdd(tempStackPointer, VM_ADDRESS_SIZE, -1); // TODO (TO_CHECK) <-- attention will be required
		
		char word2[ONE_WORD_SIZE];
		cpu->memory->getWord(tempStackPointer, word2);
		if (isithex(word2,ONE_WORD_SIZE)){
			cpu->registers.SI = 1;
		}
		unsigned long int n1 = hexToInt(word1, ONE_WORD_SIZE);
		unsigned long int n2 = hexToInt(word2, ONE_WORD_SIZE);
		
		unsigned long int result = n1|n2;

		intToHex(result, ONE_WORD_SIZE, word1);
		cpu->memory->setWord(cpu->registers.SP, word1);
	}
	void CPU::Commands::cmdXOR(){
		char tempStackPointer[VM_ADDRESS_SIZE];

		simpleCharCopy(cpu->registers.SP, tempStackPointer, VM_ADDRESS_SIZE);

		char word1[ONE_WORD_SIZE];
		cpu->memory->getWord(tempStackPointer, word1);
		if (isithex(word1,ONE_WORD_SIZE)){
			cpu->registers.SI = 1;
		}
		hexAdd(tempStackPointer, VM_ADDRESS_SIZE, -1); // TODO (TO_CHECK) <-- attention will be required
		
		char word2[ONE_WORD_SIZE];
		cpu->memory->getWord(tempStackPointer, word2);
		if (isithex(word2,ONE_WORD_SIZE)){
			cpu->registers.SI = 1;
		}
		unsigned long int n1 = hexToInt(word1, ONE_WORD_SIZE);
		unsigned long int n2 = hexToInt(word2, ONE_WORD_SIZE);
		
		unsigned long int result = n1^n2;

		intToHex(result, ONE_WORD_SIZE, word1);
		cpu->memory->setWord(cpu->registers.SP, word1);
	}
	void CPU::Commands::cmdNOT(){
		char tempStackPointer[VM_ADDRESS_SIZE];

		simpleCharCopy(cpu->registers.SP, tempStackPointer, VM_ADDRESS_SIZE);

		char word1[ONE_WORD_SIZE];
		cpu->memory->getWord(tempStackPointer, word1);
		if (isithex(word1,ONE_WORD_SIZE)){
			cpu->registers.SI = 1;
		}
		unsigned long int n1 = hexToInt(word1, ONE_WORD_SIZE);;
		
		unsigned long int result = ~n1;

		intToHex(result, ONE_WORD_SIZE, word1);
		cpu->memory->setWord(cpu->registers.SP, word1);
	}
	
	
	void CPU::Commands::cmdCMP (){
		char tmp[ONE_WORD_SIZE];
		cpu->memory->getWord(cpu->registers.SP, tmp);
		cmdSUBs();
		cpu->memory->setWord(cpu->registers.SP, tmp);
		
	}
	void CPU::Commands::cmdJMP (char arg[4]){
		
		if(isithex(arg,4)){
			simpleCharCopy(arg, cpu->registers.PC, VM_ADDRESS_SIZE);

		}
		else{
			std::cout<<"Not a hex "<<std::endl;
		}
				

	}
	void CPU::Commands::cmdJMPB(char arg[4]){

		if(isithex(arg,4)){
			if (cpu->registers.status.carry){
				cmdJMP(arg);
			}

		}
		else{
			std::cout<<"Not a hex "<<std::endl;
		}
		
			
		
	}
	void CPU::Commands::cmdJMPE(char arg[4]){

		if(isithex(arg,4)){
			if (cpu->registers.status.zero){
				cmdJMP(arg);
			}

		}
		else{
			std::cout<<"Not a hex "<<std::endl;
		}
		
		
	}


	void CPU::Commands:: cmdJAE(char arg[4]){
		if(isithex(arg,4)){
			if (!cpu->registers.status.carry){
				cmdJMP(arg);
			}

		}
		else{
			//TODO
		}

			
	}


	void CPU::Commands:: cmdJNE(char arg[4]){
		if(isithex(arg,4)){
			if (!cpu->registers.status.zero){
				cmdJMP(arg);
			}

		}
		else{
			std::cout<<"Not a hex "<<std::endl;
		}
		
	}

	void CPU::Commands:: cmdJBE(char arg[4]){
		if(isithex(arg,4)){
			if (cpu->registers.status.zero || cpu->registers.status.carry){
				cmdJMP(arg);
			}

		}
		else{
			std::cout<<"Not a hex "<<std::endl;
		}

		
	}
	

	void CPU::Commands:: cmdJMPA(char arg[4]){
		if(isithex(arg,4)){
			if (!cpu->registers.status.carry && !cpu->registers.status.zero){
				cmdJMP(arg);
			}

		}
		else{
			std::cout<<"Not a hex "<<std::endl;
		}
		
	}

	
	
	
	void CPU::Commands::cmdDS (char arg[5]){
	//	char tmp[ONE_WORD_SIZE];
		unsigned long int addrStart = hexToInt(arg, VM_ADDRESS_SIZE);
		char bias = hexToInt(&arg[4], 1);
		char stack[ONE_WORD_SIZE];
		cpu->memory->getWord(cpu->registers.SP, stack);
		unsigned long int limit = hexToInt(stack, ONE_WORD_SIZE);
		std::cout << "in DS limit: " << limit << "\n";
		char currentWord[ONE_WORD_SIZE];
		unsigned long int currentCharacterAddr = addrStart + bias;
		cpu->memory->getWord(arg, currentWord);
		if (bias < ONE_WORD_SIZE){
			for (int k = 0 + bias; k < ONE_WORD_SIZE && currentCharacterAddr < addrStart + bias + limit; ++k){
				std::cout << currentWord[k];
				++currentCharacterAddr;
			}
		} else {
			hexAdd(arg, VM_ADDRESS_SIZE, 1);
			cpu->memory->getWord(arg, currentWord);
			for (int k = 0 + bias - ONE_WORD_SIZE; k < ONE_WORD_SIZE && currentCharacterAddr < addrStart + bias + limit; ++k){
				std::cout << currentWord[k];
				++currentCharacterAddr;
			}
		}
		while (currentCharacterAddr < addrStart + bias + limit){
			hexAdd(arg, VM_ADDRESS_SIZE, 1);
			cpu->memory->getWord(arg, currentWord);
			for (int k = 0; k < ONE_WORD_SIZE && currentCharacterAddr < addrStart + bias + limit; ++k){
				std::cout << currentWord[k];
				++currentCharacterAddr;
			}
		}
		std::cout << std::endl;
		return;

	}
	
	
}
/*
std::string CPU::programCounterToString()const{
	std::ostringstream temp;
	for (int i = 0; i < CPU::programCounterSize; ++i){
		temp << this->programCounter[i];
	}
	return temp.str();
}
*/

#endif // SOME_CPU_CPP
