#include <iostream>
using namespace std;

#define MaxNum 100 //���ֵ
static int Visited[MaxNum] = {0};
static int visited[MaxNum] = {0};

// �߱����ڵ�
typedef struct node
{
	int adjvex;
	node *next;
} EdgeNode;

//������ڵ�
typedef struct
{
	int vertex;
	EdgeNode *link;
} VertexNode;

typedef VertexNode AdjList[MaxNum];

//����ͼ
static int n, e;
void create(AdjList &ga)
{

	cout << "����ͼ�Ķ������ͱ�����";
	cin >> n >> e;
	for (int i = 1; i <= n; i++)
	{
		ga[i].vertex = i;
		ga[i].link = NULL;
	}
	for (int j = 0; j < e; j++)
	{
		cout << "���붥��ԣ�";
		int vert, adj;
		cin >> vert >> adj;

		EdgeNode *p;
		p = new EdgeNode;

		p->adjvex = adj;
		p->next = ga[vert].link;
		ga[vert].link = p;

		EdgeNode *q;
		q = new EdgeNode;
		q->adjvex = vert;
		q->next = ga[adj].link;
		ga[adj].link = q;
	}
}

void show(AdjList &ga) //չʾͼ
{
	for (int i = 1; i <= n; i++)
	{
		cout << ga[i].vertex << "->";
		EdgeNode *q;
		q = new EdgeNode;
		q = ga[i].link;
		while (q != NULL)
		{
			cout << q->adjvex << "->";
			q = q->next;
		}
		cout << endl;
	}
}

//��ȱ���
void dfs(AdjList &ga, int v0)
{
	Visited[v0] = 1;
	cout << ga[v0].vertex << " ";
	EdgeNode *p;
	p = ga[v0].link;
	while (p != NULL)
	{
		if (Visited[p->adjvex] == 0)
			dfs(ga, p->adjvex);
		p = p->next;
	}
}

// ��ȱ���
void bfs(AdjList &ga, int v0)
{
	int Q[MaxNum]; //��һ����
	visited[v0] = 1;
	cout << ga[v0].vertex << " ";

	int f, r;
	f = r = 0; //��Ϊ��

	EdgeNode *p;
	p = new EdgeNode;
	p = ga[v0].link;

	do
	{
		while (p != NULL)
		{
			int v;
			v = p->adjvex;
			if (visited[v] == 0) //��vδ�����ʣ�v���
			{
				r++;
				Q[r] = v;
				visited[v] = 1;
				cout << ga[v].vertex << " ";
			}
			p = p->next;
		}

		if (f != r) //���Ӳ��գ���ͷ����
		{
			f++;
			p = ga[Q[f]].link;
		}
	} while ((p != NULL) || (f != r));
}

void main()
{
	AdjList ga;
	create(ga);
	show(ga);
	int V;
	cout << "������ȱ�����㣺";
	cin >> V;
	dfs(ga, V);
	cout << endl;
	cout << "�����ȱ�����㣺";
	int v;
	cin >> v;
	bfs(ga, v);
	cout << endl;

	system("pause");
}
