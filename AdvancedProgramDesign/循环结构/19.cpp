#include <iostream>
using namespace std;
int main()
{
	int a,b,c,d;
	cin>>a>>b;
	for(int i=2;i<=a;i++)
	{d=b%i;
	c=a%i;
	for(;c==0&&d==0;)
	{a=a/i;
	b=b/i;
	d=b%i;
	c=a%i;}}
	cout<<a<<" "<<b<<endl;
	return 0;
}
