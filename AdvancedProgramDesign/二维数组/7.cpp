#include <iostream>
#include <cstring>
using namespace std;
int main()
{
	char a[100]={0};
	int i,n,b=0,c=0,d=0;
	cin>>a;
	n=strlen(a);
	for(i=0;i<n;i++)
	{
		if(a[i]>='0'&&a[i]<='9')
		{c++;}
		else if((a[i]>='A'&&a[i]<='Z')||(a[i]>='a'&&a[i]<='z'))
		{b++;}
		else
		{d++;}
	}
	cout<<b<<" "<<c<<" "<<d<<" "<<endl;
	return 0;
}
