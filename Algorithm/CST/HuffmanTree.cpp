#include <iostream>
#include<algorithm>
#include<fstream>
#include<queue>
#include<functional>
#include<string>
#include<vector>
#include <sstream>

using namespace std;
struct TN
{
	char c;
	int f;
	int idx;//线性表中位置索引标号
	int p;//父亲线性表中的标号
	int l, r;//左右节点的索引号
	TN() :p(-1), l(-1), r(-1) {}
};
struct CN
{
	char c;//字符
	int num;//个数
	int len;//编码长度
	CN() :num(0), len(0) {}
};
class CHuffman//读取此种格式文件类
{
public:
	CHuffman();
	~CHuffman();
	CHuffman(char *c); //用文件中作为构造函数的参数
	void CreateTree();//生成编码树
	void OutputTree();//打印编码树
	void OutputCode();//打印编码
	void XCode();//Huffman编码
				 //void DeCode(int b[], int m);
	void INCH() { h_c = new CN[260]; h_n = h_sum = 0; }//初始化
	int printCode(TN node);//打印某个字符的编码
	void yasuolv();
private:
	TN *h_t;//线性表
	int h_n;//字符个数
	int h_sum;//字符总数
	CN *h_c;//统计字符数及其个数
};
CHuffman::CHuffman() {}
CHuffman::~CHuffman()
{
	delete[]h_t;
	delete[]h_c;
}
bool operator>(const TN &x, const TN &y) { return x.f > y.f; }
void CHuffman::XCode()
{
	h_t = new TN[2 * h_n];
	for (int i = 0; i < h_n; i++)
	{
		h_t[i].c = h_c[i + 1].c;
		h_t[i].f = h_c[i + 1].num;
		h_t[i].idx = i;
		//读入c,f,idx
	}
	std::priority_queue<TN, std::vector<TN>, std::greater<TN> >PQ;
	for (int i = 0; i < h_n; i++)
	{
		PQ.push(h_t[i]);
	}
	int next = h_n;//下一个要生成的节点
	while (!PQ.empty())
	{
		TN l = PQ.top();
		PQ.pop();
		TN r = PQ.top();
		PQ.pop();
		TN p;
		p.l = l.idx; p.r = r.idx;
		p.f = l.f + r.f;
		p.idx = next;
		h_t[next] = p;
		h_t[l.idx].p = h_t[r.idx].p = next;
		PQ.push(p);
		next++;
		if (next == 2 * h_n - 1) { break; }
	}
}
int CHuffman::printCode(TN node)
{
	cout << "(" << node.c << ":";
	std::vector<int> v;
	while (node.p != -1)
	{
		if (node.idx == h_t[node.p].l)
		{
			v.push_back(0);
		}
		else
		{
			v.push_back(1);
		}
		node = h_t[node.p];
	}
	int cc = v.size();
	for (int k = v.size() - 1; k >= 0; k--)
	{
		cout << v[k];
	}
	cout << ") ";
	return cc;
}
CHuffman::CHuffman(char *c)
{
	INCH();
	int n(0);//已有标志；有为1，无为0
	
	 ifstream fin("c:/users/raibows/desktop/test.txt", ios::in);
	if (!fin)
	{
		cout << "File open error!\n";
		return;
	}
	char ch;
	while ((ch = fin.get()) != EOF)
	{
		//cout << ch;
		h_sum++;
		for (int i = 1; i <= h_n; i++)
		{
			if (h_c[i].c == ch)
			{
				h_c[i].num++;
				n = 1;
				i = h_n + 1;
			}
		}
		if (n == 0)
		{
			h_n++;
			h_c[h_n].c = ch;
			h_c[h_n].num++;
		}
		else
		{
			n = 0;
		}

	}
	//cout << endl;
	cout << "num of types" << h_n << endl;
	cout << "chars in all" << h_sum << endl;
	cout << "(char,frequency):" << endl;
	int j = 0;
	for (int i = 1; i <= h_n; i++)
	{
		j++;
		cout << " (" << h_c[i].c << "," << h_c[i].num << ")";
		if (j == 10) { cout << endl; j = 0; }
	}
	cout << endl;
	fin.close();
}
void CHuffman::OutputCode()
{
	int j = 0;
	for (int i = 0; i < h_n; i++)
	{
		j++;
		h_c[i + 1].len = printCode(h_t[i]);
		if (j == 10) { cout << endl; j = 0; }
	}
	cout << endl;
}
void CHuffman::yasuolv()
{
	float lv(0);
	int le(0), lu(0), ll = h_n;
	for (int i = 1; i <= h_n; i++)
	{
		lv = lv + float(h_c[i].num)*h_c[i].len / h_sum;
	}
	while (ll > 1)
	{
		ll = ll / 2;
		lu = lu + ll % 2;
		le++;
	}
	if (lu != 1) { le++; }
	cout << "Huffman code average length is:" << lv << endl;
	cout << "normal code length is" << le << endl;
	lv = lv / le;
	cout << "compression ratio is:" << 1 - lv << endl;
}
int main(void)
{
	char c[] = "shiyan.docx";
	CHuffman  hm(c);
	hm.XCode();
	cout << endl;
	cout << "Huffman code are below" << endl;
	hm.OutputCode();
	cout << endl;
	cout << "compression ratio is" << endl;
	hm.yasuolv();
}