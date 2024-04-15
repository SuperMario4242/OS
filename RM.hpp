


#ifndef SOME_RM_HPP
#define SOME_RM_HPP
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
namespace learn2024{
	class CPU;
	class VM;
	class VirtualMemory;
}
#include "FuncsAndDefs.cpp"
#include "VirtualMemory.hpp"
#include "CPU.hpp"
#include "VM.hpp"



namespace learn2024{
	class RM {
	private:
		CPU *cpu;
		VirtualMemory *virtual_memory;
		VM *virtual_machine;
	public:
		RM(CPU *cpu, VirtualMemory *virtual_memory, VM *virtual_machine);
		void initialize();
		void run();
	};
}

#ifdef DEBUG_1233546_CUSTOM_PROJECT
#include "RM.cpp"
#endif // DEBUG
#endif

