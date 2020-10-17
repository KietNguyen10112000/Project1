#pragma once

class BurrowsWheelerTransform
{
private:

public:
	BurrowsWheelerTransform();
	~BurrowsWheelerTransform();

private:
	template<typename T>
	static int findIndex(T* arr, int arrSize, T elm);
	static int preProcessStr(char* str, int** apbLog, int apbSize);

public:
	static char* transform(char* str, int strlength);
	static char* inverseTransform(char* str);

	//static char* inverseTransform(char* str);

};
