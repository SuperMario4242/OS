#include <iostream>

//#define DEBUG_1233546_CUSTOM_PROJECT
#include "../code/RM.hpp"
//#undef DEBUG_1233546_CUSTOM_PROJECT

#include <vector>
//TODO  kanalu irenginis 
// virtuali masina ir interruptai


/*
 idle procesas egzistuoja
 + resursu planuotojas 
 + resursu paskirstitojas
 
 fork procesa padalija i du lygius
 
 
 ant linux paleidom programa forkinam ja,
 pirma programa nukilinam(kill), o vaika paliekom
 
 
 vu duoda daug microsoft licenziju
 word, exel, sql server, ... 
 
 bitWarden
 arba lastPass
 asana - projektu valdimui organizeris
 */
using namespace std;
using namespace learn2024;

int main(){
    VM vm;
//	v.startMachine();
	VirtualMemory mem;
	CPU some(&mem);
	RM machine(&some, &mem, &vm);
	
//	cout << codeCurrent << endl;
	
//	cout << codeCurrent << endl;
	
	
	
	machine.initialize();
	machine.run();
	
    cout << "Hello, world!" << endl;
	cout << some.toString();
    //char ch[4];
	//ch = "abcd";
	char st[] = "2A";
	unsigned long int num = hexToInt(st, 2);
	cout << "test:" << endl;
	for (int i = 0; i < 5; ++i){
		cout << "st [" << i << "]:" << (int)st[i] << endl;
	}
	/*unsigned char tmp = 1;
	for (int i = 0; i < 15; ++i){
		cout << "2^" << i << ":" << (int)tmp << endl;
		tmp *= 2;
	}*/
	char placeForHex[7];
	placeForHex[6] = 0;
	intToHex(42, 6, placeForHex);
	cout << "placeForHex: "<< placeForHex << endl;
	cout << "st1:" << st << endl;
	hexAdd(st, 2, 2);
	cout << "st2:" << st << endl;

	
	cout << mem.toString(240);
	
	
    return 0;
}
