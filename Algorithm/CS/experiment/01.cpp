#include<iostream>
#include<vector>
#include<map>
#include<list>
#include<algorithm>
using namespace std;

/*
分治求最大及最小
*/

template <class T>
pair<T,T> minmax(T *a,int e,int r){
    pair <T,T> v;
    if(e==r){
        v.first=a[e];
        v.second=a[r];
    }
    else{
        int m=(e+r)/2;
        pair <T,T> v1=minmax(a,e,m);
        pair <T,T> v2=minmax(a,m+1,r);
        v.first=v1.first<v2.first?v1.first:v2.first;
        v.second=v1.second<v2.second?v2.second:v1.second;
    }
    return v;
}

int main(void){
    int array[10]={1,5,23,2,5,7,2,56,99,0};
    int n=sizeof(array)/sizeof(int);
    cout<<n<<endl;
    pair <int,int> temp=minmax<int>(array,0,10);
    cout<<temp.first<<"  "<<temp.second<<endl;
}

