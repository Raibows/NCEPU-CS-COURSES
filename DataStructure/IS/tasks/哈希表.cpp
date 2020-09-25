#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;
#define Max 8

typedef struct node
{
	__int64 key;
	string name;
	string address;
	node *next;
	int hxdz;
}*point;
	
point HSB[Max];

int dizhi(__int64 k)//除留余数法
{
	int sum=0;
	int m;
	while(k!=0)
	{
		sum=sum+k%10;//求和
		k=k/10;
	}
	m=sum%7;//不超过11的最大质数
	return m;
}


void inhash(point HSB[],__int64 key,string name,string address)//信息写入哈希表
{
	node *p,*s;
	int n;
	n=dizhi(key);
	if(HSB[n]==NULL)
	{
		p=new node();
		p->key=key;
		p->name=name;
		p->address=address;
		p->hxdz=n;
		p->next=NULL;
		HSB[n]=p;
	}
	else if(HSB[n]!=NULL)//冲突
	{
		s=HSB[n];
		while(s->next!=NULL && s->key!=key)
			s=s->next;
		if(s->key==key)
		{
			cout<<s->name <<"已存在！"<<endl;
			return;
		}
		else
		{
			p=new node();
			p->key=key;
			p->name=name;
			p->address=address;
			p->hxdz=n;
			p->next=NULL;
			s->next=p;
		}
	}
}


void find(point HSB[],__int64 key)//查找与已知电话号码的匹配的信息
{
	int n;
	node *q;
	n=dizhi(key);
	q=HSB[n];
	while(q!=NULL&&q->key!=key)
		q=q->next;
	if(q==NULL)
	{
	cout<<"无此号码！"<<endl;
	}
	else
	{	cout<<"姓名:  ";
		cout<<q->name;
		cout<<"电话:  ";
		printf("%I64u",q->key);
		cout<<"地址:  ";
		cout<<q->address;
		cout<<"哈希地址:  ";
		cout<<q->hxdz<<endl;
	}
}


void delhash(point HSB[],__int64 key)//删除给定的号码
{
	int n;
	n=dizhi(key);
	if(HSB[n] == NULL)
	{
		cout<<"无此号码！";
		return;
	}
	else
	{
		node *p,*s;
		s=HSB[n];
		p=NULL;
		while(s->next!=NULL && s->key!=key)
		{
			p=s;
			s=s->next;
		}
		if(s->key==key)
		{
			cout<<"要删除的信息是："<<"姓名："<<s->name <<"  电话：";
			printf("%I64u",s->key);
			cout<<"  地址："<<s->address<<endl;
			cout<<"是否删除？！是则输入Y，否输入N：";
			string a;
			cin>>a;
			if(a=="Y")
			{
				if(p==NULL)
					HSB[n]=s->next;
				else
					p->next=s->next;
				delete s;
				cout<<"删除成功！";
			}
			else
				return;
		}
		else
			cout<<"查无此号码！"<<endl;
	}
}


void createhash(point HSB[])
{
	__int64 key;
	string name,address;
	cout<<"依次输入姓名 电话号码  地址：";
	cin>>name;
	scanf("%I64u",&key);
	cin>>address;
	inhash(HSB,key,name,address);
}


void shuchuhash(point HSB[])
{
	for(int i=0;i<Max;i++)
	{
		node *p;
		p=HSB[i];
		while(p!=NULL)
		{
			cout<<"姓名:"<<p->name<<"  电话:";
			printf("%I64u",p->key);
			cout<<"  地址:"<<p->address;
			cout<<"  哈希地址:";
			cout<<p->hxdz<<endl;
			p=p->next;
		}
	}
}


void view()
{
	
	cout <<"1.添加数据"<<endl;
	cout << "2.查找数据"<<endl;
	cout << "3.删除数据"<<endl;
	cout << "4.显示所有数据"<< endl;
	int a;
	cout<<"请选择要进行操作：";
	cin>>a;
	if (a != 1 && a != 2 && a != 3&&a!=4)
	{
		cout <<endl<< "错误！请重新输入！";
		scanf("%I64u",a);
	}
	switch(a)
	{
	case 1:createhash(HSB);
		break;
	case 2:__int64 two;
		cout << "输入要查找的电话号码：";
		scanf("%I64u",&two);
		find(HSB,two);
		break;
	case 3: __int64 three;
		cout << "输入要删除的电话号码：";
		scanf("%I64u",&three);
		delhash(HSB,three);
		break;
	case 4:shuchuhash(HSB);
	}

	cout<<endl<<"返回菜单请输入0"<<endl;
	cout<<"退出菜单请输入其他任意的按键"<<endl;
	int C;
	cin>>C;
	if(C==0)
	{
		cout<<endl;
		view();
	}
	
}


void main()
{
	cout << "               电话号码查询系统         "<<endl;
	view();
	system("pause");
}
