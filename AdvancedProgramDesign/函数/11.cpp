#include <iostream>
using namespace std;
int hanshu(int k[],int n)
{
	int i,q,t,a=0;
	for(i=0;i<n;i++)
	{
		for(q=i;q<n;q++)
		{
			if(k[i]>k[q])
			{
				t=k[i];
				k[i]=k[q];
				k[q]=t;
			}
		}
	}
	for(i=0;i<n;i++)
	{  
	    t=0;
		for(q=2;q<k[i];q++)
		{
			if(k[i]%q==0)
			{t=1;break;}
		}
		if(t==1||k[i]<2)
		{continue;}
		k[a]=k[i];
		a++;
	}
	return a;
}
int main()
{
	int k[100],n,i,b;
	cin>>n;
	for(i=0;i<n;i++)
	cin>>k[i];
	b=hanshu(k,n);
    for(i=0;i<b;i++)
    {
       cout<<k[i]<<" ";
    }
    cout<<endl;
}
	
	
 
