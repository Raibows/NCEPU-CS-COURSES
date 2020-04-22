#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
int main()
{
	char a[100]={0},b[100]={0};
	int i,c=0;
	cin>>a>>b;
	for(i=0;a[i]!=0||b[i]!=0;i++)
	{
		if(a[i]!=b[i])
		{c=fabs(int(a[i]-b[i]));break;}
	}
	cout<<c<<endl;
	return 0;
}

