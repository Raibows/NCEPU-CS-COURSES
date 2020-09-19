#include <iostream>
using namespace std;

typedef struct Node 
{
	int data;
	struct Node *next;
} *Pnode;

Pnode CreateList(int n)
{
	Pnode head=new Node;
	Pnode p=new Node;
	head->next=p;
	cout<<"请输入人名:";
	int k;
	cin>>k;
	p->data=k;
	int i=1;
	for(i=1;i<n;i++)
	{
		cin>>k;
		Pnode q=new Node;
		q->data=k;
		p->next=q;
		p=q;
	}
	p->next=head->next;   
	return head;
}

void panduan(Pnode head){
	if(!head->next){
		cout<<"表不存在！";
		return ;
	}
}

void yue_node(Pnode head,int s,int m,int n){
	panduan (head);
	Pnode p=head->next;
	Pnode q=head;
	int k=1;
	for(int j=1;j<s;j++)
	{
		p=p->next;
		q=q->next;
	}
		
	
	for(int w=0;w<n;w++)
	{
		for(int r=1;r<m;r++)
		{
			p=p->next;
			q=q->next;
		}
		cout<<"第"<<k<<"个出列的是:";
		cout<<p->data<<"\n";
		k++;
		q->next=p->next;//结点删除
		p=p->next;//p指向删除结点的后一节点
	}
}	 


void main()
{
	int n,m,s;

	cout<<"输入总人数：";
	cin>>n;
	Pnode head=CreateList(n);
	cout<<"请输入约瑟夫环的起始序号s和计数值m的值分别是：";
	cin>>s>>m;


    yue_node(head,s,m,n);

}