#include <iostream>
using namespace std;
int main()
{
	int n,a(1),b(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{a=i;
	for(int k=i+1;k<n;k++)
	{a=a+k;
	if(a>n)
	{break;}
	if(a==n)
	{for(int g=i;g<=k;g++)
	{cout<<g<<" ";
	b=1;}
	cout<<endl;}}}
if(b==0)
{cout<<"none"<<endl;}
return 0;}
	
