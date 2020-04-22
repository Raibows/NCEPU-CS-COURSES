#include <iostream>
#include <math.h>
using namespace std;
int main ()
{
	float e,sum=0,a,b,c;
	int i;
	cin>>e;
	for(i=1;;i++)
	{a=(4*i-3)*pow(-1,i+1);
		b=fabs(a);
		c=1/a;
		if((1/b)<=e)
		{break;}
		sum+=c;
	}
	cout<<sum<<endl;
	return 0;
}
		

