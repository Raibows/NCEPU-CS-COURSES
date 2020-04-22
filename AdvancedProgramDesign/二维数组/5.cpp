#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
int main()
{
	char a[100]={0},b[100]={0};
	int i,n;
	cin>>a;
	n=strlen(a);
	for(i=0;i<n;i++)
	{
		b[i]=a[n-1-i];
	}
	cout<<strcat(a,b)<<endl;
	return 0;
}
