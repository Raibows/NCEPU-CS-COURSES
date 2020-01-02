#include <vector>
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include <cassert>
#include "Register.h"
using namespace std;
static int blockNum;

struct BasicBlock
{
	string name;
	vector<GenStruct> gens;
	vector <string> codes;
	BasicBlock()
	{
		stringstream stream;
		string str;
		stream << blockNum;
		stream >> str;
		name = "L" + str;
		blockNum++;
	}
	void add(GenStruct g)
	{
		gens.push_back(g);
	}
};


class aimCode
{
private:
	vector<BasicBlock> basicBlock; //������
	void initBasicBlock();  //��ʼ��������
	int findblocknameByGen(int index);  //������Ԫʽ��ַ�ҵ�������
	string findblocknameByGen(string index) {
		int i = stoi(index);
		i = findblocknameByGen(i);
		if (i >= basicBlock.size())
			return "end";
		return basicBlock[i].name;
	}
	vector<string> createcode(GenStruct);
	void initblockcodes();
	bool stringisinGen(string, int);
public:
	vector<BasicBlock> getBasicBlock() { return basicBlock; }
	aimCode() { initBasicBlock(); initblockcodes(); }
	void clearNotUse(GenStruct);
	void writecodes();
};


void aimCode::initBasicBlock()
{
	for (int i = 0; i < genStructs.size() - 1; i++)
	{
		if (i == 0) {   //�����һ��Ϊ���
			setOut_port(0);
		}
		if (genStructs[i].code <= 58 && genStructs[i].code >= 52) //��ת���
		{
			setOut_port(genStructs[i].result);//��ת�������Ϊ������
			setOut_port(i + 1); //��ת������һ��,Ϊ������
		}
	}
	for (int i = 0; i < genStructs.size();) //����������뵽������
	{
		BasicBlock bb;
		bb.add(genStructs[i]);
		i++;
		for (; i < genStructs.size(); i++)
		{
			if (genStructs[i].out_port == 1)
			{
				basicBlock.push_back(bb);
				break;
			}
			else
				bb.add(genStructs[i]);
		}
		if (i == genStructs.size())
			basicBlock.push_back(bb);
	}
}


void aimCode::initblockcodes()
{
	for (int blockindex = 0; blockindex < basicBlock.size(); blockindex++)
	{
		for (int i = 0; i < basicBlock[blockindex].gens.size(); i++)
		{
			basicBlock[blockindex].codes = merge(basicBlock[blockindex].codes, createcode(basicBlock[blockindex].gens[i]));
		}
	}
}



int aimCode::findblocknameByGen(int index)
{
	for (int i = 0; i < basicBlock.size(); i++) //iΪblock����
	{
		for (int j = 0; j < basicBlock[i].gens.size(); j++)
		{
			if (basicBlock[i].gens[j].label == index)
			{
				return i;
			}
		}
	}
	return -1;
}




//��ӡĿ�����
void aimCode::writecodes()
{
	ofstream OutFile("D:/asm.txt");
	cout << "���ɻ���������" << endl;
	for (int blockindex = 0; blockindex < basicBlock.size(); blockindex++)
	{
		OutFile << basicBlock[blockindex].name << ":\n";
		cout << basicBlock[blockindex].name << ":\n";
		for (int i = 0; i < basicBlock[blockindex].codes.size(); i++)
		{
			OutFile << "      " << basicBlock[blockindex].codes[i] << endl;

			cout << "      " << basicBlock[blockindex].codes[i] << endl;
		}
	}
	OutFile.close();
}


vector<string> aimCode::createcode(GenStruct gen)
{
	vector<string> codes;
	int code = gen.code;
	clearNotUse(gen);
	registers reg;
	int l = gen.label;
	int regindex, temp;
	switch (code)
	{

	case 41:            //op = "*"
		if (isExistRvalue(gen.addr1) && isExistRvalue(gen.addr2))
		{
			codes.push_back("MUL " + findreg(gen.addr1, regindex,l).name + "," + findreg(gen.addr2, temp,l).name);
			regs[regindex].clearPush(gen.result);
		}
		else if (isExistRvalue(gen.addr1) && !isExistRvalue(gen.addr2))
		{
			codes.push_back("MUL " + findreg(gen.addr1, regindex,l).name + "," + gen.addr2);
			regs[regindex].clearPush(gen.result);
		}
		else if (!isExistRvalue(gen.addr1) && isExistRvalue(gen.addr2))
		{
			codes.push_back("MUL " + findreg(gen.addr2, regindex,l).name + "," + gen.addr1);
			regs[regindex].clearPush(gen.result);
		}
		else {
			reg = findreg(gen.addr1, regindex,l);
			codes.push_back("MOV " + reg.name + "," + gen.addr1);
			codes.push_back("MUL " + reg.name + "," + gen.addr2);
			regs[regindex].clearPush(gen.result);
		}
		break;

	case 43:            //op = "+" 

		if (isExistRvalue(gen.addr1) && isExistRvalue(gen.addr2))
		{
			codes.push_back("ADD " + findreg(gen.addr1, regindex,l).name + "," + findreg(gen.addr2, temp,l).name);
			regs[regindex].clearPush(gen.result);
		}
		else if (isExistRvalue(gen.addr1) && !isExistRvalue(gen.addr2))
		{
			codes.push_back("ADD " + findreg(gen.addr1, regindex,l).name + "," + gen.addr2);
			regs[regindex].clearPush(gen.result);
		}
		else if (!isExistRvalue(gen.addr1) && isExistRvalue(gen.addr2))
		{
			codes.push_back("ADD " + findreg(gen.addr2, regindex,l).name + "," + gen.addr1);
			regs[regindex].clearPush(gen.result);
		}
		else {
			reg = findreg(gen.addr1, regindex,l);
			codes.push_back("MOV " + reg.name + "," + gen.addr1);
			codes.push_back("ADD " + reg.name + "," + gen.addr2);
			regs[regindex].clearPush(gen.result);
		}
		break;
	case 45:             //op = "-"
		if (isExistRvalue(gen.addr1) && isExistRvalue(gen.addr2))
		{
			codes.push_back("SUB " + findreg(gen.addr1, regindex,l).name + "," + findreg(gen.addr2, temp,l).name);
			regs[regindex].clearPush(gen.result);
		}
		else if (isExistRvalue(gen.addr1) && !isExistRvalue(gen.addr2))
		{
			codes.push_back("SUB " + findreg(gen.addr1, regindex,l).name + "," + gen.addr2);
			regs[regindex].clearPush(gen.result);
		}
		else if (!isExistRvalue(gen.addr1) && isExistRvalue(gen.addr2))
		{
			codes.push_back("SUB " + findreg(gen.addr2, regindex,l).name + "," + gen.addr1);
			regs[regindex].clearPush(gen.result);
		}
		else {
			reg = findreg(gen.addr1, regindex,l);
			codes.push_back("MOV " + reg.name + "," + gen.addr1);
			codes.push_back("SUB " + reg.name + "," + gen.addr2);
			regs[regindex].clearPush(gen.result);
		}

	case 48:     //op = "/";
		if (isExistRvalue(gen.addr1) && isExistRvalue(gen.addr2))
		{
			codes.push_back("DIV " + findreg(gen.addr1, regindex,l).name + "," + findreg(gen.addr2, temp,l).name);
			regs[regindex].clearPush(gen.result);
		}
		else if (isExistRvalue(gen.addr1) && !isExistRvalue(gen.addr2))
		{
			codes.push_back("DIV " + findreg(gen.addr1, regindex,l).name + "," + gen.addr2);
			regs[regindex].clearPush(gen.result);
		}
		else if (!isExistRvalue(gen.addr1) && isExistRvalue(gen.addr2))
		{
			codes.push_back("DIV " + findreg(gen.addr2, regindex,l).name + "," + gen.addr1);
			regs[regindex].clearPush(gen.result);
		}
		else {
			reg = findreg(gen.addr1, regindex,l);
			codes.push_back("MOV " + reg.name + "," + gen.addr1);
			codes.push_back("DIV " + reg.name + "," + gen.addr2);
			regs[regindex].clearPush(gen.result);
		}
		break;


	case 51:             //op = ":=";
		reg = findreg(gen.addr1, regindex,l);
		if (isExistRvalue(gen.addr1)) {
			codes.push_back("MOV " + gen.result + "," + reg.name);
			regs[regindex].Rvalue.push_back(gen.result);
		}
		else {
			codes.push_back("MOV " + gen.result + "," + gen.addr1);
		}
		break;

	case 52:            //op = "j"
		codes.push_back("JMP " + findblocknameByGen(gen.result));
		break;

	case 53:           //op = "j<"
		codes.push_back("CMP " + gen.addr1 + "," + gen.addr2);
		codes.push_back("JL " + findblocknameByGen(gen.result));
		break;

	case 54:          //op = "j<="
		codes.push_back("CMP " + gen.addr1 + "," + gen.addr2);
		codes.push_back("JLE " + findblocknameByGen(gen.result));
		break;

	case 55:          //op = "j<>"
		codes.push_back("CMP " + gen.addr1 + "," + gen.addr2);
		codes.push_back("JNE " + findblocknameByGen(gen.result));
		break;

	case 56:         //op = "j=";
		codes.push_back("CMP " + gen.addr1 + "," + gen.addr2);
		codes.push_back("JE " + findblocknameByGen(gen.result));
		break;

	case 57:         //op = "j>"
		codes.push_back("CMP " + gen.addr1 + "," + gen.addr2);
		codes.push_back("JG " + findblocknameByGen(gen.result));
		break;

	case 58:         //op = "j>="
		codes.push_back("CMP " + gen.addr1 + "," + gen.addr2);
		codes.push_back("JGE " + findblocknameByGen(gen.result));
		break;
	default:
		break;
	}
	return codes;
}


//�ж�string�Ƿ���index����Ԫʽ�д���
bool aimCode::stringisinGen(string str, int index)
{
	for (int k = genStructs.size() - 1; k >= index; k--)
	{
		if (genStructs[k].addr1 == str || genStructs[k].addr2 == str)
			return true;
	}
	return false;
}


//�������л����飬�ѷǴ��õļĴ�����ֵ��ɾ��,�ѻ��������Rvalue���
void aimCode::clearNotUse(GenStruct gen)
{
	int index = gen.label;
	for (int i = 0; i < regs.size(); i++)
	{
		for (int j = 0; j < regs[i].Rvalue.size(); j++)
		{
			if (!stringisinGen(regs[i].Rvalue[j], index))
			{
				//ɾ��
				regs[i].Rvalue.erase(regs[i].Rvalue.begin() + j);
			}
		}
	}
}