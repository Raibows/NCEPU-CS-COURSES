#include <string>
#include <iostream>
#include <vector>
#include <ctype.h>
#include <fstream>
#define grammar_length 37
using namespace std;

//�ж��ַ����Ƿ��Ǵ�д
bool isUpper(string str)
{
	bool flag = true;
	if (str.size() <= 0) flag = false;
	for (int i = 0; i < str.size(); i++)
	{
		if (!isupper(str[i]))
		{
			flag = false;
			break;
		}
	}
	return flag;
}

//�ָ��
std::vector<std::string> split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//��չ�ַ����Է������
	int size = str.size();

	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}


//�ķ�����
class Grammar
{
public:
	Grammar();
	~Grammar();
	Grammar(int i, char  IN[], char ou[]) {
		id = i;
		INP = IN;
		OUP = ou;
		string str = ou;
		vector<string> ve = split(str, " ");
		for (int i = 0; i < ve.size(); i++)
		{
			if (isUpper(ve[i]))
				notEnd.push_back(ve[i]);
			else
				isEnd.push_back(ve[i]);
		}
	}
	int getid() { return id; }
	char  * getINP() { return INP; }
	char *getOUP() { return OUP; }
	/*
	void print() {
		string str = "";
		for (int i = 0;; i++)
		{
			str += *(INP + i);
			if (*(INP + i) == '\0')
				break;
		}
		str += "-> ";
		for (int i = 0; *(OUP + i) != '\0'; i++)
		{
			str += *(OUP + i);
		}
		cout << str << "\t isEnd:"; isEndprint(); cout << endl;
	}*/
	vector<string> getisEnd() { return isEnd; }
private:
	int id; //�ķ����
	char * INP;  //����ʽ�󲿷�
	char * OUP;//����ʽ�Ҳ���
	vector<string> notEnd;
	vector<string> isEnd;
	/*
	void isEndprint()
	{
		for (int i = 0; i < isEnd.size(); i++)
			cout << isEnd[i] << " ";

	}
	*/
};
Grammar::Grammar()
{}
Grammar::~Grammar()
{
}


//token�ṹ��
typedef struct token
{
	int label;
	string name;
	int code;
	string type;
	int addr;    //���ű�λ��
	int linenum;     //�к�
	token(string n, int c, int a, string t, int l) { name = n; code = c; addr = a; type = t; linenum = l; }
	token() {}
} token;


vector<token> token2;


//��ȡtoken��
void readToken()
{
	string alltext[100];
	int num = 0;
	ifstream readFile("D:/token1.txt");
	string s;
	while (getline(readFile, s))
	{
		alltext[num] += s;
		num++;
	}
	readFile.close();
	for (int i = 0; i < num; i++) {
		vector<string> ve = split(alltext[i], "  ");
		int label = stoi(ve[0]);
		int code = stoi(ve[1]);
		string n = ve[2];
		int addr = stoi(ve[3]);
		string t = ve[4];
		int l = stoi(ve[5]);
		token to(n, code, addr, t, l);
		token2.push_back(to);
	}

}



//�ķ���ֵ����
Grammar  grammar[] = {
	Grammar(0, "W", "# P #"),
	Grammar(1, "P", "program id L"),     //���򣬱�ʶ����������
	Grammar(2, "L", "S ; L"),           //S���  , L ���� A��ֵ��䣬B �������ʽ��E�������ʽ
	Grammar(2, "L", "S"),
	Grammar(3, "S", "if B then S"),
	Grammar(3, "S", "if B then L else S"),
	Grammar(3, "S", "while B do S"),
	Grammar(3, "S", "begin L end"),
	Grammar(3, "S", "var D"),
	Grammar(3, "S", "?"),       //s->�� 
	Grammar(3, "S", "A"),
	Grammar(4, "D", "id : K ;"),        //D �������  �� id��ʶ�� ��K�������� 
	Grammar(5, "K", "integer"),
	Grammar(5, "K", "bool"),
	Grammar(5, "K", "real"),
	Grammar(6, "A", "id := E"),
	Grammar(7, "E", "E + T"),
	Grammar(7, "E", "E - T"),
	Grammar(7, "E", "T"),
	Grammar(7, "E", "- E"),
	Grammar(8, "B", "B or N"),
	Grammar(8, "B", "N"),
	Grammar(8, "B", "not B"),
	Grammar(9, "T", "T * F"),
	Grammar(9, "T", "T / F"),
	Grammar(9, "T", "F"),
	Grammar(10, "F", "( E )"),
	Grammar(10, "F", "id"),
	Grammar(11, "N", "N and M"),
	Grammar(11, "N", "M"),
	Grammar(12, "M", "( B )"),
	Grammar(12, "M", "id < id"),
	Grammar(12, "M", "id > id"),
	Grammar(12, "M", "id <> id"),
	Grammar(12, "M", "id <= id"),
	Grammar(12, "M", "id >= id"),
	Grammar(12, "M", "id = id")
};



//�ж��Ƿ��Ƿ��ս��
bool isInNotend(vector<string> s, string str)
{
	bool flag = false;
	for (int i = 0; i < s.size(); i++)
	{
		if (str == s[i])
		{
			flag = true;
			break;
		}
	}
	return flag;
}


//���ݷ��ս��ַ����ҵ���Ӧ�ķ�
int FindGraIndexByvec(vector<string>t)
{
	for (int i = 0; i < grammar_length; i++)
	{
		vector<string> s = grammar[i].getisEnd();
		if (s.size() != t.size()) continue;
		int size = s.size();
		bool flag = true;
		for (int j = 0; j < size; j++)  //t�е�Ԫ�غ�s��Ԫ��ÿ�����бȽ�
		{
			if (!isInNotend(s, t[j])) {
				flag = false; break;  //
			}
		}
		if (!flag) continue; //����ҵ���ƥ��ģ���һ���ķ�
		flag = true;
		for (int j = 0; j < size; j++)  //t�е�Ԫ�غ�s��Ԫ��ÿ�����бȽ�
		{
			if (!isInNotend(t, s[j])) {
				flag = false; break;  //
			}
		}
		if (!flag) continue;
		return i;
	}
	return -1;
}