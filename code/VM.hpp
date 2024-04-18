


#ifndef SOME_VM_HPP
#define SOME_VM_HPP
#include "RM.hpp"



namespace learn2024{
	class VM {
	private:
		CPU *cpu;
		union {
			char txt[8];
			short num;
		} current;
		static constexpr short constTwoLettersToShort(char letters[]){
			
			return  static_cast<short>(letters[0]) | (static_cast<short>(letters[1]) << 8);
		}
		static short twoLettersToShort(char letters[]){
			return  static_cast<short>(letters[0]) | (static_cast<short>(letters[1]) << 8);
		}
		
		
	public:
		//void startMachine(VirtualMemory mem);
		void setCpu(CPU *cpu);
		bool runCommand(char word[ONE_WORD_SIZE]);
	};
}

#ifdef DEBUG_1233546_CUSTOM_PROJECT
#include "VM.cpp"
#endif // DEBUG
#endif

