#include <iostream>
#include <algorithm>
using namespace std;


/*
分治二分查找
*/

template <class T>
int binarySearch(T *a,int l,int r,const T &v){
    if(r<l){
        return -1;
    }
    int m=(r+l)/2;
    if(v>a[m]){
        return binarySearch(a,m+1,r,v);
    }else if (v<a[m]){
        return binarySearch(a,l,m,v);
    }else{
        return m;
    }
    
}

int main(void){
    int array[10]={3,234,3,44,16,19,11,18,24,15};
    sort(array,array+10);
    cout<<binarySearch(array,0,10,11);
}