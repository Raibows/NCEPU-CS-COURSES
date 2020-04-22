#include <iostream>
using namespace std;
int dignit(int n,int k)
{
	int i=0;int a=0,t=0;
	while(n>0)
	{
		a++;
		i=n%10;
		n=n/10;
		if(a==k)
		{t=1;break;}
	}
	if(t==0)
    {i=0;}
    return i;
}
int main()
{
	int a,b;
	cin>>a>>b;
	cout<<dignit(a,b)<<endl;
	return 0;
}
		
		

