#include <iostream>
using namespace std;
int main()
{
	int n,sum(0),b;
	cin>>n;
	if(n<=2)
	{  b=n;
		cout<<b<<endl;}
	if(n>2)
	{int *k=new int[n];
	k[1]=1;k[0]=1;
	 for(int i=2;i<n;i++)
	 {
		 k[i]=k[i-2]+k[i-1];}
	 for(int a=0;a<n;a++)
	 {sum+=k[a];}
	 cout<<sum<<endl;
	}
	return 0;
}


