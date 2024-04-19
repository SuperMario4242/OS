

#ifndef SOME_CHANNEL_DEVICE_CPP

#define SOME_CHANNEL_DEVICE_CPP
#include "ChannelDevice.hpp"

namespace learn2024{
	void ChannelDevice::setVirtualMemory(VirtualMemory * mem){
		this->userMem = mem;
	}
	
	void ChannelDevice::XCHG(){
		std::cout << "try exchange!!!" << std::endl;
		SomeStream *inputStream;
		SomeStream *outputStream;
		switch (this->registers.SRC){
			case 1:{
				inputStream = new UserStream(&this->registers.SRCa[1], this->userMem);
			break;}
			case 2:{
				inputStream = new SWAPstream(this->registers.SRCa);
			break;}
			case 3:{
				inputStream = new ConsoleStream();
			break;}
			case 4:{
				cerr << "Supervizor memory not supported yet!!!" << endl;
				int a = 10/0;
			break;}
			default:
				cerr << "Invalid Source for channel device" << endl;
				int a = 10/0;
		}
		
		switch (this->registers.DES){
			case 1:{
				outputStream = new UserStream(&this->registers.SRCa[1], this->userMem);
			break;}
			case 2:{
				outputStream = new SWAPstream(this->registers.DESa);
			break;}
			case 3:{
				outputStream = new KeyboardStream();
			break;}
			case 4:{
				cerr << "Supervizor memory not supported yet!!!" << endl;
				int a = 10/0;
			break;}
			case 5:{
				outputStream = new HDDstream(this->registers.DESa);
			break;}
			default:
				cerr << "Invalid Destination for channel device" << endl;
				int a = 10/0;
		}
		
		
		if (this->registers.MODE == 1){
			unsigned long int size = hexToInt(this->registers.SZ, VM_ADDRESS_SIZE+1);
			for (unsigned long int i = 0; i < size; ++i){
				char tmp;
				*inputStream >> tmp;
				*outputStream << tmp;
			}
		} else {
			char tmp;
			*inputStream >> tmp;
			while (tmp != this->registers.SZ[VM_ADDRESS_SIZE]){
				*outputStream << tmp;
				*inputStream >> tmp;
			}
		}
		
	}
	
	
	KeyboardStream& KeyboardStream::operator>>(char &output){
		std::cin >> output;
		return *this;
	}
	KeyboardStream& KeyboardStream::operator<<(const char &output){
		char temp[] = "Error, streams conflict: KeyboardStream can only write.";
		std::cerr << temp;
		throw temp;
	}
	
	
	ConsoleStream& ConsoleStream::operator>>(char &output){
		char temp[] = "Error, streams conflict: ConsoleStream can only read.";
		std::cerr << temp;
		throw temp;
	}
	ConsoleStream& ConsoleStream::operator<<(const char &input){
		std::cout << input;
		return *this;
	}
	
	SWAPstream::SWAPstream(char addr[6]){
		for (int i = 0; i < 5; ++i){
			this->swapAddr[i] = addr[i];
		}
		int temp = hexToInt(&addr[5], 1);
		if (temp > 7)
			temp -= 8;
		this->bias = temp;
		this->inFile = new ifstream("../res/swap.sw");
		this->outFile = new ofstream("../res/swap.sw");
		
		this->currentAddr = hexToInt(addr, 5)*10 + this->bias;
	/*	while (currentAddr > 0){
			string line;
			getline(inputFile, this->currentLine);
			--currentAddr;
		}
		getline(inputFile, this->currentLine);*/
		inFile->seekg(this->currentAddr);
	}
	SWAPstream& SWAPstream::operator>>(char &output){
		if (this->currentAddr % 10 < 8){
			inFile->seekg(this->currentAddr);
			inFile->read(&output, 1);
			++this->currentAddr;
		} else {
			while (!(this->currentAddr % 10 < 8)){
				++this->currentAddr;
			}
			inFile->seekg(this->currentAddr);
			inFile->read(&output, 1);
			++this->currentAddr;
			
		}
		/*if (this->bias < 8){
			output = this->currentLine[bias];
			++bias;
		} else {
			getline(inputFile, this->currentLine);
			bias -= 8;
			output = this->currentLine[bias];
			++bias;
		}*/
		
	}
	SWAPstream& SWAPstream::operator<<(const char &input){
		if (this->currentAddr % 10 < 8){
			outFile->seekp(this->currentAddr);
			outFile->write(&input, 1);
			++this->currentAddr;
		} else {
			while (!(this->currentAddr % 10 < 8)){
				++this->currentAddr;
			}
			outFile->seekp(this->currentAddr);
			outFile->write(&input, 1);
			++this->currentAddr;
			
		}
	}
	SWAPstream::~SWAPstream(){
		this->inFile->close();
		this->outFile->close();
	}
	
	UserStream::UserStream(char addr[5], VirtualMemory *memory){
		for (int i = 0; i < 4; ++i){
			this->userAddr[i] = addr[i+1];
		}
		int temp = hexToInt(&addr[5], 1);
		if (temp > 7) 
			temp -= 8;
		this->bias = temp;
		
		this->memory = memory;
		
	}
	UserStream& UserStream::operator>>(char &output){
		if (this->bias < 8){
			char word[8];
			this->memory->getWord(this->userAddr, word);
			output = word[bias];
			++bias;
		} else {
			char word[8]; 
			hexAdd(this->userAddr, VM_ADDRESS_SIZE, 1);
			this->bias -= 8;
			this->memory->getWord(this->userAddr, word);
			output = word[bias];
			++bias;
		}
	}
	UserStream& UserStream::operator<<(const char &input){
		if (this->bias < 8){
			char word[8];
			this->memory->getWord(this->userAddr, word);
			word[bias] = input;
			this->memory->setWord(this->userAddr, word);
			++bias;
		} else {
			char word[8];
			hexAdd(this->userAddr, VM_ADDRESS_SIZE, 1);
			this->bias -= 8;
			this->memory->getWord(this->userAddr, word);
			word[bias] = input;
			this->memory->setWord(this->userAddr, word);
			++bias;
		}
	}
	
	
	HDDstream::HDDstream(char addr[6]){
		for (int i = 0; i < 5; ++i){
			this->swapAddr[i] = addr[i];
		}
		int temp = hexToInt(&addr[5], 1);
		if (temp > 7) 
			temp -= 8;
		this->bias = temp;
		this->inFile = new ifstream("../res/HDD.txt");
	//	this->outFile = new ofstream("../res/swap.sw");
		
		unsigned long int currentAddr = hexToInt(addr, 5);
		while (currentAddr > 0){
			string line;
			getline(*this->inFile, line);
			--currentAddr;
		}
		getline(*this->inFile, this->currentLine);
	//	inFile.seekg(this->currentAddr);
	}
	HDDstream& HDDstream::operator>>(char &output){
		if (this->bias < 8){
			output = this->currentLine[bias];
			++this->bias;
		} else {
			getline(*this->inFile, this->currentLine);
			this->bias -= 8;
			output = this->currentLine[bias];
			++this->bias;
		}
		return *this;
	}
	HDDstream& HDDstream::operator<<(const char &input){
		char temp[] = "Error, streams conflict: HDDstream can only write.";
		std::cerr << temp;
		throw temp;
	}
	HDDstream::~HDDstream(){
		this->inFile->close();
	}
	
}




#endif // SOME_CHANNEL_DEVICE_HPP
