#include <algorithm>
#include <iostream>
#include <stdlib.h> 
#include <time.h>
// 这是归并排序实验
using namespace std;
#define CLK_TCK  CLOCKS_PER_SEC //机器时钟每秒的打点数  

// template <typename T>
// bool operator<(const T &x, const T &y){
//     return x < y;
// }

template <typename T>
void Merge(T *all, T *left, T *right, int leftn, int rightn){
    int i,j,k;
    i=0;
    j=0;
    k=0;
    //merge procedure
    while (i<leftn && j<rightn)
    {
        if(left[i]<right[j]){
            all[k] = left[i];
            i++;
            k++;
        }else{
            all[k] = right[j];
            j++;
            k++;
        }
    }
    //judge if all elements are in new array all
    while (i<leftn)
    {
        all[k] = left[i];
        k++;
        i++;
    }
    while(j<rightn){
        all[k] = right[j];
        k++;
        j++;
    }
    
           
}

template <typename T>
void MergeSort(T *array, int n){
    if(n < 2){
        return;
    }
    int mid = int(n/2);
    T *newLeft;
    T *newRight;
    newLeft = new T[mid];
    newRight = new T[n-mid];
    //divide the array to left  and right subarray
    for(int i=0;i<mid;i++){
        newLeft[i] = array[i];
    }
    for(int i=mid;i<n;i++){
        newRight[i-mid] = array[i];
    }
    MergeSort<T>(newLeft, mid);
    MergeSort<T>(newRight, n-mid);
    Merge<T>(array, newLeft, newRight, mid, n-mid);

    //free the memory
    delete newLeft;
    delete newRight;
}

template <typename T>
void show(T *array, int n){
    for(int i=0;i<n;i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;
}

template <typename T>
T *getRandom(int n) {
	srand((int)time(0));
	T *res = new T[n];
    for(int i=0;i<n;i++){
        res[i] = rand();
    }
	return res;
}



int main(void){
    clock_t begin,end;
    long n = 0;
    cout << "please input the length"<<endl;
    cin >> n;
    double *array;
    double *testarray = new double[n];
    array = getRandom<double>(n);
    for (int i = 0; i < n; i++)
    {
        testarray[i] = array[i];
    }
    // show<double>(array, n);
    begin = clock();
    // MergeSort<double>(array, n);
    end = clock();
    cout<<"my algorithm costs "<<double(end-begin)/CLK_TCK<<endl;
    // show<double>(array, n);

    begin = clock();
    sort(testarray,testarray+n);
    end = clock();
    cout<< "STL sort costs "<<double(end-begin)/CLK_TCK<<endl;

    

    delete array;
}