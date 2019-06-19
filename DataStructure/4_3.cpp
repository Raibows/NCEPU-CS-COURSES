#include<iostream>
using namespace std;
int main(){
    int n=0;
    cin>>n;
    int **array=new int*[n+2];
    for(int i=0;i<(n+2);i++){
        array[i]=new int[n+2];
    }
    for(int i=0;i<n+2;i++){
        for(int j=0;j<n+2;j++){
            if(i==0||j==0||i==(n+1)||j==(n+1)){
                array[i][j]=-1;
            }else{
                array[i][j]=0;
            }
        }
    }
    int x,y,tem;
    x=1;y=1;tem=1;
    while(tem<(n*n+1)){
        while(array[x][y]==0){
            array[x][y]=tem;
            tem++;
            y++;
        }
        y--;
        x++;
        while(array[x][y]==0){
            array[x][y]=tem;
            tem++;
            x++;
        }
        x--;
        y--;
        while(array[x][y]==0){
            array[x][y]=tem;
            tem++;
            y--;
        }
        x--;
        y++;
        while(array[x][y]==0){
            array[x][y]=tem;
            tem++;
            x--;
        }
        x++;
        y++;
    }
    for(int i=1;i<n+1;i++){
        for(int j=1;j<n+1;j++){
            cout<<array[i][j]<<" ";
        }
        cout<<endl;
    }




    return 0;
}