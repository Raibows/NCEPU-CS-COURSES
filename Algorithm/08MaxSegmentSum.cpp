// maximum segment sum problem
// dynamic programming
#include <iostream>
#include <algorithm>

using namespace std;
int MaxSum(int n,int *a)
{
    int *b = new int[n+1];
    b[0] = a[0];
	int sum = 0;
    // int array[length] = {-2,11,-4,13,-5,2};
	for(int i = 1;i<=n;i++)
	{
		b[i] = max(b[i-1],0) + a[i-1];
	    sum	 = max(sum,b[i]); 
	}
    return sum;
}




void maxsegsum(int* array, int* dp, int length){// dp[i] means the max segment sum of array[0:i]
    dp[0] = array[0] > 0 ? array[0] : 0;
    for(int i=1;i<length;i++){
        if(dp[i-1] > 0){
            dp[i] = dp[i-1] + array[i];
        }else
        {
            dp[i] = array[i];
        }
        
    }
}

int main(void){
    const int length = 6;
    int array[length] = {-2,11,-4,13,-5,2};
    // int array[length] = {-4,-2,-3,-1,-5,-6};
    int* dp = new int [length];
    maxsegsum(array, dp, length);
    // 
    // sort(dp,dp+length);
    cout<<dp[length-1]<<endl;
    cout<<MaxSum(length, array);
}