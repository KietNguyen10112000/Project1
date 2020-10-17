#pragma once

class SuffixArray
{
public:
	char* str;
	int strlen;
	int* sfArr;

public:
	SuffixArray(char* str, int strlen);
	~SuffixArray();

private:
	void makeSuffixArray();
	static bool cmp(char* c1, char* c2);

public:
	void print();

};