/*
 * @Author: Leon-Francis
 * @Contact: 15290552788@163.com
 * @Date: 2020-11-25 17:31:55
 * @LastEditTime: 2020-12-02 10:47:54
 * @LastEditors: Leon-Francis
 * @Description: 错误信息
 * @FilePath: /CompilerExperment/WrongMes.h
 * @(C)Copyright 2019-2020, Leon-Francis
 */
#include <string>
#include <vector>
using namespace std;

typedef struct
{
    pair<int, int> wrongPos; //错误的行列号
    string wrongType;        //错误类型
    string wrongMes;         //错误信息
} WrongMessage;

vector<WrongMessage> wrongInfo;