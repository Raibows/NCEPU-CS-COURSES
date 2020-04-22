#include <iostream>
using namespace std;
int main()
{
	int a,b(0),c=0,j;
	cin>>a;
	int *k=new int[a];
	int *p=new int[a];
	for(int i=0;i<a;i++)
	{cin>>k[i];}
	for(int f=0;f<a;f++)
	{
		for(int g=0;g<a;g++)
		{
			if(k[f]==k[g])
			{b=b+1;}
			p[f]=b;
		}
		b=0;}
	for(int h=0;h<a;h++)
	{
		for(c=0;c<h;c++)
		{if(k[h]==k[c])
		{goto loop;}}
        for(j=0;j<a;j++)
		{
			if(p[h]<p[j])
			{goto loop;}
		}
	cout<<k[h]<<" "<<p[h]<<endl;
loop:;
	}
	

return 0;
}


