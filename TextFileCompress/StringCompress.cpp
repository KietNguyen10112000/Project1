#include "StringCompress.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include "BurrowsWheelerTransform.h"

using namespace std;

StringCompress::StringCompress() 
{
}
StringCompress::~StringCompress() 
{
}

//char StringCompress::dg[10] = { 0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9 };

//char* StringCompress::nonDigitCompress(char* str, int strlen)
//{
//	char* result = new char[strlen + 1];
//	result[strlen] = '\0';
//
//	int i = 0;
//	int index = 0;
//
//	while (str[i] != '\0')
//	{
//		int count = 0;
//
//		while (str[i + count] == str[i])
//		{
//			count++;
//		}
//
//		if (count > 1)
//		{
//			result[index] = str[i];
//
//			std::string temp = std::to_string(count);
//
//			int i = 0;
//			while (temp[i] != '\0')
//			{
//				result[index + i + 1] = temp[i];
//				i++;
//			}
//
//			index += i;
//
//		}
//		else {
//			result[index] = str[i];
//		}
//
//		i += count;
//		index++;
//	}
//	result[index] = '\0';
//
//	return result;
//
//}
//
//char* StringCompress::nonDigitUncompress(char* str, int strlen)
//{
//	char* result = new char[strlen + 1];
//	result[strlen] = '\0';
//
//	int i = 0;
//
//	char* digits = new char[10];
//
//	int resultIndex = 0;
//
//	while (str[i] != '\0')
//	{
//
//		char cur = str[i] - '0';
//
//		if (cur > -1 && cur < 10)
//		{
//			int count = 0;
//			while (cur > -1 && cur < 10)
//			{
//				digits[count] = cur;
//				count++;
//				cur = str[i + count] - '0';
//			}
//
//			int num = 0;
//			for (int j = count - 1; j > -1; j--)
//			{
//				num += pow(10, count - j - 1) * digits[j];
//			}
//
//			for (int j = 0; j < num; j++)
//			{
//				result[resultIndex + j - 1] = str[i - 1];
//			}
//
//			resultIndex += num - 1;
//			i += count;
//
//		}
//		else {
//			result[resultIndex] = str[i];
//			resultIndex++;
//			i++;
//		}
//
//	}
//
//	delete[] digits;
//
//	return result;
//}
//
//char* StringCompress::digitOnlyCompress(char* digits, int length)
//{
//	char* result;
//
//	int size = 0;
//
//	if (length % 2 == 0)
//	{
//		size = length / 2;
//		result = new char[size + 1];
//		result[size] = '\0';
//	}
//	else {
//		size = (length + 1) / 2;
//		result = new char[size + 1];
//		result[size] = '\0';
//	}
//
//	int i;
//	int index = 0;
//	for (i = 0; i < length - 1; i += 2)
//	{
//		char up = digits[i] - '0';
//		char down = digits[i + 1] - '0';
//		result[index] = (up << 4) | down;
//		index++;
//	}
//	if (i == length - 1)
//	{
//		result[size - 1] = ((digits[i] - '0') << 4) | 0x0F;
//	}
//
//	return result;
//}
//
//char* StringCompress::digitOnlyUncompress(char* digits, int length)
//{
//	char* result = new char[length * 2 + 1];
//	result[length * 2] = '\0';
//
//	int index = 0;
//	for (int i = 0; i < length; i++)
//	{
//		char up = (digits[i] >> 4) & 0x0F;
//		char down = digits[i] & 0x0F;
//
//		if (down == 0x0F)
//		{
//			down = '\0' - '0';
//		}
//
//		result[index] = up + '0';
//		result[index + 1] = down + '0';
//
//		index += 2;
//	}
//
//	return result;
//}

int StringCompress::digitOnlyCompress(char* dgStart, char* buffer, int* stride)
{
	int i = 0;
	int index = 0;

	buffer[index] = (char)0x03;

	index++;

	while (true)
	{
		char up = dgStart[i] - '0';
		char down = dgStart[i + 1] - '0';

		if (up < 0 || up > 9)
		{
			buffer[index] = 0xFF;
			break;
		}

		if (down < 0 || down > 9)
		{
			buffer[index] = (up << 4) | 0x0F;
			i++;
			break;
		}

		buffer[index] = (up << 4) | down;
		if (buffer[index] == '\0')
		{
			buffer[index] = 0xAA;
		}

		index++;
		i += 2;
	}

	*stride = i;

	return index + 1;
}

int StringCompress::digitOnlyUncompress(char* dgStart, char* buffer, int* bufStride)
{
	int i = 0;
	int index = 0;

	if (dgStart[i] != (char)0x03)
	{
		return 0;
	}
	i++;

	while (true)
	{
		char up = (dgStart[i] >> 4) & 0x0F;
		char down = dgStart[i] & 0x0F;

		if (dgStart[i] == (char)0xFF)
		{
			break;
		}

		if (down == 0x0F)
		{
			buffer[index] = up + '0';
			index++;
			break;
		}

		if (dgStart[i] == (char)0xAA)
		{
			up = 0;
			down = 0;
		}

		buffer[index] = up + '0';
		buffer[index + 1] = down + '0';
		index += 2;
		i ++;
	}

	*bufStride = i + 1;

	return index;
}

char* StringCompress::compress(char* str, int strlen, int* resultLen)
{
	char* result = new char[(long long)strlen + 1];
	result[strlen] = '\0';

	int i = 0;
	int index = 0;

	while (str[i] != '\0')
	{
		if (str[i] - '0' > -1 && str[i] - '0' < 10)
		{
			int nDigits = 0;
			int n = digitOnlyCompress(&str[i], &result[index], &nDigits);

			i += nDigits;
			index += n;
			continue;
		}

		int count = 0;

		while (str[i + count] == str[i])
		{
			count++;
		}

		if (count > 1)
		{
			result[index] = str[i];

			std::string temp = std::to_string(count);

			int i = 0;
			while (temp[i] != '\0')
			{
				result[index + i + 1] = temp[i];
				i++;
			}

			index += i;

		}
		else {
			result[index] = str[i];
		}

		i += count;
		index++;
	}
	result[index] = '\0';
	*resultLen = index;

	return result;
}

char* StringCompress::uncompress(char* str, int strlen)
{
	char* result = new char[(long long)strlen + 1];
	result[strlen] = '\0';

	int i = 0;

	char* digits = new char[10];

	long long resultIndex = 0;

	while (str[i] != '\0')
	{
		
		if (str[i] == (char)0x03)
		{
			int nDigits = 0;
			int n = digitOnlyUncompress(&str[i], &result[resultIndex], &nDigits);

			i += nDigits;
			resultIndex += n;
			continue;
		}

		char cur = str[i] - '0';

		if (cur > -1 && cur < 10)
		{
			int count = 0;
			while (cur > -1 && cur < 10)
			{
				digits[count] = cur;
				count++;
				cur = str[i + count] - '0';
			}

			int num = 0;
			for (int j = count - 1; j > -1; j--)
			{
				num += pow(10, count - j - 1) * digits[j];
			}

			for (int j = 0; j < num; j++)
			{
				result[resultIndex + j - 1] = str[i - 1];
			}

			resultIndex += (long long)num - 1;
			i += count;

		}
		else {
			result[resultIndex] = str[i];
			resultIndex++;
			i++;
		}

	}

	delete[] digits;

	//result[resultIndex] = '\0';

	return result;
}

void StringCompress::readFile(fstream* f, char* buffer, long long* count)
{
	*count = 0;
	while (!f->eof())
	{
		buffer[*count] = f->get();
		if (buffer[*count] == '\0')
		{
			buffer[*count] = ' ';
		}
		(*count)++;
	}
	buffer[*count] = '$';
	(*count)++;
}

void StringCompress::compress(const char* sourceFile, const char* destFile)
{
	//get file size
	LPOFSTRUCT lpReOpenBuff = new _OFSTRUCT();
	HFILE h = OpenFile(sourceFile, lpReOpenBuff, OF_READ);
	LARGE_INTEGER size;
	GetFileSizeEx((HANDLE)h, &size);
	CloseHandle((HANDLE)h);
	delete lpReOpenBuff;

	char* buffer = new char[size.QuadPart + 2];
	buffer[size.QuadPart + 1] = '\0';

	fstream source(sourceFile);
	
	long long count = 0;
	readFile(&source, buffer, &count);
	source.close();

	char* bwtStr = BurrowsWheelerTransform::transform(buffer, count);
	delete[] buffer;

	int zipStrlen = 0;
	char* zipStr = compress(bwtStr, count, &zipStrlen);
	delete[] bwtStr;

	fstream dest(destFile, std::ofstream::out | std::ofstream::trunc);
	string str = to_string(count);
	dest.write(str.c_str(), str.length());
	dest.write("\n", 1);

	str = to_string(zipStrlen);
	dest.write(str.c_str(), str.length());
	dest.write("\n", 1);

	dest.write(zipStr, zipStrlen);
	dest.flush();

	dest.close();

}

void StringCompress::uncompress(const char* sourceFile, const char* destFile)
{
	fstream source(sourceFile);

	char* digits = new char[30]();
	char c = source.get();
	int count = 0;
	while (c != '\n')
	{
		digits[count] = c - '0';
		c = source.get();
		count++;
	}

	int destSize = 0;
	for (int j = count - 1; j > -1; j--)
	{
		destSize += pow(10, count - j - 1) * digits[j];
	}

	int sourceSize = 0;

	count = 0;
	c = source.get();
	while (c != '\n')
	{
		digits[count] = c - '0';
		c = source.get();
		count++;
	}
	for (int j = count - 1; j > -1; j--)
	{
		sourceSize += pow(10, count - j - 1) * digits[j];
	}
	delete[] digits;

	char* srcBuffer = new char[(long long)sourceSize + 1];
	srcBuffer[sourceSize] = '\0';

	count = 0;
	while (count < sourceSize)
	{
		srcBuffer[count] = source.get();
		count++;
	}

	source.close();

	char* destBuffer = uncompress(srcBuffer, destSize);
	delete[] srcBuffer;

	int destDataSize = 0;
	char* destData = BurrowsWheelerTransform::inverseTransform(destBuffer);
	delete[] destBuffer;
	fstream dest(destFile, std::ofstream::out | std::ofstream::trunc);

	dest.write(destData, (long long)destSize - 2);

	dest.flush();

	delete[] destData;

	dest.close();
}
