#include <iostream>
using namespace std;
int main()
{
	int n,i=1,j,k,m;
	int a[100][100];
	cin>>n;
	m=2*n-1;
	for(i;i<=n;i++)
	{
		for(k=i-1;k<m;k++)
		{
			for(j=i-1;j<m;j++)
			{
				a[k][j]=i;
			}
		}
		m--;
	}
	for(k=0;k<2*n-1;k++)
	{
		for(j=0;j<2*n-1;j++)
		{
			cout<<a[k][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	return 0;
}
	

