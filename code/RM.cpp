#ifndef SOME_RM_CPP
#define SOME_RM_CPP
#include "RM.hpp"


namespace learn2024{
	//void RM::initialize(){
//		
//	}
	RM::RM(CPU *cpu, VirtualMemory *virtual_memory, VM *virtual_machine){
		this->cpu = cpu;
		this->virtual_memory = virtual_memory;
		this->virtual_machine = virtual_machine;
		virtual_machine->setCpu(cpu);
	}
	void RM::initialize(){
		char dataCurrent[] = DATA_SEG_START_ADDR;
		char data[3][9] = {"Enter A:",
							"Enter B:",
							"A + B = "};
		for (int i = 0; i < 3; ++i){
			virtual_memory->setWord(dataCurrent, data[i]);
			hexAdd(dataCurrent, VM_ADDRESS_SIZE, 1);
		}
		
		char stackCurrent[] = STACK_ADDR;
		for (int i = 0; i < VM_ADDRESS_SIZE; ++i){
			this->cpu->registers.SP[i] = stackCurrent[i];
		}
		
		char codeCurrent[] = CODE_SEG_START_ADDR;
		for (int i = 0; i < VM_ADDRESS_SIZE; ++i){
			this->cpu->registers.PC[i] = codeCurrent[i];
		}
		
		char code[18][9] = {"PSH 0008",
					"DS 00000",
					"PSH 000",
					"RDu00030",
					"POP 0009",
					"DS 00010",
					"PSHa0009",
					"RDu00040",
					"POP 0009",
					"POP 0009",
					"PSHa0003",
					"PSHa0004",
					"ADDs____",
					"POP 0005",
					"PSH 0008",
					"DS 00020",
					"DS 00050",
					"HALT____"
					};
		for (int i = 0; i < 18; ++i){
			virtual_memory->setWord(codeCurrent, code[i]);
			hexAdd(codeCurrent, VM_ADDRESS_SIZE, 1);
		}
		
	}
	void RM::run(){ // <- only run command and check for interrupts
		// TODO check for interrupts
		// vm run command
		bool end = false;
		while(!end){
			
			char command[8];
			this->virtual_memory->getWord(this->cpu->registers.PC, command);
			end = this->virtual_machine->runCommand(command);
			/*
			if (needIncrementCounter==1){ // <- move to virtual_machine
				hexAdd(this->cpu->registers.PC, VM_ADDRESS_SIZE, 1);
			} else if (needIncrementCounter == 0) {
				// what to do in that case (?)
			} else if (needIncrementCounter == -1){
				break;
			}*/
		}
		
		
	}
}


#endif // SOME_RM_CPP
