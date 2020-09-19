#include<iostream>
#include<string>
#include<fstream>
#include <cassert>
#include<vector>
#include "word_ana.h"
#include "Table.h"
#include "aimCode.h"
using namespace std;

int main(){
	string url;
	cout << "请输入源程序文件路径：" << endl; //D:/1.txt
	cin >> url;
	readtext(url);
	writeToken();
	writeToken1();
	

	Table t;
	readToken();			//输出token集
	string Error;
	bool b = t.Match(token2, Error);  //完成优先关系表，语法树，输出符号栈
	if (!b) { cout << Error << endl; return 0; }
	else cout << "规约成功" << endl;
	printGens();					//输出四元式
	

	aimCode aimcode;
	aimcode.writecodes();
	system("pause");
	return 0;
}