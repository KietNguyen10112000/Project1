#include <iostream>
#include "BurrowsWheelerTransform.h"
#include "StringCompress.h"
#include <Windows.h>
#include <thread>

using namespace std;

void function(int i)
{
	//Sleep(rand() % (1000 + 50 - 0));
	cout << "Thread: " << i << " has been created !!!" << endl;
}

int findFirstMatchStrIndex(char* str1, int len1, char* str2, int len2)
{
	int result = -1;

	if (len1 > len2)
	{
		len1 = len2;
	}
	else 
	{
		len2 = len1;
	}

	char* p1 = str1;
	char* p2 = str2;

	while (true)
	{
		if (len1 == 0 || len2 == 0)
		{
			if (p1[len1] != p2[len2])
			{
				result = len1;
			}
			break;
		}
		len1 = len1 / 2;
		len2 = len2 / 2;
		if (p1[len1] != p2[len2])
		{
			result = len1;
		}
		else {
			result = findFirstMatchStrIndex(str1, len1, str2, len2);
			if (result == -1)
			{
				result = findFirstMatchStrIndex(&str1[len1], len1, &str2[len2], len2);
			}
		}
		
	}
	return result;
}

int main()
{
	/*char* str = (char*)"Java's popularity continued to decline this month, \
almost clearing the path for Python to snatch its spot as the world's second most popular programming language, \
according to Tiobe's latest programming language rankings. \n\
If Python does overtake Java, it would mark the first time since Tiobe began its programming \
language popularity index in that Java would be outside the top two spots. As Tiobe CEO Paul Jansen notes, \
C and Java have held the top two spots consistently for two decades. \
But today-year-old Java is approaching its -time y, falling percentage points compared with October.$";*/

//	char* str = (char*)"Java's popularity continued to decline this month, \
//almost clearing the path for Python to snatch its spot as the world's second most popular programming language, \
//according to Tiobe's latest programming language rankings. \
//If Python does overtake Java, it would mark the first time since Tiobe began its programming \
//language popularity index in 2001 that Java would be outside the top two spots. As Tiobe CEO Paul Jansen notes, \
//C and Java have held the top two spots consistently for two decades. \
//But today 25-year-old Java is approaching its -time y, falling 4.32 percentage points compared with October 2019.$";
//
//
//	//char* str = (char*)"banaajshdoiqwoelkzmxcn,asjdnaas$";
//
//	int strL = strlen(str);
//
//	char* bwtStr = BurrowsWheelerTransform::transform(str, strL);
//
//	int zipStrlen = 0;
//	char* zipStr = StringCompress::compress(bwtStr, strL, &zipStrlen);
//
//	char* unZipStr = StringCompress::uncompress(zipStr, strL);
//
//	int temp = 0;
//
//	char* oriStr = BurrowsWheelerTransform::inverseTransform(unZipStr);
//
//
//	cout << bwtStr << endl;
//
//	cout << endl << oriStr << endl;
//
//	cout << endl << zipStr << endl;
//
//	cout << endl << unZipStr << endl;

	//cout << findFirstMatchStrIndex((char*)"abcdefk", 7, (char*)"abddegk", 7) << endl;

	/*char str[] = "abc1lkjsdf";

	int strL = strlen(str);

	char* pStr = &str[0];

	char* buffer = new char[strL + 1];
	strcpy_s(buffer, strL * sizeof(char) + 1, pStr);

	char* buffer1 = new char[strL + 1];
	buffer1[strL] = '\0';

	int nDigits = 0;

	int n = StringCompress::digitOnlyCompress(&pStr[3], &buffer[3], &nDigits);

	n = StringCompress::digitOnlyUncompress(&buffer[3], &buffer1[3], &nDigits);

	cout << endl << "Encode Buffer: " << buffer << endl;

	cout << endl << "Decode Buffer: " << buffer1 << endl;

	cout << endl << "n: " << n << endl;
	cout << endl << "Number of digits: " << nDigits << endl;*/

	//StringCompress::compress("D:\\Project1\\TextFileExsample\\bible.txt", "compressText.txt");
	//StringCompress::compress("D:\\Java\\Game_1\\map\\navigationGrid.txt", "compressText.txt");

	StringCompress::multiThreadCompress("D:\\Project1\\TextFileExsample\\bible.txt", "compressText.txt", 4, 1 * 1024 * 1024, 2 * 1024 * 1024);
	cout << "Compressed Sucessfully !!!" << endl;

	StringCompress::uncompress("compressText.txt", "textFile.txt");
	cout << "Uncompressed Sucessfully !!!" << endl;

	//cout << (char)3 << "AAA" << endl;
	
	/*thread** thrArr = new thread * [4];
	for (int i = 0; i < 4; i++)
	{
		thrArr[i] = new thread(&function, i);
	}

	for (int i = 0; i < 4; i++)
	{
		if (thrArr[i]->joinable())
		{
			thrArr[i]->join();
			cout << "Thread " << i << " has been deleted" << endl;
			delete thrArr[i];
		}
	}
	delete[] thrArr;*/
	
	return 0;
}