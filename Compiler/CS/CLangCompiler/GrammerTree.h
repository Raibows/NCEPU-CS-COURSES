/*
 * @Author: Leon-Francis
 * @Contact: 15290552788@163.com
 * @Date: 2020-11-30 12:16:37
 * @LastEditTime: 2020-12-02 10:46:44
 * @LastEditors: Leon-Francis
 * @Description: 语法树
 * @FilePath: /CompilerExperment/GrammerTree.h
 * @(C)Copyright 2019-2020, Leon-Francis
 */
#include "GrammerAnalyze.h"
#ifndef KEYWORDNUM
#include "Tokenize.h"
#endif
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;
//倒序入栈
void ReversePushStack(stack<NodePointer> &tokenStack, NodePointer pointer)
{
    for (int t = pointer->childs.size() - 1; t >= 0; t--)
    {
        tokenStack.push(pointer->childs[t]);
    }
}
//递归下降建立语法树
NodePointer CreateTree(vector<WordToken> wordToken)
{
    //根节点
    NodePointer root = new Node;
    root->name = "Program";
    NodePointer p = root;
    stack<NodePointer> tokenStack;
    tokenStack.push(root);
    int index = 0;
    bool result = true;
    while (index < wordToken.size())
    {
        for (int i = 0; i < productions.size(); i++)
        {
            if (tokenStack.top()->name == productions[i].production)
            {
                tokenStack.pop();
                //判断是否有多个产生式
                if (productions[i].result.size() > 1)
                {
                    int firstIndex = 0;
                    bool match = false;
                    for (firstIndex = 0; firstIndex < productions[i].first.size(); firstIndex++)
                    {
                        for (int j = 0; j < productions[i].first[firstIndex].size(); j++)
                        {
                            if (wordToken[index].name == productions[i].first[firstIndex][j] || (wordToken[index].code == 81 && productions[i].first[firstIndex][j] == "id") || ((wordToken[index].code == 82 || wordToken[index].code == 83) && productions[i].first[firstIndex][j] == "digit"))
                            {
                                match = true;
                                break;
                            }
                        }
                        if (match)
                        {
                            break;
                        }
                    }
                    for (int j = 0; j < productions[i].result[firstIndex].size(); j++)
                    {
                        NodePointer temp = new Node;
                        temp->name = productions[i].result[firstIndex][j].second;
                        temp->type = productions[i].result[firstIndex][j].first;
                        p->childs.push_back(temp);
                        temp->parents = p;
                    }
                    p->procIndex = i;
                }
                else
                {
                    for (int j = 0; j < productions[i].result[0].size(); j++)
                    {
                        NodePointer temp = new Node;
                        temp->name = productions[i].result[0][j].second;
                        temp->type = productions[i].result[0][j].first;
                        temp->procIndex = i;
                        p->childs.push_back(temp);
                        temp->parents = p;
                    }
                    p->procIndex = i;
                }
                ReversePushStack(tokenStack, p);
                break;
            }
        }
        while (!tokenStack.empty() && tokenStack.top()->type == 1)
        {
            if (tokenStack.top()->name == wordToken[index].name || (wordToken[index].code == 81 && tokenStack.top()->name == "id") || ((wordToken[index].code == 82 || wordToken[index].code == 83) && tokenStack.top()->name == "digit"))
            {
                if (wordToken[index].code == 81 && tokenStack.top()->name == "id")
                {
                    p->place = wordToken[index].name;
                    p->symbleIndex = wordToken[index].addr;
                }
                else if ((wordToken[index].code == 82 || wordToken[index].code == 83) && tokenStack.top()->name == "digit")
                {
                    p->place = wordToken[index].name;
                    p->symbleIndex = wordToken[index].addr;
                }
                tokenStack.pop();
                index++;
            }
            else if (tokenStack.top()->name == "empty")
            {
                tokenStack.pop();
            }
            else
            {
                cout << "Production Error" << endl;
                return NULL;
            }
        }
        if (!tokenStack.empty())
        {
            p = tokenStack.top();
        }
    }
    if (tokenStack.empty())
    {
        cout << "Create grammer tree complete!" << endl;
        return root;
    }
    else
    {
        cout << "Create grammer tree Error" << endl;
        return NULL;
    }
}
//判断属性是否全部计算
bool IfAllCalculate(NodePointer root)
{
    for (int i = 0; i < root->childs.size(); i++)
    {
        if (!IfAllCalculate(root->childs[i]))
        {
            return false;
        }
    }
    return true;
}
//深度遍历节点，计算属性
void VisitNode(NodePointer p, bool print = false)
{
    if (p->type == 0)
    {
        for (int i = 0; i < p->childs.size(); i++)
        {
            if (p->childs[i]->type == 0)
            {
                VisitNode(p->childs[i], print);
            }
        }
        if (productions[p->procIndex].func != NULL)
        {
            productions[p->procIndex].func(p, print);
        }
    }
}
//计算继承属性
void CalculateAttr(NodePointer root)
{
    VisitNode(root, false);
    while (!IfAllCalculate(root))
    {
        VisitNode(root, false);
    }
}
//计算综合属性，打印四元式
void Print4Element(NodePointer root)
{
    VisitNode(root, true);
    cout << "4-Elements are as follows:" << endl;
    cout << endl;
    for (int i = 0; i < outputResult.size(); i++)
    {
        cout << outputResult[i].addr << "  " << outputResult[i].op << "  " << outputResult[i].num1 << "  " << outputResult[i].num2 << "  " << outputResult[i].num3 << endl;
    }
}