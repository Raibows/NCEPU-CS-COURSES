#include<bits/stdc++.h>
using namespace std;
int a[1111111];
int b,c,d;
int s[111];//代表第i包糖果
int main()
{
    memset(a,-1,sizeof(a));
    cin>>b>>c>>d;
    for(int i=0;i<b;i++)
    {
        int ss=0;
        int t;
        for(int j=0;j<k;j++)
        {
            scanf("%d",&t);
            ss|=(1<<(t-1));
        }
        s[i]=ss;
        a[ss]=1;
    }
 
    for(int i=0;i<b;i++)
    {
        for(int j=0;j<(1<<c);j++)
        {
            if(a[j]==-1)
				continue;
            if(a[j|s[i]]==-1)
				a[j|s[i]]=a[j]+a[s[i]];
            else 
				a[j|s[i]]=min(a[j|s[i]],a[j]+a[s[i]]);
        }
    }
    cout<<a[(1<<m)-1];
    return 0;
}

