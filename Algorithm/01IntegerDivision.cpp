#include <iostream>
using namespace std;
//integer division problem

int recursion(int n, int m){
    if(n==1 || m==1){
        return 1;
    }else if(n < m){
        return recursion(n, n);
    }else if(n == m){
        return recursion(n, n-1)+1;
    }else
    {
        return recursion(n-m, m) + recursion(n, m-1);
    }
}

int main(void){
    cout << recursion(3, 3) << endl;
}