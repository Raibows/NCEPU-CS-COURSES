#include<iostream>
using namespace std;
typedef struct tnode
{
	int data;
	struct tnode *Lchild;
	struct tnode *Rchild;

}*point;




void CreateBtr(point &a)
{
	int x;
	cout << "������ֵ" << endl;
	cin >> x;
	if (x == 0)
	{
		a = NULL;
		return;
	}
	else {
		point q = new tnode;
		q->data = x;
		a = q;
		CreateBtr(a->Lchild);
		CreateBtr(a->Rchild);
	}
}


void Preorder(point &t)//�������
{
	if(t)
	{
		cout<<t->data<<" ";
		Preorder(t->Lchild);
		Preorder(t->Rchild);
	}
}
void inorder(point &t)//�������
{
	if(t)
	{
		inorder(t->Lchild);
		cout<<t->data<<" ";
		inorder(t->Rchild);
	}
}
void postorder(point &t)//�������
{
	if(t)
	{
		postorder(t->Lchild);
		postorder(t->Rchild);
		cout<<t->data<<" ";
	}
}


int main()
{
	point b = new tnode;
	CreateBtr(b);
	cout<<"����������Ϊ��";
	Preorder(b);
	cout<<"\n";
	cout<<"����������Ϊ��";
	inorder(b);
	cout<<"\n";
	cout<<"����������Ϊ��";
	postorder(b);
	cout<<"\n";
	return 0;
}