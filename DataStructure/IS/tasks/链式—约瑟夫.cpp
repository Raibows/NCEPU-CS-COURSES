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
	cout<<"����������:";
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
		cout<<"�����ڣ�";
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
		cout<<"��"<<k<<"�����е���:";
		cout<<p->data<<"\n";
		k++;
		q->next=p->next;//���ɾ��
		p=p->next;//pָ��ɾ�����ĺ�һ�ڵ�
	}
}	 


void main()
{
	int n,m,s;

	cout<<"������������";
	cin>>n;
	Pnode head=CreateList(n);
	cout<<"������Լɪ�򻷵���ʼ���s�ͼ���ֵm��ֵ�ֱ��ǣ�";
	cin>>s>>m;


    yue_node(head,s,m,n);

}