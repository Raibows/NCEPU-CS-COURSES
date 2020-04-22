#include <iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int *k=new int[n];
    int *p=new int[n];
	for(int i=0;i<n;i++)
	{cin>>k[i];}
	for(int g=0;g<n;g++)
	{p[g]=k[n-g-1];}
	for(int b=0;b<n;b++)
	{cout<<p[b]<<" ";}
	cout<<endl;
	return 0;
}
