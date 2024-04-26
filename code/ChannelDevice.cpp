

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
				std::cout << "SupervisorStream" << std::endl;
				outputStream = new SupervisorStream(this->registers.DESa, this->userMem->realMemory);
				
				/*std::cout << "SupervisorMem (notWorking)" << std::endl;
				cerr << "Supervizor memory not supported yet!!!" << endl;
				int a = 10/0;*/
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
				std::cout << "SupervisorStream" << std::endl;
				outputStream = new SupervisorStream(this->registers.SRCa, this->userMem->realMemory);
				
			/*	std::cout << "SupervisorMem (notWorking)" << std::endl;
				cerr << "Supervizor memory not supported yet!!!" << endl;
				int a = 10/0;*/
			break;}
			case 5:{
			
				if (this->registers.MODE != 3){
					char temp[] = "Error, we can use HDD only with ChannelDevice MODE 3";
					std::cout << temp << std::endl;
					std::cerr << temp;
					throw temp;
				} else {
					std::cout << "HDDstream" << std::endl;
					inputStream = new HDDstream(this->registers.SRCa, this->registers.SZ);
				}
				
			break;}
			default:
				cout << "undefined" << std::endl;
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
		} else if (this->registers.MODE == 2) {
			char tmp;
			*inputStream >> tmp;
			while (tmp != this->registers.SZ[VM_ADDRESS_SIZE]){
				*outputStream << tmp;
				*inputStream >> tmp;
			}
		} else if (this->registers.MODE == 3) {
			if (this->registers.SRC != 5){
				char temp[] = "Error, we can use ChannelDevice MODE 3 only with HDD";
				std::cout << temp << std::endl;
				std::cerr << temp;
				throw temp;
			}
			unsigned long int size = (ONE_BLOCK_SIZE*128 + ONE_BLOCK_SIZE*(128-16))*ONE_WORD_SIZE;
			for (unsigned long int i = 0; i < size; ++i){
				bool show = i < 1000;// || i > size - 1000 || (i < 264000 && i > 262000);
				/*if (i > size - 1000){
					cout << "t:" << i << endl;
				}*/
				char tmp;
				
				if (show)
					if (i%8 == 0){
						cout << endl;
					}
				*inputStream >> tmp;
				if (show){
					if (i%8 == 0){
						
						cout << "i:" << i;
					}
					cout << tmp;
				}
				*outputStream << tmp;
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
	
	SupervisorStream::SupervisorStream(char addr[6], RealMemory *memory){
		for (int i = 0; i < 8-5; ++i){
			this->userAddr[i] = '0';
		}
		for (int i = 0; i < 5; ++i){
			this->userAddr[i+(8-5)] = addr[i];
		}
		int temp = hexToInt(&addr[5], 1);
		if (temp > 7) 
			temp -= 8;
		this->bias = temp;
		/*cout << "bias:" << temp << endl;
		cout << "addr:";
		for (int i = 0; i < 6; ++i){
			cout << addr[i];
		}
		cout << endl;*/
		
		this->memory = memory;
	}
	SupervisorStream& SupervisorStream::operator>>(char &output){
		if (this->bias < 8){
			char word[8];
			this->memory->getWord(this->userAddr, word);
			output = word[bias];
			++this->bias;
		} else {
			char word[8]; 
			hexAdd(this->userAddr, ONE_WORD_SIZE, 1);
			/*char tmp[8];
			for (int i = 0; i < 8-5; ++i){
				tmp[i] = '0';
			}
			for (int i = 8-5; i < 8; ++i){
				tmp[i] = this->userAddr[i-(8-5)];
			}*/
			this->bias -= 8;
			this->memory->getWord(this->userAddr, word);
			output = word[bias];
			++this->bias;
		}
		return *this;
	}
	SupervisorStream& SupervisorStream::operator<<(const char &input){
	/*	cout << "|:((" << input << ")) -> [[";
		for (int i = 0; i < 8; ++i){
			cout << this->userAddr[i];
		}
		cout << "]]b:" << (int)this->bias << "|";*/
		if (this->bias < 8){
			char word[8];
			this->memory->getWord(this->userAddr, word);
			word[bias] = input;
			this->memory->setWord(this->userAddr, word);
			++bias;
		} else {
			char word[8];
			/*cout << "sup:: addr:";
			for (int i = 0; i < 8; ++i){
				cout << this->userAddr[i];
			}
			cout << endl;*/
			
			hexAdd(this->userAddr, ONE_WORD_SIZE, 1);
			this->bias -= 8;
			this->memory->getWord(this->userAddr, word);
			word[bias] = input;
			this->memory->setWord(this->userAddr, word);
			++bias;
		}
		return *this;
	}
	
	HDDstream::HDDstream(char programName1part[4], char programName2part[4]){ // char [4], char[4]
		for (int i = 0; i < 5; ++i){
			this->hddAddr[i] = 0;
		}
	//	int temp = hexToInt(&programName[7], 1); //
	//	if (temp > 7) 
	//		temp -= 8;
		this->bias = 0;
		this->step = 0;
		this->inFile = new fstream("./res/HDD.txt");

		//cout << "I am here" << endl;
		if (!inFile->is_open()) {
			cout << "Error opening file!cout|" << this->inFile << endl;
			cerr << "Error opening file!" << endl;
			exit(EXIT_FAILURE);
		} else {
		//	cout << "file is opened" << endl;
		}

	//	cout << "in File:" << this->inFile << endl;
		
		this->dataSegRemain = ONE_BLOCK_SIZE*128 + 2; // TEMPORARY // ONE_BLOCK_SIZE*128
		this->codeSegRemain = ONE_BLOCK_SIZE*(128-16); // ONE_BLOCK_SIZE*(128-16)
		
	//	this->outFile = new ofstream("../res/swap.sw");
	//	cout << "from hdd init" << endl;
		//unsigned long int currentAddr = hexToInt(programName, 5);
		bool foundProgram = false;
		string line;
	//	getline(*this->inFile, line);
	//	cout << "line1:" << line << endl;
	//	getline(*this->inFile, line);
	//	cout << "from hdd iniline:" << line << endl;
	//	getline(*this->inFile, line);
	//	cout << "exit:" << line << endl;
	//	int a = 2/0;
		while (!foundProgram){
		//	cout << "from hdd init1" << endl;
			getline(*this->inFile, line);
			//cout << "from hdd init2, line:" << line << endl;
			string sub = line.substr(7);
	//		cout << "from hdd init3" << endl;
			if (sub.find("#NEW_PROGRAM") != string::npos){
			//	cout << "from hdd init4" << endl;
				foundProgram = true;
				for (int i = 0; i < 4; ++i){
					if (line[i] != programName1part[i]){
						foundProgram = false;
					}
				}
				for (int i = 4; i < 8; ++i){
					if (line[i] != programName2part[i-4]){
						foundProgram = false;
					}
				}
			}
			//--currentAddr;
		}
		this->currentLine = line;
		//getline(*this->inFile, this->currentLine);
	//	this->step = 1;
	//	getline(*this->inFile, this->currentLine);
	//	inFile.seekg(this->currentAddr);
	}
	HDDstream& HDDstream::operator>>(char &output){
		//cout << "nan";
		switch (this->step){
			case 0:{
			//	cout << "lala";
				bool foundDataSeg = false;
				string line;
				while (!foundDataSeg){
					
					getline(*this->inFile, line);
					string sub = line.substr(7);
					if (sub.find("#DATA_SEGMENT") != string::npos){
						foundDataSeg = true;
						
					}
				}
				this->currentLine = line;
				output = this->currentLine[bias];
				++this->bias;
				--this->dataSegRemain;
				++this->step;// = 1;
			break;}
			case 1:{
				if (this->bias < 8){
					output = this->currentLine[bias];
					++this->bias;
				} else {
					getline(*this->inFile, this->currentLine);
					--this->dataSegRemain;
				//	cout << "(1)dataSegRemain:" << this->dataSegRemain << endl;
				//	if (true)
				//		cout << "currentLine:" << this->currentLine << endl;
					//bool startCodeSeg = false;
					string sub = this->currentLine.substr(7);
					this->bias -= 8;
					if (sub.find("#CODE_SEGMENT") != string::npos){
						--this->codeSegRemain;
						++this->step; // = 2;
						output = '_';
						++this->bias;
					} else {
						output = this->currentLine[bias];
						++this->bias;
					}
					//string sub = this->currentLine.substr(7);
					
				}
			break;}
			/*case 2:{
				if (this->bias < 8){
					output = this->currentLine[bias];
					++this->bias;
				} else {
					cout << "(2)currentLine" << this->currentLine << endl;
					--this->dataSegRemain;
					this->bias -= 8;
					++this->step; // = 3;
				}
			break;}*/
			case 2:{
				if (this->bias < 4){
					output = '_';
				} else if (this->bias < 8){
					output = '-';
				} else {
					this->bias -= 8;
					--this->dataSegRemain;
					if (this->dataSegRemain < 1000){
				//		cout << "(2)dataSegRemain:" << this->dataSegRemain << endl;
					}
					
				//	if (true)
				//		cout << "this->dataSegRemain:" << this->dataSegRemain << endl;
					if (this->dataSegRemain == 1){
						++this->step; // = 3;
						/*this->currentLine[0] = '0';
						this->currentLine[1] = '1';
						this->currentLine[2] = '2';
						this->currentLine[3] = '3';
						this->currentLine[4] = '4';
						this->currentLine[5] = '5';
						this->currentLine[6] = '6';
						this->currentLine[7] = '7';*/
						++this->bias;
						output = this->currentLine[0];
						break; // ??????????
					}
					output = '_';
				}
				++this->bias;
				
				
			break;}
			case 3:{
				if (this->bias < 8){
					output = this->currentLine[bias];
					++this->bias;
				} else {
					getline(*this->inFile, this->currentLine);
					--this->codeSegRemain;
				//	if (true)
				//		cout << "(3)currentLine:" << this->currentLine << endl;
					//bool startCodeSeg = false;
					string sub = this->currentLine.substr(7);
					this->bias -= 8;
					if (sub.find("#NEW_PROGRAM_END") != string::npos){
						output = this->currentLine[bias];
						++this->bias;
						++this->step; // = 3;
					} else {
						output = this->currentLine[bias];
						++this->bias;
					}
					//string sub = this->currentLine.substr(7);
					
				}
			break;}
			case 4:{
				if (this->bias < 8){
					output = this->currentLine[bias];
					++this->bias;
				} else {
				//	cout << "(4)currentLine" << this->currentLine << endl;
				//	--this->codeSegRemain;
					this->bias -= 8;
					output = '_';
					++this->bias;
					++this->step; // = 5;
				}
			break;}
			case 5:{
				if (this->bias < 4){
					output = '_';
				} else if (this->bias < 8){
					output = '-';
					if (this->bias == 7){
						if (this->codeSegRemain == 0){
							++this->step; // = 6;
							break;
						}
					}
				} else {
					this->bias -= 8;
					--this->codeSegRemain;
					if (this->codeSegRemain < 150)
					//	cout << "(5)codeSegRemain:" << this->codeSegRemain << endl;
					
					output = '_';
				}
				++this->bias;
			break;}
			default:
				std::cout << "undefined" << std::endl;
				cerr << "Unknown step in HDDstream." << endl;
				int a = 10/0;
		}
		
		if (this->step == 0){
			
		} else if (this->step == 1){
			
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
