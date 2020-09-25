#include<stdio.h>
#include <stdlib.h>
#include<iostream>
#include<malloc.h>
using namespace std;
#define MAXSIZE 14					//让位场地最多车数
#define n 3							//停车场中最多停车数
#define fee 10						//一小时停车十块钱

struct car{							 //定义车辆的结构体
char bb;							//进入与离开信息
int num;							//车牌号
int time;							//进入或离开时间
};

typedef struct stack1				//定义栈结构体（停车场）
{
int top;							//定义栈大小
struct car G[n];					//定义栈元素
}SqStack;

struct rangweicar					//定义让位车辆的结构体
{
	int num;
	int time;
};


typedef struct stack2				//定义栈结构体（临时停靠场地）
{
	struct rangweicar H[MAXSIZE];
	int topp;
}SqStackk;


//便道用队列，链式存储结构
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



//入停车场或入便道
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
	cout<<"停车场已满\n";
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
	if(d.num==(s->G[s->top].num))  //若离开的车为最后停在停车场中的车
	{
		x = d.time-s->G[s->top].time;
		y =fee*x;
		cout<<"停车时间为:"<<x<<"小时,停车费用为:"<<y<<"元!\n";
		if(q->geshu==0)//便道无车，函数返回
		{	
			cout<<"便道为空！\n";
			s->top =s->top-1;
			return 0;
		}
		else//便道有车，车停入停车场
		{
			p=q->front->next;
			q->front->next=p->next;
			(s->G[s->top]).num=p->data;
			(s->G[s->top]).time=d.time;
			delete(p);
			q->geshu--;
			if(q->front->next==NULL)//如果便道空了
			{
				q->rear=q->front;
				return 1;
			}
		}
	}
	else			//不是最后一个进入停车场的，需要让位了
	{
		for(i=0;i<(s->top);i++)
		{
			if(s->G[i].num!=d.num)
				continue;
			else
				break;
		}
		if(i>=(s->top))		//停车场中没有输入车号的车
		{
		cout<<"ERROR!\n";
		return -1;
		}
		x = d.time-(s->G[i]) . time;
		y = fee*x;
		cout<<"停车时间为:"<<x<<"小时,停车费用为:"<<y<<"元!\n";
		k =new SqStackk ;
		k->topp = -1;
		for(j=(s->top); j>i; j--)// 离开的车后面的车都进入临时栈
		{
			k->topp++;
			(k->H[k->topp]) .num =(s->G[j]) .num;
			(k->H[k->topp]) .time =(s->G[j]) . time;
			s->top--;
		}
		cout<<"临时栈中信息为: (车号和时间) :\n";
	
		for( l=0; l<=(k->topp); l++ )//显示在新栈中的车辆信息
		{
			printf ("%d, %d\n", (k->H[l]).num, (k->H[l]).time) ;

		}

		s->top--;

		while (k->topp>=0)//临时栈的车入停车场
		{	s-> top++;
			(s->G[s->top]) .bb = 'A';
			(s->G[s->top]) .num =(k->H [k->topp]).num;
			(s->G[s->top]) .time =(k->H[k->topp]).time;
			k->topp--;
		}

		if (q->geshu==0)//便道等待车数为0
		{
			cout<<"便道为空！\n";
			return 2;
		}
		else//不为0，进入停车场
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



//通过传递来的车辆信息调用相关函数实现操作
void Judge_Output(SqStack *s, LinkQueue *q, struct car *r)
{
	if( (*r).bb=='E' || (*r).bb=='e')
	{
		cout<<"STOP!\n" ;
	}
	else if((*r).bb=='P' ||(*r).bb=='p')
	{	
		cout<<"停车场中汽车辆数为:"<<(s->top) +1<<"\n" ;
	} 
	else if((*r).bb=='W' || (*r).bb=='w')
	{	
		cout<<"便道中汽车辆数为:"<< q->geshu<<"\n";
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
	cout<<"停车场管理系统\n";
	cout<<"********************************************************\n" ;
	cout<<"A.车辆到达\nD.车辆离开\nP.停车场车辆总数\nW.便道车辆总数\nE.退出\n";
	cout<<"\n";
	for (i=0; i<MAXSIZE;i++)
	{	cout<<"请输入车辆的状态，车牌号和时间: \n";
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