#include <iostream>
using namespace std;
int main()
{
	int m,n,su=0,sm=0,sum=0,i,j;
	int a[10][10];
	cin>>m>>n;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			cin>>a[i][j];
		}
	}
    for(i=0;i<m;i++)
	{   su=0;
		for(j=0;j<n;j++)
		{
			su+=a[i][j];;
		}
		cout<<su<<" ";
	}
	cout<<endl;
	 for(j=0;j<n;j++)
	{   sm=0;
		for(i=0;i<m;i++)
		{
			sm+=a[i][j];;
		}
		cout<<sm<<" ";
	}
	cout<<endl;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			sum+=a[i][j];
		}
	}
	cout<<sum<<endl;
	return 0;
}
