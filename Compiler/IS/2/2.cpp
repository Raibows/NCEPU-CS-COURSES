#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>

using namespace std;

//����ջ
struct stack
{
	int top=0;
	char a[100];
};
stack s;
void  push(char c)
{
	s.a[s.top++] = c;
}
char* pop(int length)
{
	char* temp = new char[100];
	for (int i = 0;i < length;i++)
	{
		temp[i] = s.a[s.top - length + i];
	}
	s.top = s.top - length;
	temp[length] = '\0';
	return temp;
}
char  gettop()
{
	return s.a[s.top - 1];
}
int   getsize()
{
	return s.top;
}
char  getchar(int pos)
{
	return s.a[pos];
}
void  sc_stack()
{
	for (int i = 0;i < s.top;i++)
	{
		if (getchar(i) == '-')
		{
			cout << "**";
			cout << '\b';
		}
		else
			cout << getchar(i);
	}
	if (s.top >= 8)cout << '\t';
	else cout << '\t' << '\t';
}

//���ȹ�ϵ��
char yx[8][8] = { ' ','+','*','-','i','(',')','#',
				 '+','>','<','<','<','<','>','>',
				 '*','>','>','<','<','<','>','>',
				 '-','>','>','<','<','<','>','>',
				 'i','>','>','>',' ',' ','>','>',
				 '(','<','<','<','<','<','=',' ',
				 ')','>','>','>',' ',' ','>','>',
				 '#','<','<','<','<','<',' ','=' };

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

//��ѯ���ȹ�ϵ
int c_yx(char c1, char c2)
{                                 
	int i, j;
	switch (c1)
	{
	case '+':i = 1;break;
	case '*':i = 2;break;
	case '-':i = 3;break;
	case 'i':i = 4;break;
	case '(':i = 5;break;
	case ')':i = 6;break;
	case '#':i = 7;break;
	}
	switch (c2)
	{
	case '+':j = 1;break;
	case '*':j = 2;break;
	case '-':j = 3;break;
	case 'i':j = 4;break;
	case '(':j = 5;break;
	case ')':j = 6;break;
	case '#':j = 7;break;
	}
	switch (yx[i][j])
	{
	case '>':return 1;break;
	case '<':return -1;break;
	case '=':return 0;break;
	default:return 2;break;
	}
}

//������
int main()
{
	char shuru[100]; char sr[100];
	char* ch = new char[100];                       
	push('#');                    
	int ll=0,top,top_vt;  //���봮�±꣬����ջջ��������ջ����ս��                      
	cout << "�﷨�����������ȷ��������£�" << endl;
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
	cout << "������һ���ַ�����" << endl;
	cin.getline(shuru, 100);

	for (int i = 0;i < 100;i++)sr[i] = shuru[i];

	cout << "����ջ" << '\t' << '\t' << "���봮"<<'\t' << '\t' << "����" << endl;

	//��ʼ��
	top = getsize() - 1;     top_vt = top;  int sr_len = 0;
	//��ǰ�ַ�
	char a;

	//������ȷ����㷨                       
	do{                            
		a = shuru[ll];              
		//��������ж�
		if ((a == '*') && (shuru[ll + 1] == '*'))
		{
			a = '-';
			ll++;
		}
		//����ջ����ս��
		if (IsVT(getchar(top)))
			top_vt = top;
		else
			top_vt = top - 1;

	    //���ȼ���ľ͹�Լ
		while (IsVT(a) && (c_yx(getchar(top_vt), a) == 1))
		{
			sc_stack();   //�����ǰ����ջ                         
			int ff = top_vt, ss = ff - 1; //����ջ����ս��,����ջ�ڶ������ս�� 
			if (!IsVT(getchar(ss)))
				ss--;

			//�� s[j+1]��s[k]��ԼΪĳ��N;
			while (c_yx(getchar(ss), getchar(ff)) != -1)
			{
				ff = ss;
				ss--;
				if (!IsVT(getchar(ss)))
					ss--;
			}

			int start = getsize();
			ss++;
			int length = start - ss;
			strcpy(ch, pop(length));//��Լ���ս����
			push('N');//��ԼΪN

			//����ַ���
			for (int i = sr_len;;i++) {
				if (sr[i] == '\0')break;
				cout << sr[i];
			}
			
			cout << '\t' << '\t';
			
			//�������
			cout << "��Լ:";
			for (int i = 0;i < length;i++)
			{
				if (ch[i] == '-')
					cout << "**";
				else
					cout << ch[i];
			}
			cout << "==>" << 'N' << endl;
			//����
			top_vt = getsize() - 1;
			if (!IsVT(getchar(top_vt)))
				top_vt--;
		}
		
		//���ȼ�С�ڵ��ڵľ��ƽ�
		if ((c_yx(getchar(top_vt), a) == 2))
		{
			sc_stack();
			for (int i = sr_len;;i++) {
				if (sr[i] == '\0')break;
				cout << sr[i];
			}
			cout << '\t' << '\t';
			cout << "����!";
			cout << "��" << ll + 1 << "���ַ��Ǵ��!" << endl;
			break;
		}
		else
		{
			sc_stack();
			//����ַ���
			for (int i = sr_len;;i++) {
				if (sr[i] == '\0')break;
				cout << sr[i];
			}
			 cout << '\t' << '\t';
			sr_len++;
			if (a == '-')
				cout << "��" << "**" << " �ƽ�." << endl;
			else
				cout << "�� " << a << " �ƽ�." << endl;
			push(a);
			ll++;
			top = getsize() - 1;
		}
	
	
	} while (a != '#');
	
	
	sc_stack();
	pop(3);
	if (getsize() == 0)
		cout << '\t' << '\t' << "Yes!" << endl;
	else
		cout << '\t' << '\t' << "No!" << endl;
	return 0;
}