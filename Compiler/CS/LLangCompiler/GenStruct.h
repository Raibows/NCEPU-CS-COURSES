#include <string>
#include <sstream>


//int תstringר�ú���
void int2str(const int &int_temp, string &string_temp)
{
	stringstream stream;
	stream << int_temp;
	stream >> string_temp;    
}

//������Ԫʽ
struct GenStruct
{
	int label;
	string op;
	int code;     //��һԪ��
	string addr1="_"; //�ڶ�Ԫ�� 
	string addr2="_"; //����Ԫ��
	string result="0";//����Ԫ��
	int out_port = 0;  //��¼����Ԫʽ�Ƿ�Ϊһ�����������ڣ�����Ϊ1������Ϊ0��
	void ConvertOpToCode(string);
	GenStruct(int l){ label = l; }
	GenStruct(int l,string op,string a1,string a2,string res){
		label = l, this->op=op, ConvertOpToCode(op), addr1 = a1, addr2 = a2, result = res;
	}
};
vector<GenStruct> genStructs;  //��Ԫʽ����




//�������Ϻϲ�����
vector<string> merge(vector<string> vec1, vector<string>vec2)
{
	vector<string>vec3;
	vec3.insert(vec3.end(), vec1.begin(), vec1.end());
	vec3.insert(vec3.end(), vec2.begin(), vec2.end());
	return vec3;
}

//�����
void backpatch(vector<string> arg1, string arg2)
{
	for (int i = 0; i < arg1.size(); i++)
	{
		int index =stoi(arg1[i]);      //string תint
		genStructs[index].result = arg2;
	}
}


//������Ԫʽ
void CreateGen(string op ,string al, string a2, string res)  
{
	GenStruct t(genStructs.size(),op,al,a2,res);
	genStructs.push_back(t);
}


void printGens()
{
	ofstream OutFile("D:/equ.txt");
	for (int i = 0; i < genStructs.size(); i++)
	{
		OutFile << genStructs[i].label << ":(" << genStructs[i].op << "," << genStructs[i].addr1 << "," << genStructs[i].addr2 << "," << genStructs[i].result << ")\n";
	}
	OutFile.close();
}



int NewTempStruct_length = 0;
//����һ����ʱ����
string NewTempStruct()
{
	string s;
	int2str(NewTempStruct_length,s);
	NewTempStruct_length++;
	string  str = "T" + s;
	return  str;
}



void GenStruct::ConvertOpToCode(string op)
{
	if (op == ":=") code = 51;
	else if (op == "+") code = 43;
	else if (op == "-") code = 45;
	else if (op == "*") code = 41;
	else if (op == "/") code = 48;
	else if (op == "j<") code = 53;
	else if (op == "j<=") code = 54;
	else if (op == "j>") code = 57;
	else if (op == "j>=") code = 58;
	else if (op == "j=") code = 56;
	else if (op == "j") code = 52;
	else if (op == "j<>") code = 55;
	else
		code = 0;
}



void setOut_port(int index) //������Ԫʽ���
{
	if (index >= genStructs.size()) return;
	genStructs[index].out_port = 1;
}
void setOut_port(string idx) //������Ԫʽ���
{
	int index =stoi(idx);
	setOut_port(index);
}





//����Ԫʽ��ת�Ƶ���Ԫʽ�����е�ָ��λ��
void InsertGentoIndex(string sel, string desti)
{
	//����label++�����ĵ���Ԫ����������л�Ҫ++
	int self = stoi(sel);
	self--;
	int destin = stoi(desti);
	GenStruct gtemp = genStructs[self];
	try
	{
		int result = stoi(gtemp.result);
		if (result >= destin &&result <= self)
		{
			string str;
			int2str(++result, str);
			gtemp.result = str;
		}
	}
	catch (exception e)
	{
	}
	genStructs.erase(genStructs.begin() + self);
	gtemp.label = destin;
	for (int i = self - 1; i >= destin; i--)
	{
		
		genStructs[i].label++;
		try
		{
			int result = stoi(genStructs[i].result);
			if (result >= destin &&result <= self)
			{
				string str;
				int2str(++result, str);
				genStructs[i].result = str;
			}
		}
		catch (exception e)
		{
		}
	}
	genStructs.insert(genStructs.begin()+destin, gtemp);

}


