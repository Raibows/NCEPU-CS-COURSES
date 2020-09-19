#include <iostream>
#include <crtdbg.h>
#include <cstring>
#include <assert.h>
#include "Grammer.h"
#include "GenStruct.h"
using namespace std;

//�õ�����ĵ�ַ
string getNextquad()
{
	string s;
	int2str(genStructs.size(), s);
	return s;
}

typedef token DataType;

//�﷨���ڵ�ṹ��
struct TreeNode
{
	TreeNode()
	{
		fristnextquad = getNextquad();
		nextquad = getNextquad();
		value = data.name;
		sibling = NULL;
		child = NULL;
	}
	DataType data;
	TreeNode * sibling; //���ֵܽ��
	TreeNode * child;   //���ӽ��
	string nextquad;
	string fristnextquad;
	string value;  //�����ֵ,����ʽ����Ԫ����T1��T2
	vector<string>nextlist;
	vector<string>truelist; //����ڼ�
	vector<string>falselist; //���ڼ�
};


// �洢����Ϊ TreeNode*
typedef TreeNode *DataStack;


//������
class Tree
{
private:
	TreeNode *root = NULL;
public:
	Tree(const DataType &data);
	Tree() {}
	~Tree();
	TreeNode * GetRoot() { return root; }
	void Init(const DataType &data);
	void Destroy(TreeNode * p);
	TreeNode * InsertChild(TreeNode *p, DataType data);
	void InsertAllChild(TreeNode *p, vector<DataType> data);
	TreeNode * InsertSibling(TreeNode *p, DataType data);
	void CreateTree(TreeNode *t) {
		root = t;
	}
};


//������ջ
class Stack
{
private:
	struct Node
	{
		DataStack data;
		Node *next;
	};
	Node * head;
	void Init()
	{
		head = NULL;
	}
	void Destroy()
	{
		for (Node* p = head; p != NULL;)
		{
			Node *pTemp = p->next;
			delete p;
			p = pTemp;
		}
		head = NULL;
	}
public:
	Stack()
	{
		Init();
	}
	~Stack()
	{
		Destroy();
	}
};


//��ͨ������ʵ��
#pragma region classTreeMethod

Tree::Tree(const DataType &data)
{
	Init(data);
}


Tree::~Tree()
{
	Destroy(root);
}

//��һ�����ڵ���
void Tree::Init(const DataType &data)
{
	root = new TreeNode;
	root->child = NULL;
	root->sibling = NULL;
	root->data = data;
}


//��������
void Tree::Destroy(TreeNode * p)
{
	if (p == NULL)
	{
		return;
	}
	Destroy(p->sibling);
	Destroy(p->child);
	p = NULL;
	delete p;
}


//���һ���ӽڵ�
TreeNode * Tree::InsertChild(TreeNode * p, DataType data)
{
	if (p->child)
	{
		return p->child; //�����ӽ��
	}
	TreeNode *pNew = new TreeNode;
	pNew->data = data;
	p->child = pNew;
	return pNew;
}



//����ֵܽڵ㣨treenode�ࣩ
TreeNode * InsertSibling(TreeNode * p, TreeNode * data)
{
	if (p->sibling)
	{
		return p->sibling;//�����ֵܽ��
	}
	p->sibling = data;
	return p->sibling;
}


//���������ӽڵ�
TreeNode * InsertAllChild(TreeNode * p, vector<TreeNode> data)
{

	for (int i = data.size() - 1; i >= 0; i--)
	{
		TreeNode *Newtemp = new TreeNode;
		Newtemp->data = data[i].data;
		Newtemp->child = data[i].child;
		Newtemp->sibling = data[i].sibling;
		if (!p->child)
		{
			p->child = Newtemp;
			continue;
		}
		TreeNode *n = p->child;
		while (n->sibling)
		{
			n = n->sibling;
		}
		n = InsertSibling(n, Newtemp);
		n = n->sibling;
	}
	return p;
}


//����һ���µ����ڵ㣨token�ࣩ
TreeNode *CreateTreeNode(DataType data)
{
	TreeNode *pNew = new TreeNode;
	pNew->data = data;
	return pNew;
}

#pragma endregion


//���嶯����������Ԫʽ��
void GrammarAction(TreeNode  *pNew, vector<TreeNode> pushend, int index) // index�������ķ����� pushend����������  pNew �����
{

	string value1;
	string backpatchfalse;
	switch (index)
	{
	case 0:
		pNew->nextlist = pushend[1].nextlist;
		break;
	case 1:
		pNew->nextlist = pushend[0].nextlist;
		break;
	case 2:
		pNew->nextlist = pushend[0].nextlist;
		break;
	case 3:
		pNew->nextlist = pushend[0].nextlist;
		break;
	case 4: //if B then S
		backpatch(pushend[pushend.size() - 2].truelist, pushend[pushend.size() - 2].nextquad);
		pNew->nextlist = merge(pushend[0].nextlist, pushend[pushend.size() - 2].falselist);
		break;
	case 5://if B then L else S,then Ҫ��ת�� else����
		int2str(stoi(pushend[2].nextquad) + 1, backpatchfalse);
		backpatch(pushend[pushend.size() - 2].truelist, pushend[pushend.size() - 2].nextquad);
		backpatch(pushend[pushend.size() - 2].falselist, backpatchfalse);
		pNew->nextlist = merge(pushend[0].nextlist, pushend[pushend.size() - 2].falselist);
		CreateGen("j", "_", "_", pushend[0].nextquad);
		pNew->nextquad = getNextquad();
		InsertGentoIndex(getNextquad(), pushend[2].nextquad);
		break;
	case 6://s->while B do S
		backpatch(pushend[2].truelist, pushend[2].nextquad);
		pNew->nextlist = pushend[2].falselist;
		CreateGen("j", "_", "_", pushend[2].fristnextquad);
		pNew->nextquad = getNextquad();
		backpatch(pushend[2].falselist, getNextquad());
		break;
	case 7://begin  L end
		pNew->nextlist = pushend[1].nextlist;
		break;
	case 8://var D
		break;
	case 9:// ?
		break;
	case 10://S->A
		break;
	case 11: //D:->id:K
		break;
	case 12://k->integer
		break;
	case 13://k->bool
		break;
	case 14://k->real
		break;
	case 15://A-> id:=E
		CreateGen(pushend[1].data.name, pushend[0].value, "_", pushend[2].data.name);
		pNew->nextquad = getNextquad();
		break;
	case 16://E->E+T
		value1 = NewTempStruct();
		CreateGen("+", pushend[2].value, pushend[0].value, value1);
		pNew->value = value1;
		pNew->nextquad = getNextquad();
		break;
	case 17://E->E-T
		value1 = NewTempStruct();
		CreateGen("-", pushend[2].value, pushend[0].value, value1);
		pNew->value = value1;
		pNew->nextquad = getNextquad();
		break;
	case 18:
		pNew->value = pushend[0].value;
		break;
	case 19: //E->-E
		value1 = NewTempStruct();
		CreateGen("-", "_", pushend[0].value, value1);
		pNew->nextquad = getNextquad();
		pNew->value = value1;
		break;
	case 20://B-> B or N
		backpatch(pushend[pushend.size() - 1].falselist, pushend[pushend.size() - 1].nextquad);
		pNew->truelist = merge(pushend[pushend.size() - 1].truelist, pushend[0].truelist);
		pNew->falselist = pushend[0].falselist;
		pNew->fristnextquad = pushend[2].fristnextquad;
		break;
	case 21://B->N
		pNew->falselist = pushend[0].falselist;
		pNew->truelist = pushend[0].truelist;
		pNew->value = pushend[0].value;
		break;
	case 22://B->not B
		pNew->falselist = pushend[0].truelist;
		pNew->truelist = pushend[0].falselist;
		pNew->value = pushend[0].value;
		break;
	case 23: //T->T*F
		value1 = NewTempStruct();
		CreateGen("*", pushend[2].value, pushend[0].value, value1);
		pNew->value = value1;
		pNew->nextquad = getNextquad();
		break;
	case 24: //T->T/F
		value1 = NewTempStruct();
		CreateGen("/", pushend[2].value, pushend[0].value, value1);
		pNew->value = value1;
		pNew->nextquad = getNextquad();
		break;
	case 25://T->F
		pNew->falselist = pushend[0].falselist;
		pNew->truelist = pushend[0].truelist;
		pNew->value = pushend[0].value;
		break;
	case 26://F->(E)
		pNew->falselist = pushend[1].falselist;
		pNew->truelist = pushend[1].truelist;
		pNew->value = pushend[1].value;
		break;
	case 27://F->id
		pNew->value = pushend[0].data.name;
		break;
	case 28://N->N and M
		backpatch(pushend[pushend.size() - 1].truelist, pushend[pushend.size() - 1].nextquad);
		pNew->falselist = merge(pushend[pushend.size() - 1].falselist, pushend[0].falselist);
		pNew->truelist = pushend[0].truelist;
		pNew->fristnextquad = pushend[2].fristnextquad;
		break;
	case 29:
		pNew->falselist = pushend[0].falselist;
		pNew->truelist = pushend[0].truelist;
		pNew->value = pushend[0].value;
		break;
	case 30: //M->(B)
		pNew->falselist = pushend[1].falselist;
		pNew->truelist = pushend[1].truelist;
		pNew->value = pushend[1].value;
		break;
	case 31: //M->id <id
	case 32: //>
	case 33: //<>
	case 34: //<=
	case 35://>=
	case 36://=
		string s1;
		int2str(stoi(getNextquad()) + 1, s1);
		pNew->truelist.push_back(getNextquad());
		pNew->falselist.push_back(s1);
		CreateGen("j" + pushend[1].data.name, pushend[2].data.name, pushend[0].data.name, "0");
		CreateGen("j", "_", "_", "0");
		pNew->nextquad = getNextquad();
		break;

	}
}