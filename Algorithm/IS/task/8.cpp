
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int bit[2000050];
int  n=1000001;
int sum(int i)
{
    int s=0;
    while(i>0)
    {
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(int i,int x)
{
    while(i<=n)
    {
        bit[i]+=x;
        i+=i&-i;
    }
}
bool ok(int k,int pre)
{
    int l=k-pre+1;
    int cnt=sum(k)-sum(pre-1);
    return cnt<l;
}
bool vis[1000005];
int ans[100005];
int N;
int a[100005];
int main()
{
    scanf("%d",&N);
    for(int i=0;i<N;i++)scanf("%d",&a[i]);
    for(int i=0;i<N;i++)
    {
        if(!vis[a[i]])
        {
            ans[i]=a[i];
            vis[a[i]]=1;
            add(a[i],1);
        }
        else {
            int l=a[i];int r=1000002;
            int mid;
            while(r-l>1)
            {
                mid=(l+r)/2;
                if(ok(mid,a[i]))r=mid;
                else l=mid;
            }
            ans[i]=r;
            vis[r]=1;
            add(r,1);
        }
    }
    for(int i=0;i<N;i++)printf("%d%c",ans[i],i==N-1?'\n':' ');
    return 0;
}

