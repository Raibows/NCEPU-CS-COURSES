 #include<iostream>
using namespace std;
int main()
{
	int a[100],b[100],c[100],n,i,j,x,y,z=0;
	cin>>n;
	for(i=0;i<n;i++)
		cin>>a[i];
	if(i==1)
		cout<<a[0]<<" 1";
	else
	{
		for(i=0;i<n;i++)
			for(j=0;j<(n-1);j++)
				if(a[j]>a[j+1])
				{
					x=a[j];
					a[j]=a[j+1];
					a[j+1]=x;
				}
		for(i=0;i<(n-1);i++)
		{
			y=1;
			for(;a[i]==a[i+1];i++)
				y++;  
			b[z]=y;
			c[z]=a[i];
			z++;
		}
		for(i=0;i<z;i++)
			for(j=1;j<z;j++)
				if(b[j-1]<b[j])
				{
					x=b[j];
					b[j]=b[j-1];
					b[j-1]=x;
					x=c[j];
					c[j]=c[j-1];
					c[j-1]=x;
				}
		i=0;
		do{
			cout<<c[i]<<" "<<b[i]<<endl;
			i++;
		}while(b[i]==b[i-1]);
	}
	return 0;
}

