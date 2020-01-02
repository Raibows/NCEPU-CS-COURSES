#include "tree.h"
#include <iomanip>
#define Grammar_Maxid 13

//�ж��Ƿ�����ID��
bool typeIsId(string str)
{
	if (str == "��ʶ��" || str == "����" || str == "����" || str == "ʵ��")
		return true;
	return false;
}

//�ս���ṹ��
struct vecEnd
{
	string end;
	int index;
	vecEnd(string e, int i) { end = e; index = i; }
};


class Grammar_FL
{
private:
	vector<string> isEnd;
	string notEnd;
	int id;
public:
	vector<string> fristvt;
	vector<string> lastvt;
	Grammar_FL() {};
	int getid() { return id; }
	string getNotEnd() { return notEnd; }
	Grammar_FL(int id) { InitGrammar_FL(id); };
	void InitGrammar_FL(int id);
	//�󼯺�ʱ�ж��Ƿ��ظ�����
	bool isexistFirstvt(string str)
	{
		for (int i = 0; i < fristvt.size(); i++)
			if (str == fristvt[i])
				return true;
		return false;
	}
	bool isexistLastvt(string str)
	{
		for (int i = 0; i < lastvt.size(); i++)
			if (str == lastvt[i])
				return true;
		return false;
	}
	/*
	void  print()
	{
		cout << notEnd << "\t Fristvt:  ";
		for (int i = 0; i < fristvt.size(); i++)
			cout << fristvt[i] << " ";
		cout << "\t";
		cout << "Lastvt:  ";
		for (int i = 0; i < lastvt.size(); i++)
			cout << lastvt[i] << " ";
		cout << endl;
	}*/
};


vector <TreeNode> CreateTreeStack;

//�õ���ǰ��Լ����ķ��ս������
int returnStackendIndex(int top)
{
	int sizeinStack = 0;
	for (int i = 0; i < top;)
	{
		if (CreateTreeStack[sizeinStack].data.type == "���ս��") sizeinStack++;
		else
		{
			i++;
			sizeinStack++;
		}
	}
	if (CreateTreeStack[sizeinStack].data.type == "���ս��") sizeinStack++;
	return sizeinStack;
}

//�������id����ʽ�Ƴ����ս����
void Grammar_FL::InitGrammar_FL(int id)
{
	this->id = id;
	for (int i = 0; i < grammar_length; i++)
	{
		if (grammar[i].getid() == id)
		{

			notEnd = grammar[i].getINP();
			vector<string> vec = split(grammar[i].getOUP(), " ");
			//��ֵFristvt
			if (!isUpper(vec[0]) && vec[0] != "?")
			{
				if (!isexistFirstvt(vec[0]))
					fristvt.push_back(vec[0]);
			}
			else
			{
				if (vec.size() >= 2)
				{
					if (!isUpper(vec[1]))
					{
						if (!isexistFirstvt(vec[1]))
							fristvt.push_back(vec[1]);
					}
				}
			}
			//��ֵLastvt
			if (!isUpper(vec[vec.size() - 1]) && vec[vec.size() - 1] != "?")
			{
				if (!isexistLastvt(vec[vec.size() - 1]))
					lastvt.push_back(vec[vec.size() - 1]);
			}
			else
			{
				if (vec.size() >= 2)
				{
					if (!isUpper(vec[vec.size() - 2]))
					{
						if (!isexistLastvt(vec[vec.size() - 2]))
							lastvt.push_back(vec[vec.size() - 2]);
					}
				}
			}
		}

	}
}


class Table
{
public:
	Table();
	~Table();
	void finishGra();    //���Fristvt & Lastvt
	//void printTable();
	bool Match(vector<token>, string &);
	void printBuffer();
	void printCreateTreeStack();
	void printSignStack();
private:
	Grammar_FL *flgrammar[Grammar_Maxid];
	vector<vecEnd> end;   //�ս������
	int **t_relation;
	void initEnd();
	bool isexistEnd(vecEnd str)
	{
		for (int i = 0; i < end.size(); i++)
			if (str.end == end[i].end)
				return true;
		return false;
	}
	//�����ַ�����ѯ�ս����end���е�����
	int findend(string str)
	{
		for (int i = 0; i < end.size(); i++)
		{
			if (end[i].end == str)
				return i;
		}
		return -1;
	}
	vector <token> signStack;   //����ջ
	vector <token> Buffer;//���뻺����
	//�õ�token name����
	string getSignStackname(token t)
	{

		if (typeIsId(t.type))
			return "id";
		return t.name;
	}
	Tree *GrammarTree = NULL;
};

//���������ȹ�ϵ��
void Table::initEnd()
{

	for (int i = 0; i < grammar_length; i++)
	{
		int count = 0;
		vector<string> vec = grammar[i].getisEnd();
		for (int j = 0; j < vec.size(); j++)
		{
			vecEnd e(vec[j], count);
			if (!isexistEnd(e) && e.end != "?")
				end.push_back(e);
		}
	}
	//t_relation��ʼ��,0�����޹�ϵ,1����С��<,2�������=,3�������>
	int size = end.size();
	t_relation = new int *[size];
	for (int i = 0; i < size; i++)
		t_relation[i] = new int[size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			t_relation[i][j] = 0;     //��ʼ��Ϊ�հ�
		//���1<  ,...aP....  a<Fristvt(P)
	for (int i = 0; i < grammar_length; i++)  //�ӵ�һ���ķ���ʼ
	{
		vector<string> vec = split(grammar[i].getOUP(), " ");
		for (int j = 0; j < vec.size() - 1; j++) //�ӵ�һ�����ʿ�ʼ�ж��Ƿ����ս��
		{
			if (isUpper(vec[j]))//�Ƿ��ս��
			{
				//�ҵ�Lasttv(vec[j]) > vec[j+1]
				vector <string> vec1;
				for (int k = 0; k < Grammar_Maxid; k++)
				{
					if (flgrammar[k]->getNotEnd() == vec[j])
					{
						vec1 = flgrammar[k]->lastvt;
						break;
					}
				}

				for (int k = 0; k < vec1.size(); k++)
				{
					int row = findend(vec1[k]);
					int col = findend(vec[j + 1]);
					t_relation[row][col] = 3;   //3����>
				}
			}
			else//�ս��
			{
				//�ж� isUpper(vec[j+1]),�ս����=�����ս���� vec[j] < Fristvt(vec[j+1])
				if (isUpper(vec[j + 1])) //�ڶ����Ƿ��ս��
				{
					vector <string> vec1;
					for (int k = 0; k < Grammar_Maxid; k++)
					{
						if (flgrammar[k]->getNotEnd() == vec[j + 1])
						{
							vec1 = flgrammar[k]->fristvt;
							break;
						}
					}

					for (int k = 0; k < vec1.size(); k++)
					{
						int row = findend(vec[j]);
						int col = findend(vec1[k]);
						t_relation[row][col] = 1;   //1����<
					}
					//�жϵ������ǲ����ս��
					if (j + 2 < vec.size())
					{
						if (!isUpper(vec[j + 2])) //���ս��
						{
							int row = findend(vec[j]);
							int col = findend(vec[j + 2]);
							t_relation[row][col] = 2;  //��=  ���� aQb
						}
					}
				}
				else //=
				{
					int row = findend(vec[j]);
					int col = findend(vec[j + 1]);
					t_relation[row][col] = 2; //2����=
				}
			}
		}
		//khkj  �Ⱥ� = ��ֵ �� S-> if B then S else S  if=then=else
		for (int i = 0; i < (int)vec.size() - 2; i++)
		{
			string str1 = vec[i];
			string str2 = vec[i + 1];
			string str3 = vec[i + 2];
			if (!isUpper(str1))
			{

				if (isUpper(vec[i + 1]))
				{
					int row = findend(vec[i]);
					int col = findend(vec[i + 2]);
					t_relation[row][col] = 2;
				}
				else
				{
					int row = findend(vec[i]);
					int col = findend(vec[i + 1]);
					t_relation[row][col] = 2;
				}
			}
			else
			{
				if (!isUpper(vec[i + 1]) && !isUpper(vec[i + 2]))
				{
					int row = findend(vec[i + 1]);
					int col = findend(vec[i + 2]);
					t_relation[row][col] = 2;
				}
			}
		}
	}

}

//���캯��(������Ľ�������Ľ�����
Table::Table()
{
	GrammarTree = new Tree();     //�����﷨��
	for (int i = 0; i < Grammar_Maxid; i++)
	{
		flgrammar[i] = new Grammar_FL(i);
	}
	finishGra();   //���ú������������
	initEnd();     //���������ȹ�ϵ��
}


//��������
Table::~Table()
{
	//�ͷſռ� flgrammar
	for (int i = 0; i < Grammar_Maxid; i++)
	{
		delete flgrammar[i];
		flgrammar[i] = NULL;
	}

	//�ͷſռ� t_relation
	for (int i = 0; i < end.size(); i++)
	{
		delete[] t_relation[i];
		t_relation[i] = NULL;

	}
	delete t_relation;
	t_relation = NULL;
	GrammarTree->Destroy(GrammarTree->GetRoot());
	delete GrammarTree;
	GrammarTree = NULL;
}

//���firstvt��lastvt����
void Table::finishGra()
{

	for (int id = Grammar_Maxid - 1; id >= 0; id--)
	{
		for (int i = 0; i < grammar_length; i++)
		{
			if (grammar[i].getid() == id)
			{
				vector<string> vec = split(grammar[i].getOUP(), " ");

				if (isUpper(vec[0]) && vec[0] != flgrammar[id]->getNotEnd())
				{
					for (int j = 0; j < Grammar_Maxid; j++)
					{
						if (vec[0] == flgrammar[j]->getNotEnd())
						{
							for (int k = 0; k < flgrammar[j]->fristvt.size(); k++)
							{
								if (!flgrammar[id]->isexistFirstvt(flgrammar[j]->fristvt[k]))
									flgrammar[id]->fristvt.push_back(flgrammar[j]->fristvt[k]);
							}

						}
					}
				}
				//���Lastvt
				int lastindex = vec.size() - 1;
				if (isUpper(vec[lastindex]) && vec[lastindex] != flgrammar[id]->getNotEnd())
				{
					for (int j = 0; j < Grammar_Maxid; j++)
					{
						if (vec[lastindex] == flgrammar[j]->getNotEnd())
						{
							for (int k = 0; k < flgrammar[j]->lastvt.size(); k++)
							{
								if (!flgrammar[id]->isexistLastvt(flgrammar[j]->lastvt[k]))
									flgrammar[id]->lastvt.push_back(flgrammar[j]->lastvt[k]);
							}

						}
					}
				}

			}

		}
	}


}  //


//���������ȱ�
/*
void Table::printTable()
{
	//�����ͷ
	cout << "  ";
	for (int i = 0; i < end.size(); i++)
	{
		cout << end[i].end << "  ";
	}
	cout << endl;
	//�����
	for (int row = 0; row < end.size(); row++)
	{   //�������
		cout << end[row].end;
		for (int col = 0; col < end.size(); col++)
		{
			cout << t_relation[row][col] << " ";
		}
		cout << endl;
	}
}
*/

//�����ǰ���뻺����
void Table::printBuffer()
{
	cout << "��ǰ���뻺����:  ";
	for (int i = 0; i < Buffer.size(); i++)
		cout << Buffer[i].name;
	cout << endl;
}

//���
void Table::printCreateTreeStack()
{
	for (int i = 0; i < CreateTreeStack.size(); i++)
		cout << CreateTreeStack[i].data.name;
	cout << endl;
}


//�����ǰ����ջ
void Table::printSignStack()
{
	cout << "��ǰ����ջ:  ";
	for (int i = 0; i < CreateTreeStack.size(); i++)
		cout << CreateTreeStack[i].data.name;
	cout << endl;
	/*for (int i = 0; i < signStack.size(); i++)
		cout <<  signStack[i].name;
	cout << endl;*/
}


//��Լ��������Ԫʽ
bool Table::Match(vector<token>tokens, string &ErrorMessage)
{
	ErrorMessage = "";
	token temp("#", 0, -1, "������", 0);
	signStack.push_back(temp);
	CreateTreeStack.push_back(*CreateTreeNode(temp));
	Buffer.push_back(temp);
	for (int i = tokens.size() - 1; i >= 0; i--)
	{
		Buffer.push_back(tokens[i]);
	}
	while (true) {
		printSignStack();
		printBuffer();
		//printCreateTreeStack();
		token t = Buffer[Buffer.size() - 1];
		int row = findend(getSignStackname(signStack[signStack.size() - 1]));
		int col = -1;
		typeIsId(t.type) ? col = findend("id") : col = findend(t.name);
		if (col == -1)
		{
			ErrorMessage = "�Ƿ��ַ�" + t.name;
			printBuffer();
			return false;
		}
		int result = t_relation[row][col];

		switch (result)
		{
		case 0:
			ErrorMessage = t.name + "�������ִ���";
			printBuffer();
			return false;
			break;
		case 1: // < �ƽ�
			signStack.push_back(t);
			CreateTreeStack.push_back(*CreateTreeNode(t));
			Buffer.pop_back();
			break;
		case 2: // =  �ƽ�
			//�ж��Ƿ�Ϊ #
			if (t.name == "#") {
				//������
				token temp("W", 0, -1, "���ս��", 0);
				TreeNode *pNew = CreateTreeNode(temp);
				vector<TreeNode> pushendLast;
				for (int i = 0; i < CreateTreeStack.size(); i++)
					pushendLast.push_back(CreateTreeStack[i]);
				token temp1("#", 0, -1, "������", 0);
				CreateTreeStack.push_back(*CreateTreeNode(temp1));
				pushendLast.push_back(*CreateTreeNode(temp1));
				pNew = InsertAllChild(pNew, pushendLast);
				GrammarTree->CreateTree(pNew);
				return true;
			}
			signStack.push_back(t);
			CreateTreeStack.push_back(*CreateTreeNode(t));
			Buffer.pop_back();
			break;
		case 3: // > ��Լ    
			int top = signStack.size() - 1;
			top--;
			vector<TreeNode> pushend;     //Ҫ��Լ�Ľ��
			vector<string> pushend1;   //�������Ҳ���ʽ��
			while (true) {
				if (top < 0)
				{
					ErrorMessage = "�޷���ɹ�Լ";
					printBuffer();
					return false;
				}
				int row1 = findend(getSignStackname(signStack[top]));
				int col1 = findend(getSignStackname(signStack[top + 1]));
				int result1 = t_relation[row1][col1];
				if (result1 == 1)//���< ���ջ
				{
					for (int j = signStack.size() - 1; j > top; j--)   //������Լ��
					{
						pushend1.push_back(getSignStackname(signStack[j]));
						signStack.pop_back();
					};
#pragma region �����ڵ�
					//Ѱ�Ҳ���ʽ
					int index = FindGraIndexByvec(pushend1);
					//�ҵ��˲���ʽ,�����Ӧ����
					if (index == -1)
						break;
					token temp(grammar[index].getINP(), 0, -1, "���ս��", 0);
					for (int j = CreateTreeStack.size() - 1; j > returnStackendIndex(top); j--)
					{
						pushend.push_back(CreateTreeStack[j]);
						CreateTreeStack.pop_back();
					}
					TreeNode *pNew = CreateTreeNode(temp);
					pNew = InsertAllChild(pNew, pushend);
					GrammarAction(pNew, pushend, index);
					CreateTreeStack.push_back(*pNew);

#pragma endregion

					break;
				}
				else if (result1 == 2)
				{
					top--;
				}
			}
			break;
		}
	}
}


