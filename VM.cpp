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
		for (int i = 0; i < 2; ++i){
			current.txt[i] = word[i];
		}// interrupto apdorojimai per SI(!!!)
		
		std::cout << "get command:\n";
		for (int i = 0; i < ONE_WORD_SIZE; ++i){
			std::cout <<  word[i];
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
			case constTwoLettersToShort("PS"):
				std::cout << "PS registered" << std::endl;
				break;
			case constTwoLettersToShort("PO"):
				std::cout << "PO registered" << std::endl;
				break;
			case constTwoLettersToShort("TB"):
				std::cout << "TB registered" << std::endl;
				break;
			case constTwoLettersToShort("TH"):
				std::cout << "TH registered" << std::endl;
				break;
			case constTwoLettersToShort("AN"):
				std::cout << "AN registered" << std::endl;
				break;
			case constTwoLettersToShort("OR"):
				std::cout << "OR registered" << std::endl;
				break;
			case constTwoLettersToShort("XO"):
				std::cout << "XO registered" << std::endl;
				break;
			case constTwoLettersToShort("NO"):
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
		
		std::cout << "pause..";
		char temp;
		std::cin >> temp;
		if (temp == 'n'){
			return true;
		}
		return false;
	}
}


#endif // SOME_VM_CPP
