#include <iostream>

using namespace std;

template<typename T>
int Partition(T *array, int pivot, int end){ 
    T temp = array[pivot];
    int i = pivot; //record the position that the elements need to swap int the next procedure 
    for(int j=pivot+1; j<=end; j++){ //move the element less than the pivot element to the
        if(temp>array[j]){           //front of the pivot element
            i++; 
            swap(array[j], array[i]); 
        }
    }
    swap(array[i], array[pivot]); //only need toswap array[i] and array[pivot]
                                //because all the smaller elements have been moved front of it
    return i; // i is the right order for the pivot element
}

template<typename Q>                                
void QuickSort(Q *array, int begin, int rear){
    if(rear<=begin){
        return;
    }
    int pivot = Partition<Q>(array, begin, rear); //the pivot element has already in the right order
    QuickSort<Q>(array, begin, pivot-1); // so just let the front 
    QuickSort<Q>(array, pivot+1, rear); //and the rear part get ordered
}

int main(void){
    double array[10] = {6,245,25,3,2,1,304,23,4,5};
    QuickSort<double>(array, 0, 9);
    for(int i=0;i<10;i++){
        cout<<array[i]<<" ";
    }
}