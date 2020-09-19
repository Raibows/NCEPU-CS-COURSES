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

int dizhi(__int64 k)//����������
{
	int sum=0;
	int m;
	while(k!=0)
	{
		sum=sum+k%10;//���
		k=k/10;
	}
	m=sum%7;//������11���������
	return m;
}


void inhash(point HSB[],__int64 key,string name,string address)//��Ϣд���ϣ��
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
	else if(HSB[n]!=NULL)//��ͻ
	{
		s=HSB[n];
		while(s->next!=NULL && s->key!=key)
			s=s->next;
		if(s->key==key)
		{
			cout<<s->name <<"�Ѵ��ڣ�"<<endl;
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


void find(point HSB[],__int64 key)//��������֪�绰�����ƥ�����Ϣ
{
	int n;
	node *q;
	n=dizhi(key);
	q=HSB[n];
	while(q!=NULL&&q->key!=key)
		q=q->next;
	if(q==NULL)
	{
	cout<<"�޴˺��룡"<<endl;
	}
	else
	{	cout<<"����:  ";
		cout<<q->name;
		cout<<"�绰:  ";
		printf("%I64u",q->key);
		cout<<"��ַ:  ";
		cout<<q->address;
		cout<<"��ϣ��ַ:  ";
		cout<<q->hxdz<<endl;
	}
}


void delhash(point HSB[],__int64 key)//ɾ�������ĺ���
{
	int n;
	n=dizhi(key);
	if(HSB[n] == NULL)
	{
		cout<<"�޴˺��룡";
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
			cout<<"Ҫɾ������Ϣ�ǣ�"<<"������"<<s->name <<"  �绰��";
			printf("%I64u",s->key);
			cout<<"  ��ַ��"<<s->address<<endl;
			cout<<"�Ƿ�ɾ��������������Y��������N��";
			string a;
			cin>>a;
			if(a=="Y")
			{
				if(p==NULL)
					HSB[n]=s->next;
				else
					p->next=s->next;
				delete s;
				cout<<"ɾ���ɹ���";
			}
			else
				return;
		}
		else
			cout<<"���޴˺��룡"<<endl;
	}
}


void createhash(point HSB[])
{
	__int64 key;
	string name,address;
	cout<<"������������ �绰����  ��ַ��";
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
			cout<<"����:"<<p->name<<"  �绰:";
			printf("%I64u",p->key);
			cout<<"  ��ַ:"<<p->address;
			cout<<"  ��ϣ��ַ:";
			cout<<p->hxdz<<endl;
			p=p->next;
		}
	}
}


void view()
{
	
	cout <<"1.�������"<<endl;
	cout << "2.��������"<<endl;
	cout << "3.ɾ������"<<endl;
	cout << "4.��ʾ��������"<< endl;
	int a;
	cout<<"��ѡ��Ҫ���в�����";
	cin>>a;
	if (a != 1 && a != 2 && a != 3&&a!=4)
	{
		cout <<endl<< "�������������룡";
		scanf("%I64u",a);
	}
	switch(a)
	{
	case 1:createhash(HSB);
		break;
	case 2:__int64 two;
		cout << "����Ҫ���ҵĵ绰���룺";
		scanf("%I64u",&two);
		find(HSB,two);
		break;
	case 3: __int64 three;
		cout << "����Ҫɾ���ĵ绰���룺";
		scanf("%I64u",&three);
		delhash(HSB,three);
		break;
	case 4:shuchuhash(HSB);
	}

	cout<<endl<<"���ز˵�������0"<<endl;
	cout<<"�˳��˵���������������İ���"<<endl;
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
	cout << "               �绰�����ѯϵͳ         "<<endl;
	view();
	system("pause");
}
