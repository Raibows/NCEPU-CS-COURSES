#include<iostream>
using namespace std;
int main()
{
	int n,b,a[100],i,g,t(0);
	cin>>n;
	for(i=0;i<n;i++)
	{cin>>a[i];}
	cin>>b;
	for(i=0;;i++)
	{
		if(b>=a[i]&&b<a[i+1])
		{t=0;break;}
		if(i==n-1)
		{t=0;break;}
		if(b<a[0])
		{t=1;break;}
		
	}
	if(t==0)
	{for(g=n-1;g>=i+1;g--)
	{a[g+1]=a[g];}
    a[i+1]=b;}
	if(t==1)
	{for(g=n-1;g>=i;g--)
	{a[g+1]=a[g];}
	a[0]=b;}
	for(i=0;i<n+1;i++)
	{cout<<a[i]<<" ";}
	cout<<endl;
	return 0;
}
		