#include <iostream>
using namespace std;
int main()
{
	float a=1,i=2,c;
	float b,sum=0;
	cin>>c;
	while(sum<=c)
	{b=i/a;
	a++;
	i++;
	sum+=b;}
	cout<<sum<<endl;
	return 0;
}