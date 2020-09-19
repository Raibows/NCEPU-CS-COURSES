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
	cout << "输入结点值" << endl;
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


void Preorder(point &t)//先序遍历
{
	if(t)
	{
		cout<<t->data<<" ";
		Preorder(t->Lchild);
		Preorder(t->Rchild);
	}
}
void inorder(point &t)//中序遍历
{
	if(t)
	{
		inorder(t->Lchild);
		cout<<t->data<<" ";
		inorder(t->Rchild);
	}
}
void postorder(point &t)//后序遍历
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
	cout<<"先序遍历输出为：";
	Preorder(b);
	cout<<"\n";
	cout<<"中序遍历输出为：";
	inorder(b);
	cout<<"\n";
	cout<<"后序遍历输出为：";
	postorder(b);
	cout<<"\n";
	return 0;
}