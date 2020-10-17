#include "SuffixArray.h"
#include <algorithm>
#include <iostream>

using namespace std;

SuffixArray::SuffixArray(char* str, int strlen)
{
	this->str = str;
	this->strlen = strlen;
	makeSuffixArray();
}

SuffixArray::~SuffixArray()
{
	delete[] sfArr;
}

bool SuffixArray::cmp(char* c1, char* c2)
{
	if (strcmp(c1, c2) < 0)
	{
		return true;
	}
	return false;
}

void SuffixArray::makeSuffixArray()
{
	char** suffixs = new char* [strlen];
	sfArr = new int[strlen];

	if (!suffixs)
	{
		exit(-1);
	}

	for (int i = 0; i < strlen; i++)
	{
		suffixs[i] = &str[i];
	}

	sort(&suffixs[0], &suffixs[strlen], cmp);

	for (int i = 0; i < strlen; i++)
	{
		sfArr[i] = suffixs[i] - &str[0];
	}

	delete[] suffixs;
}

void SuffixArray::print()
{
	for (int i = 0; i < strlen; i++)
	{
		cout << sfArr[i] << " ";
	}
	cout << endl;
}