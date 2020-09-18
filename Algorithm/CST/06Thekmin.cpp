#include <iostream>
using namespace std;

template <typename T>
int partition(T *a, int p, int q){
    T x = a[p];
    int i = p;
    for(int j=p+1;j<=q;j++){
        if(!(x < a[j])){
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[p], a[i]);
    return i;
}

template <typename T>
T kthElement(T *a, int l, int r, int k){
    if(r <= l){
        return a[l];
    }
    int m = partition<T>(a, l, r);
    int kk = m-l+1;
    if(k == kk){
        return a[m];
    }else if(k<kk){
        return kthElement(a, l, m-1, k);
    }else
    {
        return kthElement(a, m+1, r, k-kk);
    }
}

int main(void){
    int test[10] = {2,3,4,1,7,5,6,10,9,8};
    int k = 0;
    while (1)
    {
        cin>>k;
        cout << kthElement<int>(test, 0, 9, k)<<endl;
    }
    
    
}