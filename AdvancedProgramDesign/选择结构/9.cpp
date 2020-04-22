#include <iostream>
using namespace std;
int main()
{
	int a,b,c,d;
	cin>>a;
	b=a%10;
	c=a/10%10;
	d=a/100;
	if(a<100||a>999)
	{cout<<"-1"<<"\n";}
	else
	{a=b*100+c*10+d;
	cout<<a<<endl;}
	return 0;
}
