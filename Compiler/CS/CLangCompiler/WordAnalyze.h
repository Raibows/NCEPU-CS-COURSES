/*
 * @Author: Leon-Francis
 * @Contact: 15290552788@163.com
 * @Date: 2020-11-25 17:31:55
 * @LastEditTime: 2020-12-02 10:47:27
 * @LastEditors: Leon-Francis
 * @Description: 词法分析过程
 * @FilePath: /CompilerExperment/WordAnalyze.h
 * @(C)Copyright 2019-2020, Leon-Francis
 */
#ifndef KEYWORDNUM
#include "Tokenize.h"
#endif
#include "WrongMes.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void readFile(string inPath, vector<string> &allText)
{
    //TODO: 由于时间有限，暂时写不了预处理过程
    ifstream inFile(inPath.c_str());
    if (!inFile.is_open())
    {
        cerr << "open file failed!" << endl;
        exit(-1);
    }
    string temp;
    while (getline(inFile, temp))
    {
        allText.push_back(temp + '\n');
    }
    inFile.close();
    cout << "original programs are as follows:" << endl;
    for (int i = 0; i < allText.size(); i++)
    {
        cout << allText[i];
    }
    return;
}

int isKeyWord(string str, int index) //最大匹配关键字
{
    if (str != "")
    {
        for (int j = min(KEYWORDMAXLEN, int(str.size()) - index); j > 0; j--)
        {
            for (int i = 0; i < KEYWORDNUM; i++)
            {
                if (str.substr(index, j) == keyWord[i].name)
                {
                    return keyWord[i].code;
                }
            }
        }
    }
    return 0;
}

int isOperator(string str, int index) //最大匹配算符
{
    if (str != "")
    {
        for (int j = min(OPERATORWORDMAXLEN, int(str.size()) - index); j > 0; j--)
        {
            for (int i = 0; i < OPERATORWORDNUM; i++)
            {
                if (str.substr(index, j) == operatorWord[i].name)
                {
                    return operatorWord[i].code;
                }
            }
        }
    }

    return 0;
}

int isDelimeter(string str, int index) //最大匹配界符
{
    if (str != "")
    {
        for (int j = min(DELIMETERMAXLEN, int(str.size()) - index); j > 0; j--)
        {
            for (int i = 0; i < DELIMETERNUM; i++)
            {
                if (str.substr(index, j) == delimeter[i].name)
                {
                    return delimeter[i].code;
                }
            }
        }
    }
    return 0;
}

string isId(string str, int index) //识别标识符的自动机
{
    if (str != "")
    {
        if (isalpha(str[index]) || str[index] == '_')
        {
            int num = 1;
            while (isalpha(str[index + num]) || isdigit(str[index + num]) || str[index + num] == '_')
            {
                num++;
            }
            return str.substr(index, num);
        }
    }
    return "";
}

string isInteger(string str, int index) //识别整数的自动机
{
    if (str != "")
    {
        if (isdigit(str[index]))
        {
            int num = 1;
            while (isdigit(str[index + num]))
            {
                num++;
            }
            return str.substr(index, num);
        }
    }
    return "";
}

string isRealNum(string str, int index) //识别实数的自动机
{
    if (str != "")
    {
        if (isdigit(str[index]))
        {
            int num = 1;
            while (isdigit(str[index + num]))
            {
                num++;
            }
            if (str[index + num] == 'E' || str[index + num] == 'e')
            {
                num++;
                if (isdigit(str[index + num]))
                {
                    num++;
                    while (isdigit(str[index + num]))
                    {
                        num++;
                    }
                    return str.substr(index, num);
                }
            }
            else if (str[index + num] == '.')
            {
                num++;
                while (isdigit(str[index + num]))
                {
                    num++;
                }
                if (str[index + num] == 'E' || str[index + num] == 'e')
                {
                    num++;
                    if (str[index + num] == '+' || str[index + num] == '-')
                    {
                        num++;
                    }
                    if (isdigit(str[index + num]))
                    {
                        num++;
                        while (isdigit(str[index + num]))
                        {
                            num++;
                        }
                        return str.substr(index, num);
                    }
                }
                else
                {
                    return str.substr(index, num);
                }
            }
        }
        else if (str[index] == '.')
        {
            int num = 1;
            if (isdigit(str[index + num]))
            {
                num++;
                while (isdigit(str[index + num]))
                {
                    num++;
                }
                if (str[index + num] == 'E' || str[index + num] == 'e')
                {
                    num++;
                    if (str[index + num] == '+' || str[index + num] == '-')
                    {
                        num++;
                    }
                    if (isdigit(str[index + num]))
                    {
                        num++;
                        while (isdigit(str[index + num]))
                        {
                            num++;
                        }
                        return str.substr(index, num);
                    }
                }
                else
                {
                    return str.substr(index, num);
                }
            }
        }
    }
    return "";
}

string isString(string str, int index) //识别字符串的自动机
{
    if (str != "")
    {
        if (index > 0 && str[index - 1] == '\"')
        {
            int num = 1;
            while (str[index + num] != '\"')
            {
                num++;
            }
            return str.substr(index, num);
        }
        else if (index > 0 && str[index - 1] == '\'')
        {
            int num = 1;
            if (str[index + 1] == '\'')
            {
                return str.substr(index, num);
            }
        }
    }
    return "";
}

string code2Name(int code) //token编码转换为name
{
    if (code <= KEYWORDNUM)
    {
        return keyWord[code - keyWord[0].code].name;
    }
    else if (code <= KEYWORDNUM + OPERATORWORDNUM)
    {
        return operatorWord[code - operatorWord[0].code].name;
    }
    else
    {
        return delimeter[code - delimeter[0].code].name;
    }
}

void text2Token(vector<string> allText)
{
    for (int lineI = 0; lineI < allText.size(); lineI++)
    {
        string lineText = allText[lineI];
        int index = 0;
        while (index != lineText.size())
        {
            if (isspace(lineText[index]))
            {
                index++;
                continue;
            }
            else if (isString(lineText, index) != "")
            {
                //将字符型常数插入到Token和符号表
                WordSymble tempSymble;
                tempSymble.number = wordSymble.size();
                tempSymble.name = isString(lineText, index);
                tempSymble.type = "string";
                tempSymble.stringValue = tempSymble.name;
                wordSymble.push_back(tempSymble);
                WordToken tempToken;
                tempToken.name = tempSymble.name;
                tempToken.code = 84;
                tempToken.label = wordToken.size();
                tempToken.addr = tempSymble.number;
                tempToken.pos.first = lineI + 1;
                tempToken.pos.second = index + 1;
                wordToken.push_back(tempToken);
                index += tempToken.name.size();
                continue;
            }
            else if (isKeyWord(lineText, index))
            {
                //将关键字插入到Token表
                WordToken temp;
                temp.code = isKeyWord(lineText, index);
                temp.name = code2Name(temp.code);
                temp.label = wordToken.size();
                temp.addr = 0;
                temp.pos.first = lineI + 1;
                temp.pos.second = index + 1;
                wordToken.push_back(temp);
                index += temp.name.size();
                continue;
            }
            else if (isOperator(lineText, index))
            {
                //将运算符插入到Token表
                WordToken temp;
                temp.code = isOperator(lineText, index);
                temp.name = code2Name(temp.code);
                temp.label = wordToken.size();
                temp.addr = 0;
                temp.pos.first = lineI + 1;
                temp.pos.second = index + 1;
                wordToken.push_back(temp);
                index += temp.name.size();
                continue;
            }
            else if (isDelimeter(lineText, index))
            {
                //将界符插入Token表
                WordToken temp;
                temp.code = isDelimeter(lineText, index);
                temp.name = code2Name(temp.code);
                temp.label = wordToken.size();
                temp.addr = 0;
                temp.pos.first = lineI + 1;
                temp.pos.second = index + 1;
                wordToken.push_back(temp);
                index += temp.name.size();
                continue;
            }
            else if (isRealNum(lineText, index) != "")
            {
                //将实数插入到Token和符号表
                WordSymble tempSymble;
                tempSymble.number = wordSymble.size();
                tempSymble.name = isRealNum(lineText, index);
                tempSymble.type = "double";
                //做一步差错检测
                try
                {
                    tempSymble.doubleValue = stod(tempSymble.name);
                }
                catch (invalid_argument &)
                {
                    WrongMessage wrong;
                    wrong.wrongPos.first = lineI + 1;
                    wrong.wrongPos.second = index + 1;
                    wrong.wrongType = "Invalid_argument";
                    wrong.wrongMes = tempSymble.name + " may is not a Realnum";
                    wrongInfo.push_back(wrong);
                }
                catch (out_of_range &)
                {
                    WrongMessage wrong;
                    wrong.wrongPos.first = lineI + 1;
                    wrong.wrongPos.second = index + 1;
                    wrong.wrongType = "Out_of_range";
                    wrong.wrongMes = tempSymble.name + " would fall out of the range of double";
                    wrongInfo.push_back(wrong);
                }
                catch (...)
                {
                    WrongMessage wrong;
                    wrong.wrongPos.first = lineI + 1;
                    wrong.wrongPos.second = index + 1;
                    wrong.wrongType = "IDK";
                    wrong.wrongMes = tempSymble.name + " <==someing wrong happen and I dont know";
                    wrongInfo.push_back(wrong);
                }
                wordSymble.push_back(tempSymble);
                WordToken tempToken;
                tempToken.name = tempSymble.name;
                tempToken.code = 83;
                tempToken.label = wordToken.size();
                tempToken.addr = tempSymble.number;
                tempToken.pos.first = lineI + 1;
                tempToken.pos.second = index + 1;
                wordToken.push_back(tempToken);
                index += tempToken.name.size();
                continue;
            }
            else if (isInteger(lineText, index) != "")
            {
                //将整数插入到Token和符号表
                WordSymble tempSymble;
                tempSymble.number = wordSymble.size();
                tempSymble.name = isInteger(lineText, index);
                tempSymble.type = "int";
                //做一步差错检测
                try
                {
                    tempSymble.intValue = stoi(tempSymble.name);
                }
                catch (invalid_argument &)
                {
                    WrongMessage wrong;
                    wrong.wrongPos.first = lineI + 1;
                    wrong.wrongPos.second = index + 1;
                    wrong.wrongType = "Invalid_argument";
                    wrong.wrongMes = tempSymble.name + " may is not an Integer";
                    wrongInfo.push_back(wrong);
                }
                catch (out_of_range &)
                {
                    WrongMessage wrong;
                    wrong.wrongPos.first = lineI + 1;
                    wrong.wrongPos.second = index + 1;
                    wrong.wrongType = "Out_of_range";
                    wrong.wrongMes = tempSymble.name + " would fall out of the range of Integer";
                    wrongInfo.push_back(wrong);
                }
                catch (...)
                {
                    WrongMessage wrong;
                    wrong.wrongPos.first = lineI + 1;
                    wrong.wrongPos.second = index + 1;
                    wrong.wrongType = "IDK";
                    wrong.wrongMes = tempSymble.name + " <==someing wrong happen and I dont know";
                    wrongInfo.push_back(wrong);
                }
                wordSymble.push_back(tempSymble);
                WordToken tempToken;
                tempToken.name = tempSymble.name;
                tempToken.code = 82;
                tempToken.label = wordToken.size();
                tempToken.addr = tempSymble.number;
                tempToken.pos.first = lineI + 1;
                tempToken.pos.second = index + 1;
                wordToken.push_back(tempToken);
                index += tempToken.name.size();
                continue;
            }
            else if (isId(lineText, index) != "")
            {
                //将标识符插入到Token和符号表
                WordToken tempToken;
                //查找符号表中有无该id，没有则重新创建
                bool ifHaveId = false;
                string id = isId(lineText, index);
                for (int i = 0; i < wordSymble.size(); i++)
                {
                    if (wordSymble[i].name == id)
                    {
                        ifHaveId = true;
                        tempToken.addr = i;
                        break;
                    }
                }
                if (!ifHaveId)
                {
                    WordSymble tempSymble;
                    tempSymble.number = wordSymble.size();
                    tempSymble.name = id;
                    wordSymble.push_back(tempSymble);
                    tempToken.addr = tempSymble.number;
                }
                tempToken.name = id;
                tempToken.code = 81;
                tempToken.label = wordToken.size();
                tempToken.pos.first = lineI + 1;
                tempToken.pos.second = index + 1;
                wordToken.push_back(tempToken);
                index += tempToken.name.size();
                continue;
            }
            else
            {
                //记录错误信息，跳转到下一行
                WrongMessage wrong;
                wrong.wrongPos.first = lineI + 1;
                wrong.wrongPos.second = index + 1;
                wrong.wrongType = "Syntax error";
                int num = 1;
                while (!isspace(lineText[index + num]) && !isOperator(lineText, index + num) && !isOperator(lineText, index + num))
                {
                    num++;
                }
                wrong.wrongMes = "Unknow word: " + lineText.substr(index, num);
                wrongInfo.push_back(wrong);
                index = lineText.size();
            }
        }
    }
    cout << "Word analyze finished" << endl;
}

void printAll() //打印token信息以及符号表以及错误信息
{
    cout << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Token table is as follows:" << endl;
    cout << "label\t\tname\t\tcode\t\taddr\t\tpos" << endl;
    for (int i = 0; i < wordToken.size(); i++)
    {
        cout << wordToken[i].label << "\t\t" << wordToken[i].name << "\t\t" << wordToken[i].code << "\t\t" << wordToken[i].addr << "\t\t" << wordToken[i].pos.first << " " << wordToken[i].pos.second << endl;
    }
    cout << "-----------------------------------------------" << endl;
    cout << "Symble table is as follows:" << endl;
    cout << "number\t\tname\t\ttype\t\tvalue" << endl;
    for (int i = 0; i < wordSymble.size(); i++)
    {
        cout << wordSymble[i].number << "\t\t" << wordSymble[i].name << "\t\t" << wordSymble[i].type << "\t\t";
        if (wordSymble[i].type == "int")
        {
            cout << wordSymble[i].intValue << endl;
        }
        else if (wordSymble[i].type == "double")
        {
            cout << wordSymble[i].doubleValue << endl;
        }
        else if (wordSymble[i].type == "string")
        {
            cout << wordSymble[i].stringValue << endl;
        }
        else
        {
            cout << endl;
        }
    }
    cout << "-----------------------------------------------" << endl;
    cout << "wrongInfo table is as follows:" << endl;
    cout << "pos\t\twrongType\t\twrongMes" << endl;
    for (int i = 0; i < wrongInfo.size(); i++)
    {
        cout << wrongInfo[i].wrongPos.first << " " << wrongInfo[i].wrongPos.second << "\t\t" << wrongInfo[i].wrongType << "\t\t" << wrongInfo[i].wrongMes << endl;
    }
    cout << "-----------------------------------------------" << endl;
}