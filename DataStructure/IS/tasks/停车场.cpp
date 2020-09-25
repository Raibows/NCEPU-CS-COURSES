#include<stdio.h>
#include <stdlib.h>
#include<iostream>
#include<malloc.h>
using namespace std;
#define MAXSIZE 14					//��λ������೵��
#define n 3							//ͣ���������ͣ����
#define fee 10						//һСʱͣ��ʮ��Ǯ

struct car{							 //���峵���Ľṹ��
char bb;							//�������뿪��Ϣ
int num;							//���ƺ�
int time;							//������뿪ʱ��
};

typedef struct stack1				//����ջ�ṹ�壨ͣ������
{
int top;							//����ջ��С
struct car G[n];					//����ջԪ��
}SqStack;

struct rangweicar					//������λ�����Ľṹ��
{
	int num;
	int time;
};


typedef struct stack2				//����ջ�ṹ�壨��ʱͣ�����أ�
{
	struct rangweicar H[MAXSIZE];
	int topp;
}SqStackk;


//����ö��У���ʽ�洢�ṹ
typedef struct QNODE
{
	int data;
	QNODE *next;
}QNODE;

typedef struct linkqueue
{
	QNODE *front,*rear;
	int geshu;
}LinkQueue;



//��ͣ����������
void A_cars(SqStack *s,LinkQueue *q,struct car a) 
{
	QNODE *t;
	if(s->top!=n-1)
	{
		(s->top)++;
		(s->G[s->top]).bb =a.bb;
		(s->G[s->top]).num =a.num;
		(s->G[s->top]).time =a.time;
	}
	else 
	{
	cout<<"ͣ��������\n";
		t =new QNODE;
		t->data =a.num;
		t->next = NULL;
		q->rear->next =t;
		q->rear =t;
		q->geshu++;
	}
}


int D_cars(SqStack *s,LinkQueue *q,struct car d)
{ 
	int i,j,l,x,y;
	QNODE *p;
	SqStackk *k;
	if(d.num==(s->G[s->top].num))  //���뿪�ĳ�Ϊ���ͣ��ͣ�����еĳ�
	{
		x = d.time-s->G[s->top].time;
		y =fee*x;
		cout<<"ͣ��ʱ��Ϊ:"<<x<<"Сʱ,ͣ������Ϊ:"<<y<<"Ԫ!\n";
		if(q->geshu==0)//����޳�����������
		{	
			cout<<"���Ϊ�գ�\n";
			s->top =s->top-1;
			return 0;
		}
		else//����г�����ͣ��ͣ����
		{
			p=q->front->next;
			q->front->next=p->next;
			(s->G[s->top]).num=p->data;
			(s->G[s->top]).time=d.time;
			delete(p);
			q->geshu--;
			if(q->front->next==NULL)//����������
			{
				q->rear=q->front;
				return 1;
			}
		}
	}
	else			//�������һ������ͣ�����ģ���Ҫ��λ��
	{
		for(i=0;i<(s->top);i++)
		{
			if(s->G[i].num!=d.num)
				continue;
			else
				break;
		}
		if(i>=(s->top))		//ͣ������û�����복�ŵĳ�
		{
		cout<<"ERROR!\n";
		return -1;
		}
		x = d.time-(s->G[i]) . time;
		y = fee*x;
		cout<<"ͣ��ʱ��Ϊ:"<<x<<"Сʱ,ͣ������Ϊ:"<<y<<"Ԫ!\n";
		k =new SqStackk ;
		k->topp = -1;
		for(j=(s->top); j>i; j--)// �뿪�ĳ�����ĳ���������ʱջ
		{
			k->topp++;
			(k->H[k->topp]) .num =(s->G[j]) .num;
			(k->H[k->topp]) .time =(s->G[j]) . time;
			s->top--;
		}
		cout<<"��ʱջ����ϢΪ: (���ź�ʱ��) :\n";
	
		for( l=0; l<=(k->topp); l++ )//��ʾ����ջ�еĳ�����Ϣ
		{
			printf ("%d, %d\n", (k->H[l]).num, (k->H[l]).time) ;

		}

		s->top--;

		while (k->topp>=0)//��ʱջ�ĳ���ͣ����
		{	s-> top++;
			(s->G[s->top]) .bb = 'A';
			(s->G[s->top]) .num =(k->H [k->topp]).num;
			(s->G[s->top]) .time =(k->H[k->topp]).time;
			k->topp--;
		}

		if (q->geshu==0)//����ȴ�����Ϊ0
		{
			cout<<"���Ϊ�գ�\n";
			return 2;
		}
		else//��Ϊ0������ͣ����
		{	s-> top++;
			p = q-> front->next;    
			q-> front->next = p->next;
			(s->G[s->top]) .num = p->data;
			(s->G[s->top]) .time = d.time;
			free(p) ;
			q->geshu--;
			if (q->front->next==NULL)
				q->rear = q-> front;
			return 3;
		}
	}
}



//ͨ���������ĳ�����Ϣ������غ���ʵ�ֲ���
void Judge_Output(SqStack *s, LinkQueue *q, struct car *r)
{
	if( (*r).bb=='E' || (*r).bb=='e')
	{
		cout<<"STOP!\n" ;
	}
	else if((*r).bb=='P' ||(*r).bb=='p')
	{	
		cout<<"ͣ��������������Ϊ:"<<(s->top) +1<<"\n" ;
	} 
	else if((*r).bb=='W' || (*r).bb=='w')
	{	
		cout<<"�������������Ϊ:"<< q->geshu<<"\n";
	}
	else if((*r).bb=='A' || (*r).bb=='a')
	{
		A_cars(s,q,*r);
	}
	else if((*r).bb=='D' || (*r).bb=='d')
	{	
		D_cars(s,q,*r);
	}
	else {
		cout<<"ERROR! \n" ;
	}
}

void main()
{
	SqStack *s;
	LinkQueue *q;
	QNODE *p;
	char d;
	int a,b;
	struct car aa [MAXSIZE];
	int  i;
	s =new SqStack ;
	s->top =-1;
	q = new LinkQueue ;
	p = new QNODE ;
	p->next = NULL;
	q->front = q->rear = p;
	q->geshu=0;
	cout<<"ͣ��������ϵͳ\n";
	cout<<"********************************************************\n" ;
	cout<<"A.��������\nD.�����뿪\nP.ͣ������������\nW.�����������\nE.�˳�\n";
	cout<<"\n";
	for (i=0; i<MAXSIZE;i++)
	{	cout<<"�����복����״̬�����ƺź�ʱ��: \n";
		cin>>d;
		cin>>a>>b;
	    aa[i].bb=d;
		aa[i].num=a;
		aa[i].time=b;
		Judge_Output(s,q,&aa[i]);
		if(aa[i].bb=='E')
			break;
	}
}