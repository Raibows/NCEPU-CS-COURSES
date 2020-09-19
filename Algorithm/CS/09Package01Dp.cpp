//0-1 package dynamic programming

#include <iostream>
#include <algorithm>
using namespace std;
#define limit 10 //the limit of package's weight
#define num 5 //amount of goods

void solution(int** dp, int weight[], int value[]){
    //dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i]]+value[i])
    for(int i=0; i<=num; i++){
        dp[i][0] = 0; //there will be no goods in the package if the package's limit is ZERO
    }
    for(int i=0; i<=limit; i++){
        dp[0][i] = 0;
    }
    for(int j=1; j<=limit; j++){
        for(int i=1; i<=num; i++){
            if(weight[i-1] <= j){
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i-1]] + value[i-1]);
            }else
            {
                dp[i][j] = dp[i-1][j];
            }
            
        }
    }
    
}

int main(void){
    int** dp = new int*[num+1];
    for(int i=0; i<=num; i++){
        dp[i] = new int [limit+1];
    }
    int weight[5] = {2, 2, 6, 5, 4};
    int value[5] = {6, 3, 5, 4, 6};
    solution(dp, weight, value);
    cout<< dp[num][limit] << endl;
}