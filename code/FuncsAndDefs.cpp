


#include "FuncsAndDefs.hpp"

#ifndef SOME_FUNCS_AND_DEFS_CPP
#define SOME_FUNCS_AND_DEFS_CPP
#include <stdlib.h>
#include <iostream>

namespace learn2024{
	void simpleCharCopy(char source[], char destination[], int size){
		for (int i = 0; i < size; ++i){
			destination[i] = source[i];
		}
	}
	unsigned long int hexToInt(char hex[], int hexSize){
	//	char hexStr[] = "1A";
	//	char hexStr2[] = "1a";
		char hexNum[hexSize+1];
		for (int i = 0; i < hexSize; ++i){
			hexNum[i] = hex[i];
		}
		hexNum[hexSize] = 0;
		unsigned long int dec = strtol(hexNum, NULL, 16);
	//	std::cout << "some int:" << dec << " lala\n";
		return dec;
	}
	
	bool isithex(char num[8],int size ) {
        for (int i = 0; i < size; i++) {
            if ((num[i] > 47 && num[i] < 58) || ( num[i] > 96 && num[i] < 102) ) {
                continue;
            }
            return false;
        }
    } 

	void intToHex(unsigned long int num, int hexSize, char placeForHex[]){
		//std::cout << "intToHex1" << std::endl;
		unsigned long int hexMax = 1;
		if (hexSize < 8)
			for (int i = 0; i < hexSize*4; ++i){
				hexMax *= 2;
			//	std::cout << "hexMax:" << hexMax << std::endl;
			}
		else if (hexSize == 8){// do nothing
		} else {
			std::cout << "error, TODO definition of error" << std::endl;
			int err = 1/0;
		}
	//	std::cout << "intToHex2, hexMax:" << hexMax << std::endl;
		if (hexSize > 0 && hexSize < 9){
	//		std::cout << "intToHex1 in if" << std::endl;
			if (hexSize < 8)
				num = num % hexMax;
		//	std::cout << "intToHex2 in if" << std::endl;
			char tmp[hexSize+1];
			for (int i = 0; i <= hexSize; ++i){
				tmp[i] = 0;
			}
		//	std::cout << "intToHex3 in if" << std::endl;
			sprintf(tmp, "%lX", num);
	//		printf("num: %X\n", num);
			int i = 0;
	//		std::cout << "intToHex4 in if" << std::endl;
			for (; i < hexSize+1; ++i){
				if (tmp[i] == 0){
					break;
				}
			}
		//	std::cout << "intToHex5 in if" << std::endl;
			i = hexSize - i;
			for (int k = 0; k < i; ++k){
				placeForHex[k] = '0';
			}
		//	std::cout << "intToHex6 in if" << std::endl;
			int st = i;
			for (; i < hexSize; ++i){
				placeForHex[i] = tmp[i-st];
			}
		//	std::cout << "intToHex7 in if" << std::endl;
		//	printf("tmp: %s\n", tmp);
		//	printf("placeForHex: %s\n", placeForHex);
		//	std::cout << "intToHex: " << num << "->" << tmp << "->" << placeForHex << std::endl;

		}
	//	std::cout << "intToHex69" << std::endl;

	}
	bool hexLess(char num1[], char num2[], int size){
		unsigned long int n1 = hexToInt(num1, size);
		unsigned long int n2 = hexToInt(num2, size);
		return n1 < n2;
	}
	bool hexEqual(char num1[], char num2[], int size){
		unsigned long int n1 = hexToInt(num1, size);
		unsigned long int n2 = hexToInt(num2, size);
		return n1 == n2;
	}
	
	void hexAdd(char hex[], int hexSize, int num){
	//	std::cout << "I am here81" << std::endl;
		int tmp = hexToInt(hex, hexSize);
	//	std::cout << "I am here81";
		tmp = tmp + num;
	//	std::cout << "I am here81" << "tmp:" << tmp << std::endl;
		intToHex(tmp, hexSize, hex);
	//	std::cout << "I am here81" << std::endl;
	}
}

#endif