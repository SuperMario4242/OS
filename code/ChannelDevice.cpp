

#ifndef SOME_CHANNEL_DEVICE_CPP

#define SOME_CHANNEL_DEVICE_CPP
#include "ChannelDevice.hpp"

namespace learn2024{
	void ChannelDevice::setRegisters(char SRC, char SRCa[6], char DES, char DESa[6], char SZ[5], char MODE){
		this->registers.SRC = SRC;
		for (int i = 0; i < 6; ++i){
			this->registers.SRCa[i] = SRCa[i];
		}
		this->registers.DES = DES;
		for (int i = 0; i < 6; ++i){
			this->registers.DESa[i] = DESa[i];
		}
		
		for (int i = 0; i < 5; ++i){
			this->registers.SZ[i] = SZ[i];
		}
		this->registers.MODE = MODE;
	}
	
	void ChannelDevice::setVirtualMemory(VirtualMemory * mem){
		this->userMem = mem;
	}
	
	void ChannelDevice::XCHG(){
		std::cout << "ChannelDevice:exchange!" << std::endl;
		SomeStream *inputStream;
		SomeStream *outputStream;
		cout << "outputStream:" ;
		switch (this->registers.DES){
			case 1:{
				std::cout << "userStream" << std::endl;
				outputStream = new UserStream(&this->registers.DESa[1], this->userMem);
			break;}
			case 2:{
				std::cout << "SWAPstream" << std::endl;
				outputStream = new SWAPstream(this->registers.DESa);
			break;}
			case 3:{
				std::cout << "ConsoleStream" << std::endl;
				outputStream = new ConsoleStream();
			break;}
			case 4:{
				std::cout << "SupervisorMem (notWorking)" << std::endl;
				cerr << "Supervizor memory not supported yet!!!" << endl;
				int a = 10/0;
			break;}
			default:
				std::cout << "undefined" << std::endl;
				cerr << "Invalid Source for channel device" << endl;
				int a = 10/0;
		}
		cout << "inputStream:" ;
		switch (this->registers.SRC){
			case 1:{
				std::cout << "userStream" << std::endl;
				inputStream = new UserStream(&this->registers.SRCa[1], this->userMem);
			break;}
			case 2:{
				std::cout << "SWAPstream" << std::endl;
				inputStream = new SWAPstream(this->registers.SRCa);
			break;}
			case 3:{
				cout << "KeyboardStream" << endl;
				inputStream = new KeyboardStream();
			break;}
			case 4:{
				std::cout << "SupervisorMem (notWorking)" << std::endl;
				cerr << "Supervizor memory not supported yet!!!" << endl;
				int a = 10/0;
			break;}
			case 5:{
				std::cout << "HDDstream" << std::endl;
				inputStream = new HDDstream(this->registers.DESa);
			break;}
			default:
				std::cout << "undefined" << std::endl;
				cerr << "Invalid Destination for channel device" << endl;
				int a = 10/0;
		}
		
		//cout << "I am here" << endl;
		if (this->registers.MODE == 1){
		//	cout << "I am here1" << endl;
			unsigned long int size = hexToInt(this->registers.SZ, VM_ADDRESS_SIZE+1);
			for (unsigned long int i = 0; i < size; ++i){
				char tmp;
				*inputStream >> tmp;
			//	cout << "inputCH:" << tmp << endl;
				*outputStream << tmp;
			//	cout << "here:" << endl;
			//	cout << "i:" << i << endl;
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
			this->userAddr[i] = addr[i];
		}
	//	cout << "addr[0] |" << addr[0] << "|" << endl;
		
		//cout << "userAddr" << this->userAddr << endl;
		
		//cout << "UserStream||we will here:";
	//	for (int i = 0; i < 5; ++i) {
		//	cout << addr[i];
	//	}
		//cout << "\n";
		int temp = hexToInt(&addr[4], 1);
		if (temp > 7) 
			temp -= 8;
		this->bias = temp;
		
		this->memory = memory;
		
	}
	UserStream& UserStream::operator>>(char &output){
		//cout << "here" << endl;
		if (this->bias < 8){
		//	cout << "here1" << endl;
			char word[8];
		//	cout << "here2" << endl;
			this->memory->getWord(this->userAddr, word);
			output = word[bias];
			//cout << "here3 output:" << output << endl;
			++this->bias;
		} else {
			char word[8]; 
			hexAdd(this->userAddr, VM_ADDRESS_SIZE, 1);
			this->bias -= 8;
			this->memory->getWord(this->userAddr, word);
			output = word[bias];
			++this->bias;
		}
		return *this;
	}
	UserStream& UserStream::operator<<(const char &input){
	//	cout << "this->userAddr" << this->userAddr << endl;
		if (this->bias < 8){
		//	cout << "here1" << endl;
			char word[8];
		//	cout << "here2" << endl;
			this->memory->getWord(this->userAddr, word);
		//	cout << "here3" << endl;
			word[bias] = input;
		//	cout << "here4" << endl;
			this->memory->setWord(this->userAddr, word);
		//	cout << "here5" << endl;
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
		return *this;
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
