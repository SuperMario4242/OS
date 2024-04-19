
#ifndef SOME_CPU_HPP

#define SOME_CPU_HPP
#include "RM.hpp"


namespace learn2024{
	
	class CPU{
	private:
		VirtualMemory *memory;
		static int programCounterSize;
		static int programPointerSize;
		static int stackPointerSize;
		public:
		struct {
			char PC[4];
			char SP[4];
			char PTR[8];
			
			struct {
				char zero;
				char carry;
			} status;
			unsigned char TI;
			unsigned char PI;
			unsigned char SI;
		} registers;
		
	public:
		CPU();
		CPU(VirtualMemory *memory);
		
		std::string toString()const;
	//	void incrementPC()(???);
		
	//	unsigned long int hexToInt(char hex[], int hexSize)const;
	//	void intTohex(unsigned long int num, int hexSize, char placeForHex[])const;
		struct {
			CPU* cpu;
			void cmdADDs();
			void cmdSUBs();
			void cmdMULs();
			void cmdDIVs();
			void cmdPSHa(char arg[4]);
			void cmdPSH (char arg[4]);
			void cmdPOP (char arg[4]);
			void cmdCMP ();
			void cmdJMP (char arg[4]);
			void cmdJMPB(char arg[4]);
			void cmdJMPE(char arg[4]);
			
			void cmdJAE(char arg[4]);
			void cmdJNE(char arg[4]);
			void cmdJBE(char arg[4]);
			void cmdJMPA(char arg[4]);
			
			void cmdDS (char arg[5]);
			void cmdAND();
			void cmdOR();
			void cmdXOR();
			void cmdNOT();
//		private:
	//		void lalal
		} commands;
		typedef decltype(commands) Commands;
		friend Commands;
	private:
		//std::string programCounterToString()const;
	};
}
#ifdef DEBUG_1233546_CUSTOM_PROJECT
#include "CPU.cpp"
#endif // DEBUG
#endif // SOME_CPU_HPP
