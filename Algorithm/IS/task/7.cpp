
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
static const int maxn = 100010;
static const int INF = 0x3f3f3f3f;
static const int mod = (int)1e9 + 7;
static const double eps = 1e-6;
static const double pi = acos(-1);
 
void redirect(){
    #ifdef LOCAL
        freopen("test.txt","r",stdin);
    #endif
}
 
struct node{
    int t,x;    
}p[maxn];
 
bool operator <(const node& a,const node& b){
    return a.t < b.t;
}
 
int last[maxn];
int val[maxn];
bool live[maxn];
 
int main(){
    redirect();
    int n,m,T,cnt = 0;
    scanf("%d %d %d",&n,&m,&T);
    for(int i = 1;i <= m;i++)scanf("%d %d",&p[i].t,&p[i].x);
    sort(p+1,p+1+m);
    for(int i = 1;i <= m;i++){
        int &t = p[i].t,&x = p[i].x;
        val[x] = max(0,val[x]-max(0,t-last[x]-1)) + 2;
        last[x] = t;
        if(val[x] > 5)live[x] = true;
        else if(val[x] <= 3)live[x] = false;
    }
    for(int i = 1;i <= n;i++){
        val[i] -= T-last[i];
        if(val[i] <= 3)live[i] = false;
        if(live[i])cnt++;
    }
    printf("%d\n",cnt);
    return 0;
}
