#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <ctype.h>

using namespace std;
struct symbol
{
	string str;
	int coding;
};
string keyword_list[15] = { "BEGIN", "IF", "THEN", "ELSE", "END", "+", "*", "**",
							 "(", ")", "int", "real", ";", "=", ":=" };
string identity[1000] = {};
string buffer = "";
char ch; //读入的字符
char strToken[20] = "";//读入的字符串
int num = 1;//编码的数字（为了递增）
int row = 1;
int add = 0;
int pointer = -1;
string input;
struct symbol keywords[15];

void getNextChar()
{
	pointer++;
	ch = input[pointer];
}

//检查ch的字符是否为空白符、回车或者制表符，若是，则反复调用getNextChar ()，直至ch中读入一非上述符号
void getbc()
{
	while (ch == ' ' || ch == '\t')
	{
		getNextChar();
	}
}

//给单词符号设定种别编码
void initialization() {
	//给关键字设定种别编码
	for (int i = 0; i < 15; i++) {
		keywords[i].str = keyword_list[i];
		if (i < 5)
		{
			keywords[i].coding = num;
		}
		else
		{
			keywords[i].coding = num + 2;
		}
		num++;
	}
}


//判断ch是否为字母
bool isLetter(char ch)
{
	return isalpha(ch);
}

//判断ch是否为数字
bool isDigit(char ch)
{
	return isdigit(ch);
}

//判断ch是否为下划线
bool isUnderline(char ch)
{
	if (ch == '_')
		return 1;
	else
		return 0;
}

//将输入的字符ch连接到strToken
void concat()
{
	char* tmp = &ch;
	strcat(strToken, tmp);
}

//把搜索指针回调一个字符位置
void retract()
{
	pointer--;
}

//对于strToken中的字符串判断它是否为保留字，若它是保留字则返回0，否则返回-1
int reserve_string(char* str) {
	for (int i = 0; i < 15; i++) {
		if (str == keywords[i].str)
		{
			return 0;
		}
	}

	return -1;
}

//若它是保留字则返回编码
int getSCode(char* str)
{
	for (int i = 0; i < 15; i++) {
		if (str == keywords[i].str)
		{
			return keywords[i].coding;
		}
	}
}

//判断标识符是否已经存在
bool isExist(char* str)
{
	for (int i = 0; i < add; i++)
	{
		if (str == identity[i]) return true;
	}
	return false;
}

//新标识符下标
int getAdd(char* str)
{
	int temp = 0;
	while (!(str == identity[temp]))
	{
		temp++;
	}
	return temp;
}

//出错处理
void error(int type, string Token)
{
	switch (type) {
	case 1:
		cout << "Error at Line " << row << ": Illegal floating point number \"" << Token << "\".";
		break;
	}
	exit(0);//抛出错误并终止程序运行
}

//判断是否是int类型
void digit_case() {
	while (isDigit(ch))
	{
		concat();
		getNextChar();
	}
	retract();
	buffer += "line" + to_string(row) + ":(7, " + strToken + ")" + "\n";
}

//词法分析
void LexiscalAnalyzer()
{
	int code = 0;
	strcpy(strToken,"");
	getNextChar();
	if (input[pointer] == '\n')
	{
		row++;
		return;
	}
	getbc();
	
	switch (ch) {
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
		while (isLetter(ch) || isDigit(ch) || isUnderline(ch)) {
			concat();
			getNextChar();
		}
		retract();
		code = reserve_string(strToken);
		if (code == -1)
		{
			if (!isExist(strToken))
			{
				identity[add] = strToken;
				add++;
			}
			buffer += "line" + to_string(row) + ":(6, " + to_string(getAdd(strToken) + 1) + ")" + "\n";
		}
		else if (code == 0)
		{
			buffer += "line" + to_string(row) + ":(" + to_string(getSCode(strToken)) + ", -)" + "\n";
		}
		break;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		digit_case();
		break;
	case '*':
		concat();
		getNextChar();

		if (ch == '*')
		{
			concat();//**
		}
		else
		{
			retract();//*
		}
		buffer += "line" + to_string(row) + ":(" + to_string(getSCode(strToken)) + ", -)" + "\n";
		break;
	case ':':
		concat();
		getNextChar();

		if (ch == '=')
		{
			concat();
		}
		else
		{
			retract();
		}
		buffer += "line" + to_string(row) + ":(" + to_string(getSCode(strToken)) + ", -)" + "\n";
		break;
	case '(':
	case ')':
	case '=':
		concat();
		buffer += "line" + to_string(row) + ":(" + to_string(getSCode(strToken)) + ", -)" + "\n";
		break;
	default:
		if (ch == EOF)
		{
			break;
		}
	}
}

int main()
{
	printf("%s", "请输入源代码：\n");
	initialization();
	string temp;
	getline(cin, temp);

	while (!cin.eof()) {
		input += temp;
		input += "\n";
		getline(cin, temp);
	}

	int n = input.length();
	while (pointer < n)
		LexiscalAnalyzer();
	
	cout << buffer;

	printf("%s", "符号表为： \n");
	printf("%s", "name\tadd\n");

	for (int i = 0; i < add; i++)
	{
		cout << identity[i] << '\t' << (i + 1) << endl;
	}
	return 0;
}
