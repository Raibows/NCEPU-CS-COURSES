#include <iostream>
#include <algorithm>
using namespace std;



const int num = 6; //num of matrix
int p[num+1] = {30, 35, 15, 5, 10, 20, 25}; //matrix[i] = p[i-1] * p[i] row * column


void show(int **t){
    for(int i=1;i<=num;i++){
        for(int j=1;j<=num;j++){
            cout<<t[i][j]<<" ";
        }
        cout<<endl;
    }
}
void traceback(int i, int j, int **pos){
    if (i == j)
    {
        cout<< "A" << i;
        return;
    }
    cout<<"(";
    traceback(i, pos[i][j], pos);
    traceback(pos[i][j]+1, j, pos);
    cout<< ")";
}
void matrixchain(int num, int p[], int** cost, int** pos){
    for(int i=1;i<=num;i++){ //single matrix product chain
        cost[i][i] = 0;
    }
    for(int i=2;i<=num;i++){//multiple matrix product chain
        for(int j=1;j<=num-i+1;j++){//traverse all the possible combination
            int end = j + i -1; //from j to end
            cost[j][end] = 999999999;
            for(int k=j;k<end;k++){ //traverse to find the best divide position
                int temp_cost = cost[j][k] + cost[k+1][end] + p[j-1] * p[k] * p[end];
                if(temp_cost < cost[j][end]){
                    cost[j][end] = temp_cost;
                    pos[j][end] = k;
                }
            }
        }
    }
}




int main(void){
    int** cost = new int *[num+1];
    for(int i=0;i<=num;i++){
        cost[i] = new int[num+1];
    }// A[i,j] means the min cost from matrix[i] to matrix[j]

    int** pos = new int *[num+1];
    for(int i=0;i<=num;i++){
        pos[i] = new int[num+1];
    }// A[i,j] means the best divide pos for matrix[i] prpduct to matrix[j]


    for(int i=0;i<=num;i++){
        cout<< p[i] <<endl;
    }

    matrixchain(num, p, cost, pos);
    cout<<cost[1][num]<<endl;
    traceback(1, num, pos);
}