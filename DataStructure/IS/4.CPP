#include<iostream>
using namespace std;

#define MaxNum 100  //最大值
static int Visited[MaxNum] = { 0 };
static int visited[MaxNum] = { 0 };

// 边表表节点
typedef struct node  
{
	int adjvex;
	node* next;
}EdgeNode;

//顶点表节点
typedef struct 
{
	int vertex;
	EdgeNode *link;
}VertexNode;

typedef VertexNode AdjList[MaxNum];

//建立图
static int n, e;
void create(AdjList &ga)
{

	cout << "输入图的顶点数和边数：";
	cin >> n >> e;
	for (int i = 1; i<=n; i++)
	{
		ga[i].vertex	= i;
		ga[i].link		= NULL;

	}
	for (int j = 0; j<e; j++)
	{
		cout << "输入顶点对：";
		int vert, adj;
		cin >> vert >> adj;

		EdgeNode *p;
		p = new EdgeNode;

		p->adjvex = adj;
		p->next = ga[vert].link;
		ga[vert].link=p;

		EdgeNode *q;
		q = new EdgeNode;
		q->adjvex = vert;
		q->next = ga[adj].link;
		ga[adj].link=q;

	}
}

void show(AdjList &ga)//展示图
{
	for (int i =1; i<=n; i++) {
		cout << ga[i].vertex << "->";
		EdgeNode *q;
		q = new EdgeNode;
		q = ga[i].link;
		while (q != NULL) {
			cout << q->adjvex << "->";
			q = q->next;
		}
		cout << endl;
	}
}

//深度遍历
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

// 广度遍历
void bfs(AdjList &ga, int v0)
{
	int Q[MaxNum];//建一个队
	visited[v0] = 1;
	cout << ga[v0].vertex << " ";

	int f, r;
	f = r = 0;//队为空

	EdgeNode *p;
	p = new EdgeNode;
	p = ga[v0].link;

	do
	{
		while (p != NULL)
		{
			int v;
			v = p->adjvex;
			if (visited[v] == 0)//若v未被访问，v入队
			{
				r++;
				Q[r] = v;
				visited[v] = 1;
				cout << ga[v].vertex << " ";
			}
			p = p->next;
		}

		if (f != r)//若队不空，对头出队
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
	cout << "输入深度遍历起点：";
	cin >> V;
	dfs(ga, V);
	cout << endl;
	cout << "输入广度遍历起点：";
	int v;
	cin >> v;
	bfs(ga, v);
	cout << endl;

	system("pause");
}
