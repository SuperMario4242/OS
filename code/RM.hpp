


#ifndef SOME_RM_HPP
#define SOME_RM_HPP
#include <sstream>
#include <string>
#include <stdio.h>
#include <iostream>
#include <climits> 
#include <fstream>

namespace learn2024{
	using namespace std;
	class CPU;
	class VM;
	class VirtualMemory;
	class ChannelDevice;
}
#include "FuncsAndDefs.hpp"
#include "VirtualMemory.hpp"
#include "CPU.hpp"
#include "VM.hpp"
#include "ChannelDevice.hpp"



namespace learn2024{
	class RM {
	private:
		
		CPU *cpu;
		VirtualMemory *virtual_memory;
		VM *virtual_machine;
	public:
		RM(CPU *cpu, VirtualMemory *virtual_memory, VM *virtual_machine, ChannelDevice *channelDevice);
		void initialize();
		void run();
	};
}

#ifdef DEBUG_1233546_CUSTOM_PROJECT
#include "RM.cpp"
#endif // DEBUG
#endif

