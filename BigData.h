#ifndef __BIG_DATA_H__
#define __BIG_DATA_H__
#include <iostream>
#include <string>
using namespace std;

typedef long long INT64;
#define UN_INIT	0xCCCCCCCCCCCCCCCC             //一开始的随机值
#define MAX_INT64 0x7FFFFFFFFFFFFFFF
#define MIN_INT64 0x8000000000000000

class BigData
{
public:
	BigData(INT64 value = UN_INIT);
	BigData(char *pData );

	BigData operator+ (const BigData &bigData);
	BigData operator- (const BigData &bigData);
	BigData operator* (const BigData &bigData);
	BigData operator/ (const BigData &bigData);

	string Add(string left, string right);
	string Sub(string left, string right);
	string Mul(string left, string right);
	string Div(string left, string right);


	bool IsINT64Overflow() const;
	friend ostream &operator<<(ostream &os, BigData &bd);



protected:
	char SubLoop(char* pLeft, int LSize, char *pRight, int RSize);
	bool IsLeftBig(char* pLeft, int LSize, char *pRight, int RSize);
//public:
	INT64 _value;
	string _strData;
};

#endif
