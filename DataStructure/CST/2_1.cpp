#include<iostream>
using namespace std;
int main()
{
    int n,wei;
    cin>>wei>>n;
    int temp=0;
    int *array=new int[n];
    for(int i=0;i<n;i++){
        cin>>array[i];
    }
    for(int i=wei+n;i<(wei+2*n);i++){
        temp=i%n;
        cout<<array[temp]<<" ";
    }
    return 0;
}