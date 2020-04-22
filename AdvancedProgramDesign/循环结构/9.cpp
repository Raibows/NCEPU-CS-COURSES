#include <iostream>
using namespace std;
int main()
{
	int n,a=0,c=0,b=1;
	cin>>n;
	if(n>0)
	{for(int i=1;i<=n;i++)
	{a=100000*i;
	c+=b;
	b=b*2;
	}}
	else
	{a=0;c=0;}
	cout<<a<<endl<<c<<endl;
	return 0;
}