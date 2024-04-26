

#ifndef SOME_CHANNEL_DEVICE_HPP

#define SOME_CHANNEL_DEVICE_HPP
#include "RM.hpp"

namespace learn2024{
	class ChannelDevice {
		private:
		VirtualMemory *userMem;
		struct {
			char SRC;
			char SRCa[6];
			char DES;
			char DESa[6];
			char SZ[5];
			char MODE;
		} registers;
		
		public:
		void setRegisters(char SRC, char SRCa[6], char DES, char DESa[6], char SZ[5], char MODE);
		void setVirtualMemory(VirtualMemory * mem);
		void XCHG();
	};

	class SomeStream {
		public:
		virtual SomeStream& operator>>(char &output) = 0;
		virtual SomeStream& operator<<(const char &input) = 0;
	};
	
	class KeyboardStream : public SomeStream{
		public:
		KeyboardStream& operator>>(char &output);
		KeyboardStream& operator<<(const char &input);
	};
	
	class ConsoleStream : public SomeStream{
		public:
		ConsoleStream& operator>>(char &output);
		ConsoleStream& operator<<(const char &input);
	};
	
	class SWAPstream : public SomeStream{
		private:
		char swapAddr[5];
		char bias;
		ifstream *inFile;
		ofstream *outFile;
		string currentLine;
		unsigned long int currentAddr;
		
		public:
		SWAPstream(char addr[6]);
		SWAPstream& operator>>(char &output);
		SWAPstream& operator<<(const char &input);
		~SWAPstream();
	};
	class UserStream : public SomeStream{
		private:
		VirtualMemory *memory;
		char userAddr[4];
		char bias;
		public:
		UserStream(char addr[5], VirtualMemory *memory);
		UserStream& operator>>(char &output);
		UserStream& operator<<(const char &input);
		
	};
	
	
	class SupervisorStream : public SomeStream{
		private:
		RealMemory *memory;
		char userAddr[8];
		char bias;
		public:
		SupervisorStream(char addr[5], RealMemory *memory);
		SupervisorStream& operator>>(char &output);
		SupervisorStream& operator<<(const char &input);
		
	};
	
	class HDDstream : public SomeStream{
		private:
		char hddAddr[5];
		char bias;
		fstream *inFile;
		string currentLine;
		unsigned long int currentAddr;
		unsigned long int dataSegRemain;
		unsigned long int codeSegRemain;
		char step; // 0 - search for program; 1 - in data segment; 2 - between data and code segment; 3 - in code segment; 4 - almost end; 5 - end
		
		public:
		HDDstream(char programName1part[4], char programName2part[4]);
		HDDstream& operator>>(char &output);
		HDDstream& operator<<(const char &input);
		~HDDstream();
	};
}



#ifdef DEBUG_1233546_CUSTOM_PROJECT
#include "ChannelDevice.cpp"
#endif // DEBUG
#endif // SOME_CHANNEL_DEVICE_HPP
