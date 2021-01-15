#include <iostream>

int fileSize = 0;

#include "BurrowsWheelerTransform.h"
#include "StringCompress.h"
#include <Windows.h>
#include <thread>
#include <string>

using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

int main()
{
	//char* str = (char*)"Java's popularity continued to decline this month, \
almost clearing the path for Python to snatch its spot as the world's second most popular programming language, \
according to Tiobe's latest programming language rankings. \n\
If Python does overtake Java, it would mark the first time since Tiobe began its programming \
language popularity index in that Java would be outside the top two spots. As Tiobe CEO Paul Jansen notes, \
C and Java have held the top two spots consistently for two decades. \
But today-year-old Java is approaching its -time y, falling percentage points compared with October.$";

	/*char* str = (char*)"Java's popularity continued to decline this month, \
almost clearing the path for Python to snatch its spot as the world's second most popular programming language, \
according to Tiobe's latest programming language rankings. \
If Python does overtake Java, it would mark the first time since Tiobe began its programming \
language popularity index in 2001 that Java would be outside the top two spots. As Tiobe CEO Paul Jansen notes, \
C and Java have held the top two spots consistently for two decades. \
But today 25-year-old Java is approaching its -time y, falling 4.32 percentage points compared with October 2019.\n\n\n$";

	int strL = strlen(str);

	char* bwtStr = BurrowsWheelerTransform::transform(str, strL);

	int zipStrlen = 0;
	char* zipStr = StringCompress::compress(bwtStr, strL, &zipStrlen);

	char* unZipStr = StringCompress::uncompress(zipStr, strL);

	char* oriStr = BurrowsWheelerTransform::inverseTransform(unZipStr);


	cout << bwtStr << endl;

	cout << endl << oriStr << endl;

	cout << endl << zipStr << endl;

	cout << endl << unZipStr << endl;*/

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
	//long long start = GetTickCount64();
	//StringCompress::multiThreadCompress("D:\\Project1\\TextFileExsample\\bible.txt", "compressText.txt", 4, 1 * 1024 * 1024, 1.5 * 1024 * 1024);
	//cout << "Compressed Sucessfully !!!" << endl;

	//cout << endl << "Compress Time: " << (GetTickCount64() - start) << endl;

	//StringCompress::uncompress("compressText.txt", "textFile.txt");
	//cout << "Uncompressed Sucessfully !!!" << endl;

	cout << "Ho ten: Nguyen Huu Kiet\nMSSV: 20183571\n*********************************\nCHUONG TRINH NEN FILE TEXT DEMO\
		\n*********************************\n";

	int chosen = 0;
	string filePath = "";
	string savePath = "";

	while (true)
	{
		cout << "\n*********************************\nChon lua chon: \n\
			\n1. Nen file text.\n\n2. Giai nen file txt_zip.\n\n3. Thoat.\n\nNhap lua chon: ";
		//cin >> chosen;
		cin >> chosen;

		while (chosen != 1 && chosen != 2 && chosen != 3)
		{
			cout << "Khong co lua chon nao thoa man !!!\nMoi ban chon lai: ";
			cin >> chosen;
		}

		if (chosen == 1)
		{
			cout << "\nBan da chon nen file !!!\n\n";
			cout << "File path: ";
			getline(cin, filePath);
			getline(cin, filePath);
			cout << "So luong thread dung song song: ";
			int numthread = 1;
			cin >> numthread;
			while (numthread < 1)
			{
				cout << "So luong thread khong hop le, nhap lai: ";
				cin >> numthread;
			}

			savePath = filePath + "_zip";

			try
			{
				fileSize = StringCompress::getFileSize(filePath.c_str());
				int min = 0, max = 0;
				if (fileSize < 10 * 1024 * 1024)
				{
					min = fileSize / numthread;
					max = min + 0.5 * 1024 * 1024;
				}
				else if (fileSize < 100 * 1024 * 1024)
				{
					min = fileSize / (numthread * 2);
					max = min + 2 * 1024 * 1024;
				}
				else if(fileSize < 500 * 1024 * 1024)
				{
					min = fileSize / (numthread * 8);
					max = min + 3 * 1024 * 1024;
				}
				else if (fileSize < 1024 * 1024 * 1024)
				{
					min = fileSize / (numthread * 16);
					max = min + 4 * 1024 * 1024;
				}
				else 
				{
					min = fileSize / (numthread * 16);
					max = min + 6 * 1024 * 1024;
					numthread = numthread * 2;
				}
				cout << "Processing: 0%";
				StringCompress::multiThreadCompress(filePath.c_str(), savePath.c_str(),
					numthread, min, max);

				cout << "\nFile nen cua ban da duoc luu tai: " << savePath << "\n\n";
				system("pause");
			}
			catch (const char* e)
			{
				cout << e << endl;
			}

		}
		else if (chosen == 2)
		{
			cout << "\nBan da chon giai nen file !!!\n\n";
			cout << "File path: ";
			getline(cin, filePath);
			getline(cin, filePath);
			
			fs::path _filePath = filePath;

			std::wstring ext = _filePath.extension().c_str();
			std::transform(ext.begin(), ext.end(), ext.begin(),
				[](unsigned char c) { return std::tolower(c); });

			savePath = filePath + "_unzip.txt";

			if (L".txt_zip" == ext) // Heed the dot.
			{
				StringCompress::uncompress(filePath.c_str(), savePath.c_str());
			}
			else
			{
				cout << "File sai dinh dang !!!\n";
			}

			cout << "\nFile giai nen cua ban da duoc luu tai: " << savePath << "\n\n";
			system("pause");
		}
		else if (chosen == 3)
		{
			break;
		}
		
	}

	return 0;
}