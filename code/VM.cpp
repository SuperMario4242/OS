#ifndef SOME_VM_CPP
#define SOME_VM_CPP
#include "VM.hpp"


namespace learn2024{
	/*void VM::startMachine(VirtualMemory mem){
		std::cout << "lalala123456\n";
	}*/
	
	void VM::setCpu(CPU *cpu){
		this->cpu = cpu;
	}
	bool VM::runCommand(char word[ONE_WORD_SIZE]){
		std::cout << "pause..";
		char temp[9];
		
		std::cin.getline(temp, 9);
//		>> temp;
		if (temp[0] == 'n'){
			return true;
		}
		for (int i = 0; i < ONE_WORD_SIZE; ++i){
			current.txt[i] = temp[i];
		}// interrupto apdorojimai per SI(!!!)
		
		std::cout << "get command:\n";
		for (int i = 0; i < ONE_WORD_SIZE; ++i){
			std::cout <<  temp[i];
		}
		std::cout << "\n";
		bool needIncrementCounter = true;
		switch (twoLettersToShort(current.txt)) {
			case constTwoLettersToShort("AD"):
				std::cout << "AD registered" << std::endl;
				break;
			case constTwoLettersToShort("SU"):
				std::cout << "SU registered" << std::endl;
				break;
			case constTwoLettersToShort("MU"):
				std::cout << "MU registered" << std::endl;
				break;
			case constTwoLettersToShort("DI"):
				std::cout << "DI registered" << std::endl;
				break;
			case constTwoLettersToShort("PS")://
				if (current.txt[2] == 'H'){
			//		std::cout <<  "third";
					if (current.txt[3] == 'a'){
						this->cpu->commands.cmdPSHa(&current.txt[4]);
					} else {
						this->cpu->commands.cmdPSH(&current.txt[4]);
					}
				} else {
					//to do
				}
				
				std::cout << "PS registered" << std::endl;
				break;
			case constTwoLettersToShort("PO")://
				if (current.txt[2] == 'P'){
					this->cpu->commands.cmdPOP(&current.txt[4]);
				}
				std::cout << "PO registered" << std::endl;
				break;
			case constTwoLettersToShort("TB"):
				std::cout << "TB registered" << std::endl;
				break;
			case constTwoLettersToShort("TH"):
				std::cout << "TH registered" << std::endl;
				break;
			case constTwoLettersToShort("AN"):
				this->cpu->commands.cmdAND();
				std::cout << "AN registered" << std::endl;
				break;
			case constTwoLettersToShort("OR"):
				this->cpu->commands.cmdOR();
				std::cout << "OR registered" << std::endl;
				break;
			case constTwoLettersToShort("XO"):
				this->cpu->commands.cmdXOR();
				std::cout << "XO registered" << std::endl;
				break;
			case constTwoLettersToShort("NO"):
				this->cpu->commands.cmdNOT();
				std::cout << "NO registered" << std::endl;
				break;
			case constTwoLettersToShort("CM"):
				std::cout << "CM registered" << std::endl;
				break;
			case constTwoLettersToShort("JN"):
				std::cout << "JN registered" << std::endl;
				break;
			case constTwoLettersToShort("JA"):
				std::cout << "JA registered" << std::endl;
				break;
			case constTwoLettersToShort("JB"):
				std::cout << "JB registered" << std::endl;
				break;
			case constTwoLettersToShort("DS"):
				this->cpu->commands.cmdDS(&current.txt[3]);
				std::cout << "DS registered" << std::endl;
				break;
			case constTwoLettersToShort("RD"):
				std::cout << "RD registered" << std::endl;
				break;
			case constTwoLettersToShort("HA"):
				std::cout << "HA registered" << std::endl;
				break;
			default:
				std::cout << "nothing registered" << std::endl;
				break;
		}
		
		if (needIncrementCounter){ // <- move to virtual_machine
			hexAdd(this->cpu->registers.PC, VM_ADDRESS_SIZE, 1);
		} else {
			// what to do in that case (?)
		} 
		
		
		return false;
	}
}


#endif // SOME_VM_CPP
