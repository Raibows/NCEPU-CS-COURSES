#include<iostream>
#include<cmath>
using namespace std;
float hanshu(float a)
{float b=0;
	if(a<=0)
		b=sin(a)+1;
	if(a>0&&a<10)
		b=a*a+3/a;
	if(a>=10)
		b=pow(a+4,0.5);
	return b;
}
int main()
{   float a;
	cin>>a;
	cout<<hanshu(a)<<endl;
	return 0;
}
