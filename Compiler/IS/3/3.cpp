#include<iostream>
#include<string>
using namespace std;

//���ȹ�ϵ��
char yx[8][8] = { ' ','+','*','-','i','(',')','#',
				'+','>','<','<','<','<','>','>',
				'*','>','>','<','<','<','>','>',
				'-','>','>','<','<','<','>','>',
				'i','>','>','>',' ',' ','>','>',
				'(','<','<','<','<','<','=',' ',
				')','>','>','>',' ',' ','>','>',
				'#','<','<','<','<','<',' ','=' };

int sr_i[100];
int sr_len = 0;
char c_arr[100];
int Sp = 0;
int Temp[100];
int Tp, four_count = 0;


//���������
void sc_shu(int i)
{
	if (i < 100)//
	{
		if (i == 3)
			cout << "**";
		else
			cout << yx[0][i];
	}
	else if (i < 200)//
	{
		cout << c_arr[i - 100];
	}
	else if (i < 300)
	{
		sc_shu(Temp[i - 200]);
	}
	else
		cout << "T" << i - 300;
}

//��Ԫʽ
typedef class four_shi
{
	char op;
	int s1, s2, s3;
public:
	four_shi(int op, int  s1, int  s2)
	{
		this->op = yx[0][op];
		this->s1 = s1;
		this->s2 = s2;
		this->s3 = four_count + 300;
	}
	void four_sc()
	{
		cout << "(";
		if (op == '-')
			cout << "**";
		else
			cout << op;
		cout << ",";
		sc_shu(s1);
		cout << ",";
		sc_shu(s2);
		cout << ",";
		sc_shu(s3);
		cout << ")" ;
	}
	void cs_four()
	{
		cout << "����:" << four_count;
		four_sc();
	}
}*Four;
Four four[100];

//����ջ
struct stack
{
	int top=0;
	int a[100];	
};
stack s;
int size()
{
	return s.top;
}
void push(int  c)
{
	s.a[s.top++] = c;
}
int pop(int temp[], int length)
{
	for (int i = 0;i < length;i++)
	{
		temp[i] = s.a[s.top - length + i];
	}
	s.top = s.top - length;
	return length;
}
int gettop()
{
	return s.a[s.top - 1];
}
int getchar(int pos)
{
	return s.a[pos];
}

void shuchu(int i)
{
	if (i < 100)
	{
		if (i == 3)
			cout << "**";
		else
			cout << yx[0][i];
		return;
	}
	else if (i < 200)
	{
		cout << c_arr[i - 100];
		return;
	}
	else if (i < 300)
	{
		cout << "E" << i - 200;
	}
	else
		cout << "T" << i - 300;
}

//���ջ
void sc_stack()
{
	for (int i = 0;i < s.top;i++)
	{
		shuchu(s.a[i]);

	}
	if (s.top > 5) cout << '\t';
	else cout << '\t' << '\t';

}

bool ischar(char c)
{
if (((c >= 'a') && (c <= 'z')) || (c >= '0') && (c <= '9') || ((c >= 'A') && (c <= 'Z')))
	return true;
else
	return false;
}

//��ѯ���ȹ�ϵ
int c_yx(int i, int j)
{
	if (i / 100 == 1)
		i = 4;
	if (j / 100 == 1)
		j = 4;
	switch (yx[i][j])
	{
	case '>':return 1;break;
	case '<':return -1;break;
	case '=':return 0;break;
	default:return 2;break;
	}
}


int siyuanshi(int t[3])
{
	four_count++;
	four[four_count] = new four_shi(t[1], t[0], t[2]);
	four[four_count]->cs_four();
	cout << endl;
	return four_count + 300;
}

//�����ӳ���
int fanyi(int* ch, int ll)
{
	pop(ch, ll);
	if (ll == 1)//E->i
	{
		Temp[++Tp] = ch[0];
		cout << "�ϲ�:";
		shuchu(ch[0]);
		cout << "==>";
		shuchu(Tp + 200);
		cout << endl;
		return Tp + 200;
	}
	else if (ch[0] == 5 && ch[2] == 6)//E->(E1)
	{
		Temp[++Tp] = ch[1];
		cout << "�ϲ���(";
		shuchu(ch[1]);
		cout << ")==>";
		shuchu(Tp + 200);
		cout << endl;
		return Tp + 200;
	}
	else if (ch[0] > 100 && ch[2] > 100 && ch[1] < 100)//E��E1+E2 E��E1*E2 E��E1**E2
	{
		cout << "�ϲ���";
		shuchu(ch[0]);
		shuchu(ch[1]);
		shuchu(ch[2]);
		cout << "==>";
		shuchu(four_count + 301);
		cout << '\t';
		return siyuanshi(ch);
	}
	else
	{
		cout << "�ϲ�ʧ�ܣ�" << endl;
		//exit(0);
	}
}

//�ַ�����������
int zifu(char ch)
{
	for (int i = 1;i < c_arr[0];i++)
		if (c_arr[i] == ch)
			return i + 100;
	c_arr[++Sp] = ch;
	return Sp + 100;
}

//�ַ���������
int c2i(char ch)
{
	int j;
	for (j = 0;j < 8;j++)
		if (ch == yx[0][j])
			return j;
	if (ischar(ch))
	{
		return zifu(ch);
	}
	else
		return 0;
}

//�����ַ�����������
void in2i(int sr_i[], char str[], int& d_len, int len)
{
	for (int i = 0;i < len;i++)
	{
		sr_i[d_len] = c2i(str[i]);
		if (sr_i[d_len] == 0)//�����ַ�
		{
			cout << "�������" << "λ��:" << i + 1 << endl;
			cout << str[i] << "���ܱ�ʶ��" << endl;
			system("pause");
			exit(0);
		}
		if (sr_i[d_len] == 2 && sr_i[d_len - 1] == 2)//**
			sr_i[d_len - 1] = 3;
		else 
			d_len++;
	}
}

//�ж��Ƿ�Ϊ�ս��
bool IsVT(char c)
{
	bool flag = false;
	for (int i = 0;i < 8;i++)
	{
		if (c == yx[0][i])
		{
			flag = true;
		}
	}
	return flag;
}

int main()
{
	char shuru[100];
	int* ch = new int[100];
	
	cout << "��������������ȷ��������£�" << endl;
	for (int i = 0;i < 8;i++)
	{
		for (int j = 0;j < 8;j++)
		{
			if (yx[i][j] == '-')
				cout << "**" << '\t';
			else
				cout << yx[i][j] << '\t';
		}
		cout << endl;
	}
	cout << "---------------------------------------------------------" << endl;
	
	cout << "������һ�γ���(�� # ������):" << endl;
	cin.getline(shuru, 100);int len = strlen(shuru);
	
	in2i(sr_i, shuru, sr_len, len);

	cout << "����ջ:" << '\t' << '\t' << "����:" << '\t' << '\t' << '\t' << "��Ԫʽ:" << endl;
	push(7);
	
	int ll = 0;
	int top = size() - 1; int top_vt = top;
	int a = sr_i[0];
	
	do{
		a = sr_i[ll];

		//����ջ����ս��
		if (getchar(top) < 200)
			top_vt = top;
		else
			top_vt = top - 1;

		while (a < 200 && (c_yx(getchar(top_vt), a) == 1))
		{
			sc_stack();//�����ǰ����ջ 
			int ff = top_vt, ss = ff - 1;
			if (getchar(ss) > 200)
				ss--;

			//�� s[j+1]��s[k]��ԼΪĳ��N;
			while (c_yx(getchar(ss), getchar(ff)) != -1)
			{
				ff = ss;
				ss--;
				if (getchar(ss) > 200)
					ss--;
			}
			
			int start = size();
			ss++;
			int length = start - ss;
			
			push(fanyi(ch, length));//��Լ���ս����
			top_vt = size() - 1;
			if (getchar(top_vt) > 200)
				top_vt--;
		}
		
		//���ȼ�С�ڵ��ڵľ��ƽ�
		if ((a < 200) && (c_yx(getchar(top_vt), a) == 2))
		{
			cout << "����!" << endl;
			cout << "��" << ll + 1 << " ��ĸ����!" << endl;
			shuchu(a);

			exit(0);
		}
		else
		{
			sc_stack();
			cout << "�ƽ�:";
			shuchu(a);
			cout << endl;
			push(a);
			ll++;
			top = size() - 1;
		}
	} while (a != 7);

	sc_stack();
	int t[100];
	pop(t, 3);
	if (size() == 0)
		cout << "Yes!" << endl;
	else
		cout << "No!" << endl;
	
	
	cout << "�����Ԫʽ����:" << endl;
	for (int l = 1;l <= four_count;l++)
	{
		cout << l << ":";
		four[l]->four_sc();
		cout << endl;
	}

	return 0;
}