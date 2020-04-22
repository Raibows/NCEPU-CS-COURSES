#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
int main()
{
	int a[100][100]={0},max,min,i,k,m,n;
	cin>>m>>n;
	for(i=0;i<m;i++)
	{
		for(k=0;k<n;k++)
		{
			cin>>a[i][k];
		}
	}
	
	for(i=0;i<m;i++)
	{
		max=a[i][0];
		for(k=0;k<n;k++)
		{
			if(max<a[i][k])
			{max=a[i][k];}
		}
		cout<<max<<" ";
	}
	cout<<endl;
	for(i=0;i<n;i++)
	{
		min=a[0][i];
		for(k=0;k<m;k++)
		{
			if(min>a[k][i])
			{min=a[k][i];}
		}
		cout<<min<<" ";
	}
	cout<<endl;
		
	
	return 0;
}
