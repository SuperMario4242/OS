2 ways to compile this:

1.
	a) uncomment 2 strings in 'text.cpp':

	#define DEBUG_1233546_CUSTOM_PROJECT

	#undef DEBUG_1233546_CUSTOM_PROJECT

	b) run command from terminal:

	g++ -std=c++11 inputs/test.cpp -o out.exe
2.
	a) comment 2 strings in 'text.cpp':

	//#define DEBUG_1233546_CUSTOM_PROJECT

	//#undef DEBUG_1233546_CUSTOM_PROJECT

	b) run file 'createExe.bat'
