#include<iostream>
using namespace std;
int visited[100]={0};
int Visited[100]={0};
typedef struct Edge
{
	int loc;
	struct Edge *next;
}*point;

typedef struct VNode
{
	int vertex;
	struct Edge *link;
}*Node;
struct VNode a[10];

static int n,e;


void create(struct VNode a[])
{
	
	cout<<"����ͼ�Ķ������ͱ�����";
	cin>>n>>e;
	for(int i=1;i<=n;i++)//��ʼ���ڽӱ�
	{
		a[i].vertex=i;
		a[i].link=NULL;

	}
	for(int j=0;j<e;j++)
	{
		cout<<"���붥��ԣ�";//�������Һ��� 
		char c,b;
		cin>>c>>b;
		int vert=c-64;
		int adj=b-64;
		point p;
		p=new Edge;
		p->loc=adj;
		p->next=a[vert].link;
		a[vert].link=p;


	}
}



 void dfs(struct VNode a[], int V0)
{
	point p;
	if (visited[V0] == 0)
	{

		cout << char(V0+64) << endl;
		visited[V0] = 1;
	}//����������������
	p = a[V0].link;
	while (p != NULL)
	{
		if (visited[p->loc] == 0)
		{
			dfs(a, p->loc);
		}
		p = p->next;//p���봫��
	}
}

 void bfs(struct VNode a[], int V0)
{
	int Q[100];
	if (Visited[V0] == 0)
	{
		cout << char(V0+64) << endl;
		Visited[V0] = 1;
	}//����������������
	int f = 0, r = 0;
	point p = new Edge;
	p = a[V0].link;
	do {
		while (p != NULL)
		{
			if (Visited[p->loc] == 0)
			{
				r++;
				Q[r] = p->loc;
				cout <<char(p->loc+64) << endl;
				Visited[p->loc] = 1;
			}
			p = p->next;
		}
		if (f != r)
		{
			f++;
			p = a[Q[f]].link;
		}
	} while ((p != NULL) || (f != r));
}

void show(struct VNode a[])
{
		for(int i=1;i<=n;i++){
		cout<<char(a[i].vertex+64)<<"->";
		point q;
		q = new Edge;
		q=a[i].link;
		while(q!=NULL){
			cout<<char(q->loc+64)<<"->";
			q=q->next;
		}
		cout<<endl;
	}
}


int main()
{
	create(a);
	 show(a);
	for (int i = 1; i <= n; i++)
	{
		visited[i] = 0;
	}
	cout << "����ȱ���" << endl;
	for (int j = 1; j <= n; j++)//����������������
	{
		dfs(a, j);
	}
	for (int k = 1; k <= n; k++)
	{
		Visited[k] = 0;
	}
	cout << "����ȱ���" << endl;
	for (int l = 1; l <= n; l++)//����������������
	{
		bfs(a, l);
	}
	return 0;
}

