#pragma once
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_SF_ARR_AT_TIME 8
//#define DEBUG

class SuffixArray
{
private:
	static unsigned char manySfArr;

public:
	char* str;
	int strlen;

//#ifdef DEBUG
//	vector<int> sfArr;
//#else
	int* sfArr;
//#endif
	
	int count = 0;

public:
	SuffixArray(char* str, int strlen);
	~SuffixArray();

private:
	void makeSuffixArrayNormal();
	void makeSuffixArrayFast();
	void firstCalculateIndexArr(int* index);
	int firstCalculateIndex(int i, int j);
	void calculateIndexArr(int* index, int deep, int* outIndex);
	int calculateIndex(int i, int j, int deep, int* index);

public:
	void print();

};