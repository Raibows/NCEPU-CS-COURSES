/*
 * @Author: Leon-Francis
 * @Contact: 15290552788@163.com
 * @Date: 2020-12-02 01:16:21
 * @LastEditTime: 2020-12-02 10:47:05
 * @LastEditors: Leon-Francis
 * @Description: 文法产生式
 * @FilePath: /CompilerExperment/GrammerAnalyze.h
 * @(C)Copyright 2019-2020, Leon-Francis
 */
#include <string>
#include <vector>
using namespace std;

#define BEGINADDR 100
int tempnum = 0;

typedef struct  //四元式结果
{
    int addr;
    string op;
    string num1;
    string num2;
    string num3;
} OutputResult;
vector<OutputResult> outputResult;
int address = BEGINADDR;

typedef struct Node //语法树节点
{
    //属性
    string name = "";
    string place = "";
    int symbleIndex = -1;
    bool complete = true;
    int type = 0;
    vector<int> trueaddr;
    vector<int> falseaddr;
    vector<int> nextaddr;
    int printAddress = -1;
    int quad = -1;
    int procIndex;

    //指针
    struct Node *parents;
    vector<struct Node *> childs;

} * NodePointer;

typedef struct  //产生式节点
{
    string production = "";
    vector<vector<pair<int, string>>> result;
    void (*func)(NodePointer pointer, bool print) = NULL;
    vector<vector<string>> first;
} Production;

vector<Production> productions;

string newTemp()
{
    return "T" + to_string(tempnum++);
}

void BackPatch(vector<int> backAddr, int quad)
{
    for (int i = 0; i < backAddr.size(); i++)
    {
        outputResult[backAddr[i] - BEGINADDR].num3 = to_string(quad);
    }
}

void Merge(vector<int> e1, vector<int> &e3)
{
    for (int i = 0; i < e1.size(); i++)
    {
        bool ifMerge = true;
        for (int j = 0; j < e3.size(); j++)
        {
            if (e1[i] == e3[j])
            {
                ifMerge = false;
                break;
            }
        }
        if (ifMerge)
        {
            e3.push_back(e1[i]);
        }
    }
}

//-----------------------------------------------------------------------
//以下为计算每个产生式属性的函数

void StatementFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[2]->childs[0]->name != "empty")
    {
        if (pointer->printAddress == -1)
        {
            pointer->printAddress = address;
            address++;
        }
        if (pointer->childs[1]->place != "")
        {
        }
        else
        {
            pointer->complete = false;
        }
    }

    if (print)
    {
        if (pointer->childs[2]->childs[0]->name != "empty")
        {
            OutputResult temp;
            temp.addr = pointer->printAddress;
            temp.op = ":=";
            temp.num1 = pointer->childs[2]->place;
            temp.num2 = "__";
            temp.num3 = pointer->childs[1]->place;
            outputResult.push_back(temp);
        }
    }
}

void VariableClosureFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->name != "empty")
    {
        if (pointer->childs[1]->childs[0]->name != "empty")
        {
            if (pointer->printAddress == -1)
            {
                pointer->printAddress = address;
                address++;
            }
            if (pointer->childs[0]->place != "")
            {
            }
            else
            {
                pointer->complete = false;
            }
        }
    }

    if (print)
    {
        if (pointer->childs[0]->name != "empty")
        {
            if (pointer->childs[1]->childs[0]->name != "empty")
            {
                OutputResult temp;
                temp.addr = pointer->printAddress;
                temp.op = ":=";
                temp.num1 = pointer->childs[1]->place;
                temp.num2 = "__";
                temp.num3 = pointer->childs[0]->place;
                outputResult.push_back(temp);
            }
        }
    }
}

void InitValueFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->name == "empty")
    {
        return;
    }
    if (pointer->childs[1]->place != "")
    {
        pointer->place = pointer->childs[1]->place;
    }
    else
    {
        pointer->complete = false;
    }
}

void ExpressionFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->place != "")
    {
        if (pointer->childs[1]->childs[0]->name != "empty")
        {
            if (pointer->printAddress == -1)
            {
                pointer->printAddress = address;
                address++;
            }
            if (pointer->childs[1]->place != "")
            {
                if (pointer->place == "")
                {
                    pointer->place = newTemp();
                }
            }
            else
            {
                pointer->complete = false;
            }
        }
        else
        {
            pointer->place = pointer->childs[0]->place;
        }
    }
    else
    {
        pointer->complete = false;
    }
    if (print)
    {
        if (pointer->childs[1]->childs[0]->name != "empty")
        {
            OutputResult temp;
            temp.addr = pointer->printAddress;
            temp.op = pointer->childs[1]->childs[0]->name;
            temp.num1 = pointer->childs[0]->place;
            temp.num2 = pointer->childs[1]->place;
            temp.num3 = pointer->place;
            outputResult.push_back(temp);
        }
    }
}

void FactorFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->place != "")
    {
        if (pointer->childs[1]->childs[0]->name != "empty")
        {
            if (pointer->printAddress == -1)
            {
                pointer->printAddress = address;
                address++;
            }
            if (pointer->childs[1]->place != "")
            {
                if (pointer->place == "")
                {
                    pointer->place = newTemp();
                }
            }
            else
            {
                pointer->complete = false;
            }
        }
        else
        {
            pointer->place = pointer->childs[0]->place;
        }
    }
    else
    {
        pointer->complete = false;
    }
    if (print)
    {
        if (pointer->childs[1]->childs[0]->name != "empty")
        {
            OutputResult temp;
            temp.addr = pointer->printAddress;
            temp.op = pointer->childs[1]->childs[0]->name;
            temp.num1 = pointer->childs[0]->place;
            temp.num2 = pointer->childs[1]->place;
            temp.num3 = pointer->place;
            outputResult.push_back(temp);
        }
    }
}

void FactorExpressionFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->name == "(")
    {
        if (pointer->childs[1]->place != "")
        {
            pointer->place = pointer->childs[1]->place;
        }
        else
        {
            pointer->complete = false;
        }
    }
    else if (pointer->childs[0]->name == "Variable")
    {
        if (pointer->childs[0]->place != "")
        {
            pointer->place = pointer->childs[0]->place;
        }
        else
        {
            pointer->complete = false;
        }
    }
    else
    {
        if (pointer->childs[0]->place != "")
        {
            pointer->place = pointer->childs[0]->place;
        }
        else
        {
            pointer->complete = false;
        }
    }
}

void FactorExpressionRecursionFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->name == "empty")
    {
        return;
    }
    if (pointer->childs[1]->place != "")
    {
        if (pointer->childs[2]->childs[0]->name != "empty")
        {
            if (pointer->printAddress == -1)
            {
                pointer->printAddress = address;
                address++;
            }
            if (pointer->childs[2]->place != "")
            {
                if (pointer->place == "")
                {
                    pointer->place = newTemp();
                }
            }
            else
            {
                pointer->complete = false;
            }
        }
        else
        {
            pointer->place = pointer->childs[1]->place;
        }
    }
    else
    {
        pointer->complete = false;
    }
    if (print)
    {
        if (pointer->childs[2]->childs[0]->name != "empty")
        {
            OutputResult temp;
            temp.addr = pointer->printAddress;
            temp.op = pointer->childs[2]->childs[0]->name;
            temp.num1 = pointer->childs[1]->place;
            temp.num2 = pointer->childs[2]->place;
            temp.num3 = pointer->place;
            outputResult.push_back(temp);
        }
    }
}

void ItemFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->name != "empty")
    {
        if (pointer->childs[1]->place != "")
        {
            if (pointer->childs[2]->childs[0]->name != "empty")
            {
                if (pointer->printAddress == -1)
                {
                    pointer->printAddress = address;
                    address++;
                }
                if (pointer->childs[2]->place != "")
                {
                    if (pointer->place == "")
                    {
                        pointer->place = newTemp();
                    }
                }
                else
                {
                    pointer->complete = false;
                }
            }
            else
            {
                pointer->place = pointer->childs[1]->place;
            }
        }
        else
        {
            pointer->complete = false;
        }
    }
    if (print)
    {
        if (pointer->childs[0]->name != "empty")
        {
            if (pointer->childs[2]->childs[0]->name != "empty")
            {
                OutputResult temp;
                temp.addr = pointer->printAddress;
                temp.op = pointer->childs[2]->childs[0]->name;
                temp.num1 = pointer->childs[1]->place;
                temp.num2 = pointer->childs[2]->place;
                temp.num3 = pointer->place;
                outputResult.push_back(temp);
            }
        }
    }
}

void AssignmentStatementFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->printAddress == -1)
    {
        pointer->printAddress = address;
        address++;
    }
    if (pointer->childs[0]->place != "" && pointer->childs[2]->place != "")
    {
    }
    else
    {
        pointer->complete = false;
    }
    if (print)
    {
        OutputResult temp;
        temp.addr = pointer->printAddress;
        temp.op = ":=";
        temp.num1 = pointer->childs[2]->place;
        temp.num2 = "__";
        temp.num3 = pointer->childs[0]->place;
        outputResult.push_back(temp);
    }
}

void BoolStatementFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[1]->childs[0]->name != "empty")
    {
        if (pointer->childs[0]->complete && pointer->childs[1]->complete)
        {
            pointer->falseaddr = pointer->childs[1]->falseaddr;
            Merge(pointer->childs[0]->trueaddr, pointer->trueaddr);
            Merge(pointer->childs[1]->trueaddr, pointer->trueaddr);
        }
        else
        {
            pointer->complete = false;
        }
    }
    else
    {
        if (pointer->childs[0]->complete)
        {
            pointer->trueaddr = pointer->childs[0]->trueaddr;
            pointer->falseaddr = pointer->childs[0]->falseaddr;
        }
        else
        {
            pointer->complete = false;
        }
    }
    if (print)
    {
        if (pointer->childs[1]->childs[0]->name != "empty")
        {
            if (pointer->childs[0]->complete && pointer->childs[1]->complete)
            {
                BackPatch(pointer->childs[0]->falseaddr, pointer->childs[1]->childs[1]->quad);
            }
        }
    }
}

void MFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->quad == -1)
    {
        pointer->quad = address;
    }
}

void NFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->nextaddr.size() == 0)
    {
        pointer->nextaddr.push_back(address);
    }
    if (pointer->printAddress == -1)
    {
        pointer->printAddress = address;
        address++;
    }
    if (print)
    {
        OutputResult temp;
        temp.addr = pointer->printAddress;
        temp.op = "j";
        temp.num1 = "__";
        temp.num2 = "__";
        temp.num3 = "0";
        outputResult.push_back(temp);
    }
}

void BoolStatementClosureFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->name != "empty")
    {
        if (pointer->childs[3]->childs[0]->name != "empty")
        {
            if (pointer->childs[2]->complete && pointer->childs[3]->complete)
            {
                pointer->falseaddr = pointer->childs[3]->falseaddr;
                Merge(pointer->childs[2]->trueaddr, pointer->trueaddr);
                Merge(pointer->childs[3]->trueaddr, pointer->trueaddr);
            }
            else
            {
                pointer->complete = false;
            }
        }
        else
        {
            if (pointer->childs[2]->complete)
            {
                pointer->trueaddr = pointer->childs[2]->trueaddr;
                pointer->falseaddr = pointer->childs[2]->falseaddr;
            }
            else
            {
                pointer->complete = false;
            }
        }
    }
    if (print)
    {
        if (pointer->childs[0]->name != "empty")
        {
            if (pointer->childs[3]->childs[0]->name != "empty")
            {
                if (pointer->childs[2]->complete && pointer->childs[3]->complete)
                {
                    BackPatch(pointer->childs[2]->falseaddr, pointer->childs[3]->childs[1]->quad);
                }
            }
        }
    }
}

void BoolItemFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[1]->childs[0]->name != "empty")
    {
        if (pointer->childs[0]->complete && pointer->childs[1]->complete)
        {
            pointer->trueaddr = pointer->childs[1]->trueaddr;
            Merge(pointer->childs[0]->falseaddr, pointer->falseaddr);
            Merge(pointer->childs[1]->falseaddr, pointer->falseaddr);
        }
        else
        {
            pointer->complete = false;
        }
    }
    else
    {
        if (pointer->childs[0]->complete)
        {
            pointer->trueaddr = pointer->childs[0]->trueaddr;
            pointer->falseaddr = pointer->childs[0]->falseaddr;
        }
        else
        {
            pointer->complete = false;
        }
    }
    if (print)
    {
        if (pointer->childs[1]->childs[0]->name != "empty")
        {
            if (pointer->childs[0]->complete && pointer->childs[1]->complete)
            {
                BackPatch(pointer->childs[0]->falseaddr, pointer->childs[1]->childs[1]->quad);
            }
        }
    }
}

void BoolItemClosureFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->name != "empty")
    {
        if (pointer->childs[3]->childs[0]->name != "empty")
        {
            if (pointer->childs[2]->complete && pointer->childs[3]->complete)
            {
                pointer->trueaddr = pointer->childs[3]->trueaddr;
                Merge(pointer->childs[2]->falseaddr, pointer->falseaddr);
                Merge(pointer->childs[3]->falseaddr, pointer->falseaddr);
            }
            else
            {
                pointer->complete = false;
            }
        }
        else
        {
            if (pointer->childs[2]->complete)
            {
                pointer->trueaddr = pointer->childs[2]->trueaddr;
                pointer->falseaddr = pointer->childs[2]->falseaddr;
            }
            else
            {
                pointer->complete = false;
            }
        }
    }
    if (print)
    {
        if (pointer->childs[0]->name != "empty")
        {
            if (pointer->childs[3]->childs[0]->name != "empty")
            {
                if (pointer->childs[2]->complete && pointer->childs[3]->complete)
                {
                    BackPatch(pointer->childs[2]->falseaddr, pointer->childs[3]->childs[1]->quad);
                }
            }
        }
    }
}

void BoolFactorFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->name != "!")
    {
        if (pointer->trueaddr.size() == 0)
        {
            pointer->trueaddr.push_back(address);
            pointer->falseaddr.push_back(address + 1);
        }
        if (pointer->printAddress == -1)
        {
            pointer->printAddress = address;
            address++;
            address++;
        }
    }
    else
    {
        if (pointer->childs[1]->complete)
        {
            pointer->trueaddr = pointer->childs[1]->falseaddr;
            pointer->falseaddr = pointer->childs[1]->trueaddr;
        }
        else
        {
            pointer->complete = false;
        }
    }
    if (print)
    {
        if (pointer->childs[0]->name != "!")
        {
            OutputResult temp;
            temp.addr = pointer->printAddress;
            temp.op = "j";
            if (pointer->childs[1]->childs[0]->name == "<")
            {
                temp.op += "b";
            }
            else if (pointer->childs[1]->childs[0]->name == ">")
            {
                temp.op += "a";
            }
            else if (pointer->childs[1]->childs[0]->name == "==")
            {
                temp.op += "z";
            }
            else
            {
                temp.op += "nz";
            }
            temp.num1 = pointer->childs[0]->place;
            temp.num2 = pointer->childs[2]->place;
            temp.num3 = "0";
            outputResult.push_back(temp);
            OutputResult temp1;
            temp1.addr = pointer->printAddress + 1;
            temp1.op = "j";
            temp1.num1 = "__";
            temp1.num2 = "__";
            temp1.num3 = "0";
            outputResult.push_back(temp1);
        }
    }
}

void FunctionClosureFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (print)
    {
        if (pointer->childs[0]->name != "empty")
        {
            BackPatch(pointer->childs[0]->nextaddr, pointer->childs[1]->quad);
        }
    }
}

void WhileCycleFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->printAddress == -1)
    {
        pointer->printAddress = address;
        address++;
    }

    pointer->nextaddr = pointer->childs[3]->falseaddr;
    if (print)
    {
        BackPatch(pointer->childs[7]->nextaddr, pointer->childs[2]->quad);
        BackPatch(pointer->childs[3]->trueaddr, pointer->childs[6]->quad);
        OutputResult temp;
        temp.addr = pointer->printAddress;
        temp.op = "j";
        temp.num1 = "__";
        temp.num2 = "__";
        temp.num3 = to_string(pointer->childs[2]->quad);
        outputResult.push_back(temp);
    }
}

void IfStatementFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (print)
    {
        if (pointer->childs[8]->childs[0]->name != "empty")
        {
            BackPatch(pointer->childs[2]->trueaddr, pointer->childs[5]->quad);
            BackPatch(pointer->childs[2]->falseaddr, pointer->childs[8]->childs[3]->quad);
            Merge(pointer->childs[6]->nextaddr, pointer->nextaddr);
            Merge(pointer->childs[8]->childs[0]->nextaddr, pointer->nextaddr);
            Merge(pointer->childs[8]->childs[4]->nextaddr, pointer->nextaddr);
        }
        else
        {
            BackPatch(pointer->childs[2]->trueaddr, pointer->childs[5]->quad);
            Merge(pointer->childs[2]->falseaddr, pointer->nextaddr);
            Merge(pointer->childs[6]->nextaddr, pointer->nextaddr);
        }
    }
}

void SuffixStatementFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->printAddress == -1)
    {
        pointer->printAddress = address;
        address++;
    }
    if (print)
    {
        OutputResult temp;
        temp.addr = pointer->printAddress;
        temp.op = pointer->childs[1]->childs[0]->name;
        temp.num1 = "__";
        temp.num2 = "__";
        temp.num3 = pointer->childs[0]->place;
        outputResult.push_back(temp);
    }
}

void ForCycleFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->printAddress == -1)
    {
        pointer->printAddress = address;
        address++;
    }
    pointer->nextaddr = pointer->childs[4]->falseaddr;
    if (print)
    {
        BackPatch(pointer->childs[8]->nextaddr, pointer->childs[3]->quad);
        BackPatch(pointer->childs[4]->trueaddr, pointer->childs[11]->quad);
        OutputResult temp;
        temp.addr = pointer->printAddress;
        temp.op = "j";
        temp.num1 = "__";
        temp.num2 = "__";
        temp.num3 = to_string(pointer->childs[6]->quad);
        outputResult.push_back(temp);
    }
}

//初始化产生式
void initProduction()
{
    Production program = {"Program", {{{1, "int"}, {1, "main"}, {1, "("}, {1, ")"}, {1, "{"}, {0, "ProgramBody"}, {1, "}"}}}};
    productions.push_back(program);
    Production programBody = {"ProgramBody", {{{0, "StatementClosure"}, {0, "FunctionClosure"}}}};
    productions.push_back(programBody);
    Production statementClosure = {"StatementClosure", {{{0, "StatementSen"}, {0, "StatementClosure"}}, {{1, "empty"}}}, NULL, {{"int", "char", "double", "float", "long", "short"}, {"id", "while", "if"}}};
    productions.push_back(statementClosure);
    Production statementSen = {"StatementSen", {{{0, "Statement"}, {1, ";"}}}};
    productions.push_back(statementSen);
    Production statement = {"Statement", {{{0, "Type"}, {0, "Variable"}, {0, "InitValue"}, {0, "VariableClosure"}}}, StatementFunc};
    productions.push_back(statement);
    Production variableClosure = {"VariableClosure", {{{0, "Variable"}, {0, "InitValue"}, {0, "VariableClosure"}}, {{1, "empty"}}}, VariableClosureFunc, {{"id"}, {";"}}};
    productions.push_back(variableClosure);
    Production type = {"Type", {{{1, "int"}}, {{1, "char"}}, {{1, "double"}}, {{1, "float"}}, {{1, "long"}}, {{1, "short"}}}, NULL, {{"int"}, {"char"}, {"double"}, {"float"}, {"long"}, {"short"}}};
    productions.push_back(type);
    Production variable = {"Variable", {{{1, "id"}}}, NULL};
    productions.push_back(variable);
    Production initValue = {"InitValue", {{{1, "="}, {0, "Expression"}}, {{1, "empty"}}}, InitValueFunc, {{"="}, {"id", ";"}}};
    productions.push_back(initValue);
    Production expression = {"Expression", {{{0, "Factor"}, {0, "Item"}}}, ExpressionFunc};
    productions.push_back(expression);
    Production factor = {"Factor", {{{0, "FactorExpression"}, {0, "FactorExpressionRecursion"}}}, FactorFunc};
    productions.push_back(factor);
    Production factorExpression = {"FactorExpression", {{{1, "("}, {0, "Expression"}, {1, ")"}}, {{0, "Variable"}}, {{0, "Digit"}}}, FactorExpressionFunc, {{"("}, {"id"}, {"digit"}}};
    productions.push_back(factorExpression);
    Production digit = {"Digit", {{{1, "digit"}}}, NULL};
    productions.push_back(digit);
    Production factorExpressionRecursion = {"FactorExpressionRecursion", {{{1, "*"}, {0, "FactorExpression"}, {0, "FactorExpressionRecursion"}}, {{1, "/"}, {0, "FactorExpression"}, {0, "FactorExpressionRecursion"}}, {{1, "empty"}}}, FactorExpressionRecursionFunc, {{"*"}, {"/"}, {"+", "-", ";", "id", "<", ">", "==", "!", "<=", ">=", ")"}}};
    productions.push_back(factorExpressionRecursion);
    Production item = {"Item", {{{1, "+"}, {0, "Factor"}, {0, "Item"}}, {{1, "-"}, {0, "Factor"}, {0, "Item"}}, {{1, "empty"}}}, ItemFunc, {{"+"}, {"-"}, {";", "id", "<", ">", "==", "!", "<=", ">=", ")"}}};
    productions.push_back(item);
    Production functionClosure = {"FunctionClosure", {{{0, "AssignmentStatement"}, {0, "M"}, {0, "FunctionClosure"}}, {{0, "WhileCycle"}, {0, "M"}, {0, "FunctionClosure"}}, {{0, "IfStatement"}, {0, "M"}, {0, "FunctionClosure"}}, {{0, "ForCycle"}, {0, "M"}, {0, "FunctionClosure"}}, {{1, "empty"}}}, FunctionClosureFunc, {{"id"}, {"while"}, {"if"}, {"for"}, {"}"}}};
    productions.push_back(functionClosure);
    Production assignmentStatement = {"AssignmentStatement", {{{0, "Variable"}, {1, "="}, {0, "Expression"}, {1, ";"}}}, AssignmentStatementFunc};
    productions.push_back(assignmentStatement);
    Production boolStatement = {"BoolStatement", {{{0, "BoolItem"}, {0, "BoolStatementClosure"}}}, BoolStatementFunc};
    productions.push_back(boolStatement);
    Production m = {"M", {{{1, "empty"}}}, MFunc};
    productions.push_back(m);
    Production n = {"N", {{{1, "empty"}}}, NFunc};
    productions.push_back(n);
    Production boolStatementClosure = {"BoolStatementClosure", {{{1, "||"}, {0, "M"}, {0, "BoolItem"}, {0, "BoolStatementClosure"}}, {{1, "empty"}}}, BoolStatementClosureFunc, {{"|"}, {")", ";"}}};
    productions.push_back(boolStatementClosure);
    Production boolItem = {"BoolItem", {{{0, "BoolFactor"}, {0, "BoolItemClosure"}}}, BoolItemFunc};
    productions.push_back(boolItem);
    Production boolItemClosure = {"BoolItemClosure", {{{1, "&&"}, {0, "M"}, {0, "BoolFactor"}, {0, "BoolItemClosure"}}, {{1, "empty"}}}, BoolItemClosureFunc, {{"&"}, {"|", ")", ";"}}};
    productions.push_back(boolItemClosure);
    Production boolFactor = {"BoolFactor", {{{0, "Expression"}, {0, "BoolSymbol"}, {0, "Expression"}}, {{1, "!"}, {0, "BoolFactor"}}}, BoolFactorFunc, {{"(", "digit", "id"}, {"!"}}};
    productions.push_back(boolFactor);
    Production boolSymbol = {"BoolSymbol", {{{1, "<"}}, {{1, ">"}}, {{1, "=="}}, {{1, "!="}}}, NULL, {{"<"}, {">"}, {"=="}, {"!="}}};
    productions.push_back(boolSymbol);
    Production whileCycle = {"WhileCycle", {{{1, "while"}, {1, "("}, {0, "M"}, {0, "BoolStatement"}, {1, ")"}, {1, "{"}, {0, "M"}, {0, "ProgramBody"}, {1, "}"}}}, WhileCycleFunc};
    productions.push_back(whileCycle);
    Production ifStatement = {"IfStatement", {{{1, "if"}, {1, "("}, {0, "BoolStatement"}, {1, ")"}, {1, "{"}, {0, "M"}, {0, "ProgramBody"}, {1, "}"}, {0, "ElseStatement"}}}, IfStatementFunc};
    productions.push_back(ifStatement);
    Production elseStatement = {"ElseStatement", {{{0, "N"}, {1, "else"}, {1, "{"}, {0, "M"}, {0, "ProgramBody"}, {1, "}"}}, {{1, "empty"}}}, NULL, {{"else"}, {"}", "id", "while", "if"}}};
    productions.push_back(elseStatement);
    Production forCycle = {"ForCycle", {{{1, "for"}, {1, "("}, {0, "AssignmentStatement"}, {0, "M"}, {0, "BoolStatement"}, {1, ";"}, {0, "M"}, {0, "SuffixStatement"}, {0, "N"}, {1, ")"}, {1, "{"}, {0, "M"}, {0, "ProgramBody"}, {1, "}"}}}, ForCycleFunc};
    productions.push_back(forCycle);
    Production suffixStatement = {"SuffixStatement", {{{0, "Variable"}, {0, "Suffix"}}}, SuffixStatementFunc};
    productions.push_back(suffixStatement);
    Production suffix = {"Suffix", {{{1, "++"}}, {{1, "--"}}}, NULL, {{"++"}, {"--"}}};
    productions.push_back(suffix);
}