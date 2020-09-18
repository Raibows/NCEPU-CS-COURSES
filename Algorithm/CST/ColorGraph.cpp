// color graph problem
// backtrack algorithm
#include <iostream>
using namespace std;

#define m 5 //num of color
#define num 5 // num of points
int *x = new int[m];
int** adj = new int* [num];


bool bcolor(int k){//judge if the kth point could be colored by x[k] color
    for(int i=0;i<k;i++){
        if(adj[i][k]==1&&x[i]==x[k]){
            return false;
        }
    }
}

void backtrack(int k){
    if(k==num){
        //output
        return;
    }
    for(int i=0;i<m;i++){
        x[k] = i;
        if(bcolor(k)){
            backtrack(k+1);
        }
    }
}

int main(void){
    for (int i = 0; i < num; i++) {
        adj[i] = new int[num];
    }

    // input adjacent table

    backtrack(0);

}