#include <iostream>
using namespace std;
int main()
{
	int a,b,c(0);
	cin>>a>>b;
	int *k=new int[a];
	int *p=new int[b]; 
	for(int i=0;i<a;i++)
	cin>>k[i];
	for(int q=0;q<b;q++)
	cin>>p[q];
	for(int h=0;h<a;h++)
	{
		for(int y=0;y<b;y++)
		{if(k[h]==p[y])
		{cout<<k[h]<<" ";c++;}}}
			
   if(c==0)
   cout<<"no"<<endl;
   else
   {cout<<endl;}
   return 0;
}
