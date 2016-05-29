#include <iostream>
#include "BigData.h"
/*
	待修改：
	1、BigData bigData("+a123456789123456789");   输出的0 不是我们想要的
	2、构造函数处理
	3、相加 不应该进入的IF语句

*/

using namespace std;

//void Test_GetSize()
//{
//	BigData data1;
//	size_t ret = data1._GetSize(-199);
//	cout << ret << endl;
//}


/*
		加法的测试：
		1、都没有溢出
				同号
				异号
		2、有一个溢出
		3、两个都溢出
		4、再交换加数的顺序，重复测
		5、以上情况考虑一下进位
		（应该全部通过）
*/
void AddTest1()
{
	BigData data1(-20);
	BigData data2(-30);
	BigData data3;
	data3 = data1 + data2;
	BigData data4(20);
	BigData data5(-30);
	BigData data6 = data4 + data5;
	BigData data7("20");
	BigData data8("30");
	BigData data9 = data7 + data8;
	BigData data10("-20");
	BigData data11("-30");
	BigData data12 = data10 + data11;

}

void AddTest2()
{
	BigData data1("2222222222222222222222222");
	BigData data2(33);
	BigData data3 = data1 + data2;

	BigData data4("2222222222222222222222222");
	BigData data5(-33);
	BigData data6 = data4 + data5;

	BigData data7(33);
	BigData data8("2222222222222222222222222");
	BigData data9 = data7 + data8;

	BigData data10("33333333333333333333333333");
	BigData data11("2222222222222222222222222");
	BigData data12 = data10 + data11;

	BigData data13("222222222222222222222222222");
	BigData data14("999999999999999222222222222");
	BigData data15 = data13 + data14;
}


/*
	减法的测试：
	1、都没有溢出
		符号相同
		符号不同
	2、有一个溢出
	3、两个都溢出
	4、以上情况考虑借位
	（应该没问题）
*/

void SubTest1()
{
	BigData data1(33);
	BigData data2(22);
	BigData data3 = data1 - data2;
	data3 = data2 - data1;

	BigData data4(33);
	BigData data5(-22);
	BigData data6 = data4 - data5;
	data3 = data5 - data4;

	BigData data7("222222222222222222222222222222");
	BigData data8("111111111111111111111111111111");
	data3 = data7 - data8;
	data3 = data8 - data7;

	BigData data13;
	BigData data9("-222222222222222222222222222222");
	BigData data10("111111111111111111111111111111");
	data13 = data9 - data10;
	data13 = data10 - data9;

	BigData data11("-222222222222222222222222222222");
	BigData data12("-111111111111111111111111111111");
	data13 = data11 - data12;
	data13 = data12 - data11;
}

string Mul(string left, string right)
{
	int LSize = left.size();
	int RSize = right.size();
	if (LSize > RSize)
	{
		swap(left, right);
		swap(LSize, RSize);
	}
	char cSymbol = '+';
	string strRet;
	strRet.resize(LSize + RSize - 1);
	if (left[0] != right[0])
	{
		cSymbol = '-';
	}
	strRet[0] = cSymbol;

	char cStep = 0;		//进位
	int  Datalen = strRet.size();
	int offset = 0;		//错位
	for (int i = 1; i < Datalen; ++i)
	{
		strRet[i] += '0';
	}
	for (int iLidx = 1; iLidx < LSize; ++iLidx)
	{
		char cLeft = left[LSize - iLidx] - '0';
		cStep = 0;
		if (cLeft == 0)
		{
			offset++;
			continue;
		}
		for (int iRidx = 1; iRidx < RSize; ++iRidx)    
		{
			char cRet = cLeft * (right[RSize - iRidx] - '0');
//			cRet += (strRet[RSize - iRidx - offset] - '0');
			cRet += cStep;
			cStep = cRet / 10;
			strRet[Datalen - iRidx - offset] += (cRet % 10);
			while (strRet[Datalen - iRidx - offset] > '9')
			{
				++cStep;
				strRet[Datalen - iRidx - offset] -= 10;
			}
		}
		strRet[Datalen - RSize - offset] += cStep;
		++offset;
	}

	return strRet;
}

/*
	对Mul方法的单独测试
*/
void TestBigDataMul()
{
	string ret = Mul("+11", "+666");
	cout << ret << endl;
}


/*
乘法的测试：
1、两个数都没有超出范围
结果也没有超出范围
结果超出了范围
2、其中一个数超出了范围
3、两个数都超出了范围
4、以上情况，考虑同号、异号
（应该没问题）
*/
void MulTest()
{
	BigData data1(12);
	BigData data2(-11);
	BigData data3 = data1 * data2;

	BigData data4("-1111111111111111111111111111111111");
	BigData data5(2);
	data3 = data4 * data5;

	BigData data6("-1111111111111111");
	BigData data7("2222222222222222");
	data3 = data6 * data7;
}

/*
	除法的测试：
	1、右数为 0 的情况
	2、左右两数都没有超出
	3、其中至少一个数超出
	4、以上情况，改变两数的正负号
	5、考虑左数含有0 及 借位 的情况
*/
void DivTest1()
{
	BigData data1(33);
	BigData data2(11);
	BigData data3 = data1 / data2;
	data3 = data2 / data1;

	BigData data4(-33);
	BigData data5(11);
	data3 = data4 / data5;
	data3 = data5 / data4;


	BigData data6("33333333333333333333333333333333333333");
	BigData data7(1);
	data3 = data6 / data7;
	data3 = data7 / data6;
}

void DivTest2()
{
	BigData data1("333333333333333333333333");
	BigData data2("111111111111111111111111");
	BigData data3 = data1 / data2;
	data3 = data2 / data1;

	BigData data4("111111111111111111111111");
	BigData data5("222222222222");
	data3 = data4 / data5;
	data3 = data5 / data4;

	BigData data6("10000000000000000000");
	BigData data7(2);
	data3 = data6 / data7;
}
int main()
{
	DivTest2();
	return 0;
}

