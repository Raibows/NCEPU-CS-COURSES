#include<iostream>
using namespace std;
int main()
{
	int n,a[100],i,g,q(0),w(0),t,z=0;
	int b[100];
	cin>>n;
	for(i=0;i<n;i++)
	{cin>>a[i];}
	for(i=0;i<n;i++)
	{
		z=0;
		if(a[i]<2)
			continue;
		for(g=2;g<a[i];g++)
		{
			if(a[i]%g==0)
			{
				z=1;
				break;
			}
		}
		if(z==1)
			continue;
		b[q]=a[i];
		q++;
	}
    for(g=0;g<q;g++)
	{
		for(w=g;w<q;w++)
		{
			if(b[g]<b[w])
			{
				t=b[g];
			    b[g]=b[w];
			    b[w]=t;
			}
		}
	}
	g=0;
	for(i=0;i<q;i++)
	{g+=b[i];}
	cout<<g<<endl;
	for(i=0;i<q;i++)
	{cout<<b[i]<<" ";}
	cout<<endl;
return 0;
}

	