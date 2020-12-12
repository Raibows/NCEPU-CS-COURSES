/*
 * @Author: Leon-Francis
 * @Contact: 15290552788@163.com
 * @Date: 2020-12-01 16:21:13
 * @LastEditTime: 2020-12-02 10:46:25
 * @LastEditors: Leon-Francis
 * @Description: 顶层文件
 * @FilePath: /CompilerExperment/main.cpp
 * @(C)Copyright 2019-2020, Leon-Francis
 */

#include "GrammerTree.h"
#include "WordAnalyze.h"
#include <iostream>
#include <vector>

using namespace std;

void readFile(string inPath, vector<string> &allText);

int main(int argc, char const *argv[])
{
    string inPath;
    inPath = ".\\TestCode.txt";
    vector<string> allText;
    readFile(inPath, allText);
    text2Token(allText); //词法分析
    printAll();
    cout << endl;
    initProduction(); //初始化产生式
    NodePointer root;
    root = CreateTree(wordToken); //建立语法分析树
    CalculateAttr(root);          //计算继承属性
    Print4Element(root);          //计算综合属性以及打印四元式
    return 0;
}
