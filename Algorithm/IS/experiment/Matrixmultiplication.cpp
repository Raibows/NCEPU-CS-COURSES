#include<iostream>
using namespace std;

#define NUM 100
int m[NUM][NUM],s[NUM][NUM],p[NUM];
int n;


void MatrixChain(int*p,int n,int m[100][100],int s[100][100]) //s 断开位置
{
	for (int i= 1; i<=n; i++) 
		m[i][i]=0;
	for(int r=2;r<=n;r++)
	{
		for(int i=1;i<=n-r+1;i++)
		{	
			int j=i+r-1;
			m[i][j]= m[i+1][j]+p[i-1]*p[i]*p[j];
			s[i][j] = i;
			for (int k= i+1; k<j; k++) 
			{	
				int t= m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(t<m[i][j]) 
				{
					m[i][j]= t;
					s[i][j]= k;
				}
			}

		}
}//tianbiao
}



void Traceback(int i, int j, int s[100][100])
{
	if(i==j) 
	{
		cout<<"A"<<i ;
	}
	else if(i+1==j)
	{
		cout<<"(A"<<i<<"A"<<j<<")";
	}
	else{
		cout<<"(";
	Traceback(i,s[i][j],s);
	Traceback(s[i][j]+1,j,s);
	cout<<")"; 
	}
}


int main()
{
	cout<<"请输入矩阵连乘的个数n=";
	cin>>n;
	cout<<"请输入第一个矩阵行数和第一个矩阵到第"<<n<<"个矩阵列数：";
	for(int i=0;i<=n;i++)
	{
		cin>>p[i];
	}
	MatrixChain(p,n,m,s);
	cout<<"最优值为："<<m[1][n]<<endl;
	
	cout<<"最优解为："<<endl;
	Traceback(1, n,s);
	cout<<endl;

}









