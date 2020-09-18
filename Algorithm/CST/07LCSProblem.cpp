//Longest Common Sequence Problem
//LCS problem
#include <iostream>
#include <string>
using namespace std;


void LCS(int** dp, int* s1, int* s2, int length_s1, int length_s2, string** record){ //use ** for double dimensional array
    // dp is the table and dp[i][j] means the LCS of s1[0:i-1] and s2[0:j-1]
    for(int i=0;i<=length_s1;i++){
        dp[i][0] = 0; //the LCS will be ZERO only if one of the length of s1 or s2 is 0
        record[i][0] = "";
    }
    for(int i=0;i<=length_s2;i++){
        dp[0][i] = 0;
        record[0][i] = "";
    }
    for(int i=1;i<=length_s1;i++){
        for(int j=1;j<=length_s2;j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1; //recursion 
                record[i][j] = record[i-1][j-1] + to_string(s1[i-1]);
            }else if(dp[i-1][j] > dp[i][j-1]){
                dp[i][j] = dp[i-1][j];
                record[i][j] = record[i-1][j];
            }else
            {
                dp[i][j] = dp[i][j-1];
                record[i][j] = record[i][j-1];
            }
        }
    }
}


int main(void){
    int s1[8] = {1,3,4,5,6,7,7,8};
    int s2[9]= {3,5,7,4,8,6,7,8,2};
    const int length_s1 = 8;
    const int length_s2 = 9;
    int** dp = new int* [length_s1+1];
    string** temp = new string* [length_s1+1];
    for(int i=0;i<=length_s1;i++){
        dp[i] = new int[length_s2+1];
        temp[i] = new string[length_s2+1];
    }
    LCS(dp, s1, s2, length_s1, length_s2, temp);
    cout << dp[length_s1][length_s2] << endl;
    cout << temp[length_s1][length_s2] << endl;
}