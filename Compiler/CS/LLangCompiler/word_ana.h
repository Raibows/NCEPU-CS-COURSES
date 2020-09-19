#include<iostream>
#include<string>
#include<fstream>
#include <cassert>
#include "Data.h"
using namespace std;

int temp = 0;
int total = 0;    //������Ϣ����
int line = 0;
int k = 0;   //�ʸ���
int l; //�ڷ��ű��е�λ��

//�ж��ڷ��ű��Ƿ����
bool isexist(string word, int Length) {
	for (int i = 0; i < Length; i++) {
		if (symble[i].name == word) {
			temp = i;
			return true;
		}
	}
	return false;
}

//�ؼ���
int isKeyword(string s)
{
	int i = 0;
	if (s != "") {
		if (((s[0] >= 'A') && (s[0] <= 'Z')) || ((s[0] >= 'a') && (s[0] <= 'z')))
		{
			while (i < 17)
			{
				if (keyword[i].name == s)
				{
					return  keyword[i].code;
				}
				i++;
			}

			return 18;	//��ʶ��
		}

	}
	return -1;
}

//���
int isOperator(string s)
{
	int i = 0;
	if (s != "")
	{
		while (i < 12)
		{
			if (s == operatorword[i].name)
			{
				return operatorword[i].code;
				break;
			}
			i++;
		}
	}
	return -1;
}

//���
int isDelimeter(string s)
{
	int i = 0;
	if (s != "")
	{
		while (i < 6)
		{
			if (s == delimeter[i].name)
			{
				return delimeter[i].code;
				break;
			}
			i++;
		}
	}
	return -1;
}

//����
int isConstants(string &s, int n)
{
	int i = 0;
	int pointNum = 0;
	string str;
	while (i < s.length())
	{
		if (s[i] == '.')
		{
			pointNum++;
		}
		if ((pointNum == 0) && (((s[i] >= 'A') && (s[i] <= 'Z')) || ((s[i] >= 'a') && (s[i] <= 'z'))))
		{
			wronginfo[total].number = total + 1;
			wronginfo[total].name = s;
			wronginfo[total].location = n + 1;
			wronginfo[total].type = "���󵥴ʣ����ֿ�ͷ�����֡���ĸ����";
			total++;
			for (int k = 0; k < i; k++)
			{
				str += s[k];
			}
			s = str;
			return 19;
			break;
		}
		if ((pointNum == 1) && (((s[i] >= 'A') && (s[i] <= 'Z')) || ((s[i] >= 'a') && (s[i] <= 'z'))))
		{

			wronginfo[total].number = total + 1;
			wronginfo[total].name = s;
			wronginfo[total].location = n + 1;
			wronginfo[total].type = "���󵥴ʣ�ʵ����С�����ֳ�����ĸ��";
			total++;
			for (int k = 0; k < i; k++)
			{
				str += s[k];
			}
			s = str;
			return 20;
			break;
		}
		if (pointNum == 2)
		{
			wronginfo[total].number = total + 1;
			wronginfo[total].name = s;
			wronginfo[total].location = n + 1;
			wronginfo[total].type = "���󵥴ʣ�����С���㣩";
			total++;
			for (int k = 0; k < i; k++)
			{
				str += s[k];
			}
			s = str;
			return 20;
			break;
		}
		i++;
	}

	for (int k = 0; k < i; k++) {
		str += s[k];
	}
	if (pointNum == 0) {
		s = str;
		return 19;
	}
	if (pointNum == 1) {
		s = str;
		return 20;
	}

	return -1;

}



//�õ����ű��token
void getToken() {
	for (; alltext[line] != ""; line++)
	{
		string text = alltext[line];
		int length = text.length();
		for (int i = 0; i < length; i++)
		{
			if (text[i] != ' ') {
				string word = "";
				if (((text[i] >= 'A') && (text[i] <= 'Z')) || ((text[i] >= 'a') && (text[i] <= 'z')))
				{
					while (((text[i] >= 'A') && (text[i] <= 'Z')) || ((text[i] >= 'a') && (text[i] <= 'z')) || ((text[i] >= 48) && (text[i] <= 57)))
					{
						word += text[i];
						i++;
					}
					i--;
					if (isKeyword(word) != -1)
					{
						if (isKeyword(word) == 18)
						{
							tokens[k].name = word;
							tokens[k].code = isKeyword(word);
							tokens[k].type = "��ʶ��";
							tokens[k].linenum = line;
							if (!isexist(word, l)) {
								symble[l].name = word;
								symble[l].type = "��ʶ��";
								symble[l].number = l;
								tokens[k].addr = l;
								l++;
							}
							else {
								tokens[k].addr = temp;
							}
							k++;

						}
						else {
							tokens[k].name = word;
							tokens[k].code = isKeyword(word);
							tokens[k].type = "�ؼ���";
							tokens[k].linenum = line;
							k++;
						}
					}
				}

				else if ((text[i] >= 48) && (text[i] <= 57))
				{
					while (((text[i] >= 48) && (text[i] <= 57)) || (text[i] == '.') || ((text[i] >= 'A') && (text[i] <= 'Z')) || ((text[i] >= 'a') && (text[i] <= 'z')))
					{
						word += text[i];
						i++;
					}
					i--;
					int a = isConstants(word, line);
					if (a == 19)
					{
						tokens[k].name = word;
						tokens[k].code = 19;
						tokens[k].type = "����";
						tokens[k].linenum = line;
						if (!isexist(word, l)) {
							symble[l].name = word;
							symble[l].type = "����";
							symble[l].number = l;
							tokens[k].addr = l;
							l++;
						}
						else {

							tokens[k].addr = temp;
						}
						k++;
					}
					else if (a == 20)
					{
						tokens[k].name = word;
						tokens[k].code = 20;
						tokens[k].type = "ʵ��";
						tokens[k].linenum = line;
						if (!isexist(word, l)) {
							symble[l].name = word;
							symble[l].type = "ʵ��";
							symble[l].number = l;
							tokens[k].addr = l;
							l++;
						}
						else {

							tokens[k].addr = temp;
						}
						k++;
					}
				}
				else
				{
					word += text[i];
					string ss = word;
					ss += text[i + 1];
					if (isOperator(ss) != -1)
					{
						word += text[i + 1];
						i = i + 1;
						tokens[k].name = word;
						tokens[k].code = isOperator(word);
						tokens[k].type = "���";
						tokens[k].linenum = line;
						k++;
					}
					else if (isDelimeter(word) != -1)
					{
						tokens[k].name = word;
						tokens[k].code = isDelimeter(word);
						tokens[k].type = "���";
						tokens[k].linenum = line;
						k++;
					}
					else if (isOperator(word) != -1)
					{
						tokens[k].name = word;
						tokens[k].code = isOperator(word);
						tokens[k].type = "���";
						tokens[k].linenum = line;
						k++;

					}
					else {
						tokens[k].name = word;
						tokens[k].code = 100;
						tokens[k].type = "�Ƿ��ַ�";
						tokens[k].linenum = line;
						k++;
					}
				}
			}
		}
	}
}


void readtext(string url)
{
	ifstream infile;
	infile.open(url.data());
	if (!infile)
	{
		cout << "�����ڴ��ļ�������������!" << endl;
		string url;
		cin >> url;
		readtext(url);
	}
	else {
		int i = 0;
		string s;
		while (getline(infile, s))
		{
			alltext[i] += s;
			i++;
		}
		infile.close();
		cout << "����������£�" << endl;
		for (int i = 0; alltext[i] != ""; i++)
		{
			cout << alltext[i] << endl;
		}
		cout << "�ʷ���������" << endl;
		getToken();
	}
}


void writeToken()
{
	int j = 0;
	ofstream OutFile("D:/token.txt");
	while (tokens[j].name != "")
	{
		OutFile << "(" << j + 1 << "," << tokens[j].code << "," << tokens[j].name << "," << tokens[j].addr << ")";
		OutFile << "\r\n";
		j++;
	}
	OutFile.close();

	j = 0;
	cout << "token�ļ����ɳɹ�" << endl;
	ofstream OutFile1("D:/symble.txt");
	while (symble[j].name != "")
	{
		OutFile1 << "(" << symble[j].number << "," << symble[j].name << "," << symble[j].type << ")";
		OutFile1 << "\r\n";
		j++;
	}
	OutFile1.close();
	cout << "symble�ļ����ɳɹ�" << endl;

	ofstream OutFile2("D:/wrong.txt");
	for (int i = 0; i < total; i++)
	{
		OutFile2 << wronginfo[i].number << "  " << wronginfo[i].location << "  " << wronginfo[i].name << "  " << wronginfo[i].type;
		OutFile2 << "\r\n";
	}
	OutFile2.close();

	ofstream OutFile3("D:/wrong.txt");
	for (int i = 0; i < total; i++)
	{
		cout << "������Ϣ:" << endl;
		cout << wronginfo[i].number << "  " << wronginfo[i].location << "  " << wronginfo[i].name << "  " << wronginfo[i].type << endl;
		OutFile3 << wronginfo[i].number << "  " << wronginfo[i].location << "  " << wronginfo[i].name << "  " << wronginfo[i].type;
		OutFile3 << "\r\n";
	}
	OutFile2.close();
}


void writeToken1()
{
	int j = 0;
	ofstream OutFile("D:/token1.txt");
	while (tokens[j].name != "")
	{
		OutFile << j + 1 << "  " << tokens[j].code << "  " << tokens[j].name << "  " << tokens[j].addr<<"  "<<tokens[j].type<<"  "<<tokens[j].linenum;
		OutFile << "\n";
		j++;
	}
	OutFile.close();
	j = 0;
	cout << "token�ļ����ɳɹ�" << endl;
}
/*
int main() {
	string url;
	cout << "������Դ�����ļ�·��: " << endl;    //D:/1.txt
	cin >> url;
	readtext(url);
	writeToken();
	system("pause");
	return 0;
}
*/
