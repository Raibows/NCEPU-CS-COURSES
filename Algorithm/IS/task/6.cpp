#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[100005];
int n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    int level=1;//����
    ll MAX=a[1];
    ll ans=1;//��һ��
    int num=1;//�ò�Ľڵ���
    int pos=2;//��һ�㿪ͷָ��λ��
    for(;;)
    {
        level++;
        num*=2;
        ll sum=0;
        for(int j=pos;j<=min(pos+num-1,n);j++)sum+=a[j];
        if(sum>MAX)
        {
            ans=level;
            MAX=sum;
        }
        pos=pos+num;
        if(pos>n)break;
    }
    printf("%lld\n",ans);
    return 0;
}

