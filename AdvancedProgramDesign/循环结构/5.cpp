#include <iostream>
using namespace std;
int main()
{
	int a=0,n=0,sum=0,c;
	cin>>a>>n;
	c=a;
	for(int i=0;i<n;i++)
	{
		sum+=a;
		a=(a*10+c);}
	cout<<sum<<endl;
	return 0;
}
