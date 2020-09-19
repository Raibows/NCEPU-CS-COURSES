#include <iostream>

using namespace std;

//找第k大元素




template <class T>
int partition(T *a, int p, int q){
    T x = a[p];
    int i = p; //record the location of partition
    for(int j=p+1; j<=q; j++){
        if(!(x<a[j])){
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[p], a[i]);
    return i;
}









template <class T>
T kthElement(T *a, int l, int r, int k){
    if(r<=l){
        return a[l];
    }
    int m = partition(a, l, r);
    int kk = m - 1 + l;
    if((k-1) == kk){
        return a[m];
    }else if (k<kk)
    {
        return kthElement(a, l, m-1, k);
    }else
    {
        return kthElement(a, m+1, r, k-kk);
    }
    
    
}


int main(void){
    int a[7] = {2, 3, 4, 1, 9, 0, -10};
    cout<< kthElement<int>(a, 0, 7, 2);
}