#include "BurrowsWheelerTransform.h"
#include "SuffixArray.h"
#include <string>

BurrowsWheelerTransform::BurrowsWheelerTransform()
{
}

BurrowsWheelerTransform::~BurrowsWheelerTransform()
{
}

char* BurrowsWheelerTransform::transform(char* str, int strlength)
{
	//int strlength = strlen(str);
	SuffixArray* suffixArr = new SuffixArray(str, strlength);

	char* result = new char[strlength + 1];
	result[strlength] = '\0';

	for (int i = 0; i < strlength; i++)
	{
		result[i] = str[(suffixArr->sfArr[i] - 1 + strlength) % strlength];
	}

	delete suffixArr;
	return result;
}

template<typename T>
int BurrowsWheelerTransform::findIndex(T* arr, int arrSize, T elm)
{
	for (int i = 0; i < arrSize; i++)
	{
		if (arr[i] == elm) return i;
	}
	return -1;
}

int BurrowsWheelerTransform::preProcessStr(char* str, int** apbLog, int apbSize)
{
	if (*apbLog)
	{
		delete[] * apbLog;
	}
	*apbLog = new int[apbSize]();

	int strlength = 0;
	int curChar = str[strlength];

	while (curChar != '\0')
	{
		(*apbLog)[(unsigned char)curChar]++;

		strlength++;

		curChar = str[strlength];
	}

	return strlength;

}

char* BurrowsWheelerTransform::inverseTransform(char* str)
{
	int* apbLog = nullptr;
	int apbSize = 300;
	int strlength = preProcessStr(str, &apbLog, apbSize);

	int sum = 0;

	int* apbIndex = new int[apbSize]();

	for (int i = 0; i < apbSize; i++)
	{
		apbIndex[i] = sum;
		sum += apbLog[i];
	}

	delete[] apbLog;

	char* result = new char[strlength + 1];
	result[strlength] = '\0';

	int* nextStr = new int[strlength];

	for (int i = 0; i < strlength; i++)
	{
		unsigned char curChar = str[i];
		nextStr[apbIndex[(unsigned char)curChar]] = i;
		apbIndex[curChar]++;
	}

	int index = findIndex<char>(str, strlength, '$');
	for (int i = 0; i < strlength; i++)
	{
		result[i] = str[nextStr[index]];
		index = nextStr[index];
	}

	delete[] nextStr;

	delete[] apbIndex;

	return result;
}

