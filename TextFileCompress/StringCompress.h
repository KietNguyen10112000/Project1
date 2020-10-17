#pragma once
#include <fstream>

//using namespace std;

class StringCompress
{
public:
	StringCompress();
	~StringCompress();

private:
	//read file and count number of charater
	static void readFile(std::fstream* f, char* buffer, long long* count);

public:
	//compress string that has letters only (a-z and A-Z);
	//static char* nonDigitCompress(char* str, int strlen);

	//uncompress string that has letters only (a-z and A-Z);
	//static char* nonDigitUncompress(char* str, int strlen);

	//compress string that has digits only (0-9);
	//static char* digitOnlyCompress(char* digits, int length);

	//uncompress string that has digits only (0-9);
	//static char* digitOnlyUncompress(char* digits, int length);

	//return number of character encoded
	//define if char = 0xFF then n next chars will be encoded for digits (from 0 to 9) and end with 4 bits 1111
	//after call this fuction stride will be number of encoded digits in dgStart
	static int digitOnlyCompress(char* dgStart, char* buffer, int* stride);
	//return number of decoded digits
	//define if char = 0xFF then n next chars will be encoded for digits (from 0 to 9) and end with 4 bits 1111
	//after call this fuction bufStride will be number of character has been decoded
	static int digitOnlyUncompress(char* dgStart, char* buffer, int* bufStride);

	//compress string (a-z, A-Z, 0-9)
	static char* compress(char* str, int strlen, int* resultLen);

	static char* uncompress(char* str, int strlen);

	//compress a text file
	//window platform only
	static void compress(const char* sourceFile, const char* destFile);
	//uncompress a text file
	static void uncompress(const char* sourceFile, const char* destFile);

};


