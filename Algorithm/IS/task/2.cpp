#include<iostream>
using namespace std;
typedef long long ll;
int main()
{
    ll a,b,c;
    ll k;
    a=b=c=1;
    for(int i=4;i<=20190324;i++)
    {
        k=((a+b)%10000+c)%10000;
        a=b;
        b=c;
        c=k;
    }
    cout<<k<<endl;

}
