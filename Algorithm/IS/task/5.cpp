#include<bits/stdc++.h>
using namespace std;
typedef long long qq;
qq fast_mul(qq x, qq y, qq p){
    qq ret=0;
    x%=p, y%=p;
    while(y>0){
        if(y&1){
            ret= (ret+x)%p;
        }
        y>>=1;
        x= (x+x)%p;
    }
    return ret;
}
qq fast_pow(qq x, qq k, qq p){
    qq ret=1;
    x%=p;
    while(k>0){
        if(k&1){
            ret= fast_mul(ret, x, p);
        }
        k>>=1;
        x= fast_mul(x, x, p);
    }
    return ret;
}
qq phi(qq n){
    qq ret= n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            ret= ret/i*(i-1);
            while(n%i==0) n/=i;
        }
    }
    if(n!=1){
        ret= ret/n*(n-1);
    }
    return ret;
}
qq get_p(qq n){
    for(qq i=2;i<=n;i++){
        if(n%i==0){
            return i;
        }
    }
}
int main(){
    qq n = (qq)1001733993063167141;
    qq d = 212353;
    qq C = 20190324;
    qq p,q,e,k;
    printf("n=%lld\n",n);
    p=get_p(n);
    q=n/p;
    printf("p=%lld, q=%lld\n",p,q);
    k=(p-1)*(q-1);
    printf("k=(p-1)*(q-1)=%lld\n",k);
    printf("phi(k)=%lld\n",phi(k));
    e=fast_pow(d,phi(k)-1,k);
    printf("e=d^(phi(k)-1)=%lld (mod k)\n",e);
    printf("d*e=%lld (mod k)\n",fast_mul(d,e,k));
    qq X=fast_pow(C,e,n);
    printf("X=C^e (mod n)= %lld\n",X);
    while(1)getchar();
    return 0;
}

