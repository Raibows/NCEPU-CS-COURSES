#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>

using namespace std;

//分析栈
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

//优先关系表
char yx[8][8] = { ' ','+','*','-','i','(',')','#',
				 '+','>','<','<','<','<','>','>',
				 '*','>','>','<','<','<','>','>',
				 '-','>','>','<','<','<','>','>',
				 'i','>','>','>',' ',' ','>','>',
				 '(','<','<','<','<','<','=',' ',
				 ')','>','>','>',' ',' ','>','>',
				 '#','<','<','<','<','<',' ','=' };

//判断是否为终结符
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

//查询优先关系
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

//主函数
int main()
{
	char shuru[100]; char sr[100];
	char* ch = new char[100];                       
	push('#');                    
	int ll=0,top,top_vt;  //输入串下标，分析栈栈顶，分析栈最顶的终结符                      
	cout << "语法分析器的优先分析表如下：" << endl;
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
	cout << "请输入一个字符串：" << endl;
	cin.getline(shuru, 100);

	for (int i = 0;i < 100;i++)sr[i] = shuru[i];

	cout << "分析栈" << '\t' << '\t' << "输入串"<<'\t' << '\t' << "动作" << endl;

	//初始化
	top = getsize() - 1;     top_vt = top;  int sr_len = 0;
	//当前字符
	char a;

	//算符优先分析算法                       
	do{                            
		a = shuru[ll];              
		//特殊情况判断
		if ((a == '*') && (shuru[ll + 1] == '*'))
		{
			a = '-';
			ll++;
		}
		//分析栈最顶的终结符
		if (IsVT(getchar(top)))
			top_vt = top;
		else
			top_vt = top - 1;

	    //优先级大的就归约
		while (IsVT(a) && (c_yx(getchar(top_vt), a) == 1))
		{
			sc_stack();   //输出当前分析栈                         
			int ff = top_vt, ss = ff - 1; //分析栈最顶的终结符,分析栈第二顶的终结符 
			if (!IsVT(getchar(ss)))
				ss--;

			//将 s[j+1]…s[k]归约为某个N;
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
			strcpy(ch, pop(length));//归约的终结符串
			push('N');//归约为N

			//输出字符串
			for (int i = sr_len;;i++) {
				if (sr[i] == '\0')break;
				cout << sr[i];
			}
			
			cout << '\t' << '\t';
			
			//输出动作
			cout << "归约:";
			for (int i = 0;i < length;i++)
			{
				if (ch[i] == '-')
					cout << "**";
				else
					cout << ch[i];
			}
			cout << "==>" << 'N' << endl;
			//更新
			top_vt = getsize() - 1;
			if (!IsVT(getchar(top_vt)))
				top_vt--;
		}
		
		//优先级小于等于的就移进
		if ((c_yx(getchar(top_vt), a) == 2))
		{
			sc_stack();
			for (int i = sr_len;;i++) {
				if (sr[i] == '\0')break;
				cout << sr[i];
			}
			cout << '\t' << '\t';
			cout << "错误!";
			cout << "第" << ll + 1 << "个字符是错的!" << endl;
			break;
		}
		else
		{
			sc_stack();
			//输出字符串
			for (int i = sr_len;;i++) {
				if (sr[i] == '\0')break;
				cout << sr[i];
			}
			 cout << '\t' << '\t';
			sr_len++;
			if (a == '-')
				cout << "将" << "**" << " 移进." << endl;
			else
				cout << "将 " << a << " 移进." << endl;
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