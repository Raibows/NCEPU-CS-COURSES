#include "tree.h"
#include <iomanip>
#define Grammar_Maxid 13

//判断是否属于ID。
bool typeIsId(string str)
{
	if (str == "标识符" || str == "常数" || str == "整数" || str == "实数")
		return true;
	return false;
}

//终结符结构体
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
	//求集合时判断是否重复存在
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

//得到当前规约串里的非终结符个数
int returnStackendIndex(int top)
{
	int sizeinStack = 0;
	for (int i = 0; i < top;)
	{
		if (CreateTreeStack[sizeinStack].data.type == "非终结符") sizeinStack++;
		else
		{
			i++;
			sizeinStack++;
		}
	}
	if (CreateTreeStack[sizeinStack].data.type == "非终结符") sizeinStack++;
	return sizeinStack;
}

//求出给定id产生式推出的终结符集
void Grammar_FL::InitGrammar_FL(int id)
{
	this->id = id;
	for (int i = 0; i < grammar_length; i++)
	{
		if (grammar[i].getid() == id)
		{

			notEnd = grammar[i].getINP();
			vector<string> vec = split(grammar[i].getOUP(), " ");
			//赋值Fristvt
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
			//赋值Lastvt
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
	void finishGra();    //完成Fristvt & Lastvt
	//void printTable();
	bool Match(vector<token>, string &);
	void printBuffer();
	void printCreateTreeStack();
	void printSignStack();
private:
	Grammar_FL *flgrammar[Grammar_Maxid];
	vector<vecEnd> end;   //终结符集合
	int **t_relation;
	void initEnd();
	bool isexistEnd(vecEnd str)
	{
		for (int i = 0; i < end.size(); i++)
			if (str.end == end[i].end)
				return true;
		return false;
	}
	//根据字符串查询终结符在end的中的索引
	int findend(string str)
	{
		for (int i = 0; i < end.size(); i++)
		{
			if (end[i].end == str)
				return i;
		}
		return -1;
	}
	vector <token> signStack;   //符号栈
	vector <token> Buffer;//输入缓冲区
	//得到token name属性
	string getSignStackname(token t)
	{

		if (typeIsId(t.type))
			return "id";
		return t.name;
	}
	Tree *GrammarTree = NULL;
};

//完成算符优先关系表
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
	//t_relation初始化,0代表无关系,1代表小于<,2代表等于=,3代表大于>
	int size = end.size();
	t_relation = new int *[size];
	for (int i = 0; i < size; i++)
		t_relation[i] = new int[size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			t_relation[i][j] = 0;     //初始化为空白
		//完成1<  ,...aP....  a<Fristvt(P)
	for (int i = 0; i < grammar_length; i++)  //从第一个文法开始
	{
		vector<string> vec = split(grammar[i].getOUP(), " ");
		for (int j = 0; j < vec.size() - 1; j++) //从第一个单词开始判断是否是终结符
		{
			if (isUpper(vec[j]))//是非终结符
			{
				//找到Lasttv(vec[j]) > vec[j+1]
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
					t_relation[row][col] = 3;   //3代表>
				}
			}
			else//终结符
			{
				//判断 isUpper(vec[j+1]),终结符则=，非终结符则 vec[j] < Fristvt(vec[j+1])
				if (isUpper(vec[j + 1])) //第二个是非终结符
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
						t_relation[row][col] = 1;   //1代表<
					}
					//判断第三个是不是终结符
					if (j + 2 < vec.size())
					{
						if (!isUpper(vec[j + 2])) //是终结符
						{
							int row = findend(vec[j]);
							int col = findend(vec[j + 2]);
							t_relation[row][col] = 2;  //加=  形如 aQb
						}
					}
				}
				else //=
				{
					int row = findend(vec[j]);
					int col = findend(vec[j + 1]);
					t_relation[row][col] = 2; //2代表=
				}
			}
		}
		//khkj  等号 = 赋值 如 S-> if B then S else S  if=then=else
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

//构造函数(完成树的建立、表的建立）
Table::Table()
{
	GrammarTree = new Tree();     //建立语法树
	for (int i = 0; i < Grammar_Maxid; i++)
	{
		flgrammar[i] = new Grammar_FL(i);
	}
	finishGra();   //调用函数求出两集合
	initEnd();     //完成算符优先关系表
}


//析构函数
Table::~Table()
{
	//释放空间 flgrammar
	for (int i = 0; i < Grammar_Maxid; i++)
	{
		delete flgrammar[i];
		flgrammar[i] = NULL;
	}

	//释放空间 t_relation
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

//求出firstvt和lastvt集合
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
				//完成Lastvt
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


//输出算符优先表
/*
void Table::printTable()
{
	//输出表头
	cout << "  ";
	for (int i = 0; i < end.size(); i++)
	{
		cout << end[i].end << "  ";
	}
	cout << endl;
	//输出表
	for (int row = 0; row < end.size(); row++)
	{   //输出表列
		cout << end[row].end;
		for (int col = 0; col < end.size(); col++)
		{
			cout << t_relation[row][col] << " ";
		}
		cout << endl;
	}
}
*/

//输出当前输入缓冲区
void Table::printBuffer()
{
	cout << "当前输入缓冲区:  ";
	for (int i = 0; i < Buffer.size(); i++)
		cout << Buffer[i].name;
	cout << endl;
}

//输出
void Table::printCreateTreeStack()
{
	for (int i = 0; i < CreateTreeStack.size(); i++)
		cout << CreateTreeStack[i].data.name;
	cout << endl;
}


//输出当前符号栈
void Table::printSignStack()
{
	cout << "当前符号栈:  ";
	for (int i = 0; i < CreateTreeStack.size(); i++)
		cout << CreateTreeStack[i].data.name;
	cout << endl;
	/*for (int i = 0; i < signStack.size(); i++)
		cout <<  signStack[i].name;
	cout << endl;*/
}


//规约并建立四元式
bool Table::Match(vector<token>tokens, string &ErrorMessage)
{
	ErrorMessage = "";
	token temp("#", 0, -1, "结束符", 0);
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
			ErrorMessage = "非法字符" + t.name;
			printBuffer();
			return false;
		}
		int result = t_relation[row][col];

		switch (result)
		{
		case 0:
			ErrorMessage = t.name + "附近出现错误";
			printBuffer();
			return false;
			break;
		case 1: // < 移进
			signStack.push_back(t);
			CreateTreeStack.push_back(*CreateTreeNode(t));
			Buffer.pop_back();
			break;
		case 2: // =  移进
			//判断是否为 #
			if (t.name == "#") {
				//建立树
				token temp("W", 0, -1, "非终结符", 0);
				TreeNode *pNew = CreateTreeNode(temp);
				vector<TreeNode> pushendLast;
				for (int i = 0; i < CreateTreeStack.size(); i++)
					pushendLast.push_back(CreateTreeStack[i]);
				token temp1("#", 0, -1, "结束符", 0);
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
		case 3: // > 规约    
			int top = signStack.size() - 1;
			top--;
			vector<TreeNode> pushend;     //要规约的结点
			vector<string> pushend1;   //用来查找产生式用
			while (true) {
				if (top < 0)
				{
					ErrorMessage = "无法完成规约";
					printBuffer();
					return false;
				}
				int row1 = findend(getSignStackname(signStack[top]));
				int col1 = findend(getSignStackname(signStack[top + 1]));
				int result1 = t_relation[row1][col1];
				if (result1 == 1)//如果< 则出栈
				{
					for (int j = signStack.size() - 1; j > top; j--)   //弹出规约串
					{
						pushend1.push_back(getSignStackname(signStack[j]));
						signStack.pop_back();
					};
#pragma region 建立节点
					//寻找产生式
					int index = FindGraIndexByvec(pushend1);
					//找到了产生式,完成相应动作
					if (index == -1)
						break;
					token temp(grammar[index].getINP(), 0, -1, "非终结符", 0);
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


