#include<vector>


//寄存器结构体
struct registers
{
	string	name;     //寄存器名称
	vector<string> Rvalue;     //寄存器存放的值
	registers(string n) { name = n; }
	registers() {};
	void clearPush(string n)       //
	{
		Rvalue.clear();
		Rvalue.push_back(n);
	}
	bool isinReg(string n)     //判断是否在寄存器
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


//分配寄存器
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

//判断在不在RVALUE里
bool isExistRvalue(string arg)
{
	for (int i = 0; i < regs.size(); i++)
	{
		if (regs[i].isinReg(arg))
			return true;
	}
	return false;
}
