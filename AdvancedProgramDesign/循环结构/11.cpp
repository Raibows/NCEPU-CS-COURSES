#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	double n,x,s(1),d,h(1);
	cin>>n>>x;
	for(int i=1;i<=n;i++)
	{
		h=1;
		for(d=1;d<=i;d++)
		{h=h*d;}
		s+=(pow(-1,1+i)*pow(x,i)/h);
	}
	cout<<s<<'\n';
	return 0;
}
