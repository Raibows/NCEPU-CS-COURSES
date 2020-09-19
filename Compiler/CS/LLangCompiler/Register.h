#include<vector>


//�Ĵ����ṹ��
struct registers
{
	string	name;     //�Ĵ�������
	vector<string> Rvalue;     //�Ĵ�����ŵ�ֵ
	registers(string n) { name = n; }
	registers() {};
	void clearPush(string n)       //
	{
		Rvalue.clear();
		Rvalue.push_back(n);
	}
	bool isinReg(string n)     //�ж��Ƿ��ڼĴ���
	{
		bool flag = false;
		for (int i = 0; i < Rvalue.size(); i++)
		{
			if (Rvalue[i] == n)
				flag = true;
		}
		return flag;
	}
};
vector<registers> regs = { registers("BX"),registers("DX")};


//����Ĵ���
registers findreg(string arg, int &index,int l)
{
	
	for (int i = 0; i < regs.size(); i++)
	{
		if (regs[i].isinReg(arg))
		{
			index = i;
			return regs[i];
		}
	}
	
	for (int i = 0; i < regs.size(); i++)
	{
		if (regs[i].Rvalue.size() == 0)
		{
			index = i;
			return regs[i];
		}
	}
	int location = l;
	for (int k= location;k<genStructs.size();k++)
	{
		if (regs[0].isinReg(genStructs[k].addr1) || regs[0].isinReg(genStructs[k].addr2)) {
			index = 1;
			return regs[1];
		}
		else
		{
			index = 0;
			return regs[0];
		}
	}

	return NULL;
	
}

//�ж��ڲ���RVALUE��
bool isExistRvalue(string arg)
{
	for (int i = 0; i < regs.size(); i++)
	{
		if (regs[i].isinReg(arg))
			return true;
	}
	return false;
}
