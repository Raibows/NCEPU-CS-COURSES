#include<iostream>
using namespace std;
int main(){
    int m,n;
    cin>>m>>n;
    int *array=new int[n];
    for(int i=0;i<n;i++){
        cin>>array[i];
    }
    int out=0;
    int i=0;
    int j=n;
    for(;j>0;j--){
        int tem=m;
        while(tem>0){
            out=i%n;
            if(array[out]==-1){
                i++;  
            }
            else{
                i++;
                tem--;
            }
        }
        cout<<array[out];
        array[out]=-1;
        i=out;
    }
    return 0;
    }
