#include <iostream>
using namespace std;
int main()
{int a,b,e,o,p;
cin>>a;
b=a;e=a;

for(o=0;e>0;o++)
{e=e/10;
p=o+1;}
int k[p];
for(int i=0;i<p;i++)
{b=a%10;
a=a/10;
k[i]=b;}
int max;
max=k[0];
for(int c=0;c<p;c++)
{if(max<k[c])
max=k[c];}
cout<<max<<endl;
return 0;
}


