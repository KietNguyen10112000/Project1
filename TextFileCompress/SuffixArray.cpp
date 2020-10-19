#include "SuffixArray.h"
struct FirstSfCompare
{
	char* str;
	FirstSfCompare(char* str)
	{
		this->str = str;
	}

	bool operator () (int i, int j)
	{
		return str[i] < str[j];
	}
};
struct SfCompare {
	int jump;
	int* index;
	SfCompare(int* index, int jump)
	{
		this->index = index;
		this->jump = jump;	
	}

	bool operator () (int i, int j)
	{
		if (index[i] == index[j])
		{
			return index[i + jump] < index[j + jump];
		}
		return index[i] < index[j];

	}

};

struct NormalSfCompare {
	char* str;
	NormalSfCompare(char* str)
	{
		this->str = str;
	}

	bool operator () (int i, int j)
	{
		return strcmp(&str[i], &str[j]) < 0;

	}

};

unsigned char SuffixArray::manySfArr = 0;

SuffixArray::SuffixArray(char* str, int strlen)
{

	if (manySfArr < MAX_SF_ARR_AT_TIME)
	{
		this->strlen = strlen;
		this->str = str;
		manySfArr++;
		makeSuffixArrayNormal();
	}
	else {
		throw "Cannot initializing more SuffixArray at the moment !!!";
		exit(-1);
	}
	
}

SuffixArray::~SuffixArray()
{
#ifdef DEBUG
	
#else
	delete[] sfArr;
#endif
	
	manySfArr--;
}

void SuffixArray::firstCalculateIndexArr(int* index)
{
	count = 0;
	for (int i = 0; i < strlen - 1; i++)
	{
		index[sfArr[i]] = firstCalculateIndex(sfArr[i], sfArr[(long long)i + 1]);
	}
	index[sfArr[(long long)strlen - 1]] = count;
}

int SuffixArray::firstCalculateIndex(int i, int j)
{
	if (str[i] != str[j])
	{
		int result = count;
		count++;
		return result;
	}
	return count;
}

void SuffixArray::calculateIndexArr(int* index, int deep, int* outIndex)
{
	count = 0;
	for (int i = 0; i < strlen - 1; i++)
	{
		outIndex[sfArr[i]] = calculateIndex(sfArr[i], sfArr[(long long)i + 1], deep, index);
	}
	outIndex[sfArr[(long long)strlen - 1]] = count;
}

int SuffixArray::calculateIndex(int i, int j, int deep, int* index)
{
	while (deep != 0)
	{
		deep = deep / 2;
		if (i + deep > strlen - 1 || j + deep > strlen - 1)
		{
			int result = count;
			count++;
			return result;
		}
		if (index[i + deep] != index[j + deep])
		{
			int result = count;
			count++;
			return result;
		}
	}
	return count;
}
//this is the better one (4mb take 20s)
void SuffixArray::makeSuffixArrayNormal()
{
	sfArr = new int[strlen];

	for (int i = 0; i < strlen; i++)
	{
		sfArr[i] = i;
	}

	sort(&sfArr[0], &sfArr[strlen], NormalSfCompare(str));
}
//this's only O(n*Log(n)^2) on paper but so bad in reality (4mb take 260s ~ 300s)
void SuffixArray::makeSuffixArrayFast()
{

//#ifdef DEBUG
	//sfArr = vector<int>(strlen);
	//vector<int> index1(strlen, 0);
	//vector<int> index2(strlen, 0);
//#else
	sfArr = new int[strlen];
	int* index1 = new int[strlen]();
	int* index2 = new int[strlen]();
//#endif

	for (int i = 0; i < strlen; i++)
	{
		sfArr[i] = i;
	}

	SfCompare cmp(&index1[0], 0);
	
//#ifdef DEBUG
	//sort(sfArr.begin(), sfArr.end(), FirstSfCompare(str));
//#else
	sort(&sfArr[0], &sfArr[strlen], FirstSfCompare(str));
//#endif 
	firstCalculateIndexArr(&index1[0]);

	int i = 1;
	
	bool flag = true;
	while (i  < this->strlen)
	{
		cmp.jump = i;
		if (flag)
		{
			calculateIndexArr(&index1[0], i, &index2[0]);
			cmp.index = &index2[0];
		}
		else
		{
			calculateIndexArr(&index2[0], i, &index1[0]);
			cmp.index = &index1[0];
		}
		flag = !flag;
		
		
//#ifdef DEBUG
		//sort(sfArr.begin(), sfArr.end(), cmp);
//#else
		sort(&sfArr[0], &sfArr[strlen], cmp);
//#endif 
		
		i = i * 2;
	}
//#ifdef DEBUG
	
//#else
	delete[] index1;
	delete[] index2;
//#endif
}

void SuffixArray::print()
{
	for (int i = 0; i < strlen; i++)
	{
		cout << sfArr[i] << " ";
	}
	cout << endl;
}