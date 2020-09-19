#include <iostream>
#include <algorithm>
#include <cmath>
int all = 13;   //the  max all queen
int n = 0;  //the first n queen

using namespace std;    
//check if the kth queen could place in k row and x[k] column
bool bPlace(int k, int *x){
    for (int i = 0; i < k; i++)
    {
        if(x[k] == x[i]){
            return false;
        }else if (abs(k-i) == abs(x[k] - x[i]))
        {
            return false;
        }
    }
    return true;
}

//output procedure
void output(int *x, int num){
    cout<<"( ";
    cout<<(x[0]+1);    
    for(int i=1;i<num;i++){
        cout<<","<<x[i]+1;
    }
    cout<<" )  ";
}

//backtrack procedure
void BackTrack(int k, int *x, int &flag){
    if (k == n){
        flag ++; // solution count increment
        if(flag==1){
            output(x, n); //output the first solution
        }
        return;
    }
    for (int i = 0; i < n; i++)
    {
        x[k] = i;
        if(bPlace(k, x)){
            BackTrack(k+1, x, flag);
        }
    }
    

}
    
int main(void){
    int flag = 0;
    cout<<"---------------------------------------"<<endl;
    int *x;
    for(int i=4;i<=all;i++){
        n = i;
        x = new int[n];
        flag = 0;
        cout<<"Queen " << i ;
        cout<< " the first solution ";
        BackTrack(0, x, flag);
        cout<< " Solutions " << flag <<endl;
        delete []x;
    }
    cout<<"---------------------------------------"<<endl;
}