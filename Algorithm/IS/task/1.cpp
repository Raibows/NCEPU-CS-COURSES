#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef long long ll;
int main() {
	int a,b,c,d,e,f,g,h,l;
	int i,k,m,n;
	ll sum=0;
	for(i=1;i<=9;i++)
	{
		if(i==1||i==2||i==0||i==9)
		{
			sum+=i*i;
		}
	}
	
	
	for(k=10;k<=99;k++)
	{
		a=k%10;
		b=k/10;
		if(a==1||a==2||a==0||a==9||b==1||b==2||b==0||b==9)
		{
			sum+=k*k;
		}
	}
	
	
	for(m=100;m<=999;m++)
	{
		c=m%10;	//978-8 
		d=(m/10)%10;//7
		e=m/100;//9
		if(c==1||c==2||c==0||c==9||d==1||d==2||d==0||d==9||e==1||e==2||e==0||e==9)
		{
			sum+=m*m;
		}
	}

	
	
	for(n=1000;n<=2019;n++)
	{
		f=n%10;
		g=(n/1000)%10;
		h=(n/100)%10;
		l=(n/10)%10;	
		if(f==1||f==2||f==0||f==9||g==1||g==2||g==0||g==9||h==1||h==2||h==0||h==9||l==1||l==2||l==0||l==9)
		{
			sum+=n*n;
		}
	}

	cout<<sum<<endl;
	return 0;
}
