#include <iostream>
using namespace std;

// 快速排序中的分区算法
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
void Quicksort(T *a, int l, int r){
    if(r<=l){
        return;
    }
    int m = partition(a, l, r);
    Quicksort(a, l, m-1);
    Quicksort(a, m+1, r);
}