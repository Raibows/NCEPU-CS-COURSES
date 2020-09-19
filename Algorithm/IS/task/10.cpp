#include<bits/stdc++.h>
using namespace std;
#define modk(x) (((x)>=k)?((x)-k):(x))
const int maxn = 2005;
int c[maxn][maxn], n, m, k, T;
void init(){
    ///预处理C(i,j)
    c[0][0]=1;
    for(int i=1;i<maxn;i++){
        c[i][0]=1%k;
        for(int j=1;j<=i;j++){
            c[i][j]=modk(c[i-1][j]+c[i-1][j-1]);
        }
    }
    ///处理C(i,j)是否为k 的倍数
    for(int i=0;i<maxn;i++){
        for(int j=0;j<=i;j++){
            if(c[i][j]==0) c[i][j]=1;
            else c[i][j]=0;
        }
    }
    ///将二维数组C处理成区域前缀和
    for(int i=1;i<maxn;i++){
        int s=0;
        for(int j=0;j<maxn;j++){
            s+=c[i][j];
            c[i][j]=c[i-1][j]+s;
        }
    }
}
int main(){
    scanf("%d%d",&T,&k);
    init();
    while(T--){
        scanf("%d%d",&n,&m);
        printf("%d\n",c[n][m]);
    }
    return 0;
    system("pause");
}

