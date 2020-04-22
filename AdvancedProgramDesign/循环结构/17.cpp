#include <iostream>
using namespace std;
int main()
{
	int n,a(1),b,s(0),c;
	cin>>n;
	c=n;
    for(int i=1;c>0;i++)
    {b=c%10;
	for(int k=1;k<=b;k++)
    {a=a*k;}
    s=s+a;
    c=c/10;
	a=1;}
    cout<<s<<endl;
    if(n==s)
    {cout<<"yes"<<endl;}
    else
    {cout<<"no"<<endl;}
    return 0;
}
	
    
 
