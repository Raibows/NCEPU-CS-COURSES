#include <iostream>
#include <cstring>
using namespace std;
int main()
{
	char a[100];
	char c;
	int i=0,n,t=0;
	cin>>a>>c;
	n=strlen(a);
	for(i=0;i<n;i++)
	{
		if(a[i]==c)
		{
			t=1;
			break;
		}
	}
	if(t==1)
	{
		cout<<i<<endl;
	}
	else
	{
		cout<<"no"<<endl;
	}
    return 0;
}

