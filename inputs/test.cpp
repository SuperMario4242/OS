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
	ChannelDevice cd;
	//cd.XCHG();
	//cout << "ULONG_MAX" << ULONG_MAX << endl;
    VM vm;
//	v.startMachine();
	cout << "test" << endl;
	RealMemory rmem;
//	cout << "ttest" << endl;
	
	VirtualMemory vmem(&rmem, "00020100");
	CPU some(&vmem);
	cout << "test0" << endl;
	RM machine(&some, &vmem, &vm, &cd);
	
//	cout << codeCurrent << endl;
	
//	cout << codeCurrent << endl;
	cout << "test1" << endl;
	
	
	machine.initialize();
	
	cout << "test2" << endl;
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

	char addr[] = "00000100";
//	cout << vmem.toString(addr, 50);
	cout << rmem.toString(addr, 50);
	cout << "-------------\n";
	char addr2[] = "00008100";
	cout << rmem.toString(addr2, 50);
	cout << "-------------\n";
	char addr3[] = "00010100";
	cout << rmem.toString(addr3, 50);
	cout << "-------------\n";
	char addr4[] = "00018100";
	cout << rmem.toString(addr4, 50);
	cout << "-------------\n";
	char addr5[] = "00020100";
	cout << rmem.toString(addr5, 50);
	
	cout << ",,,,,,,,,\n";
	cout << "virtual memory: \n";
	char addr6[] = "0000";
	cout << vmem.toString(addr6, 50);
	cout << ",,,,,,,,,\n";
	char addr7[] = "8000";
	cout << vmem.toString(addr7, 50);
	cout << ",,,,,,,,,\n";
	char addr8[] = "f000";
	cout << vmem.toString(addr8, 50);
	
    return 0;
}
