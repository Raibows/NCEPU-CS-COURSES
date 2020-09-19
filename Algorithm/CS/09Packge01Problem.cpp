#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

//01 package problem
// greedy algorithm

template <typename T>
class pack{
public:
    T weight;
    T value;
    T unit_value;
    pack(){
        weight = 0;
        value = 0;
        unit_value = weight/0;
    }
};
template <typename T>
bool operator <(const pack<T> &x, const pack<T> &y){
    return x.unit_value < y.unit_value;
}




template <typename T>
class solution{
public:
    int num;
    T limit; //weight limit
    pack<T> *arr; //store info of packages in all
    queue<int> choice; //choices of package
    T all_value;
    T all_weight;
    solution(){
        cout<<"please input num and limit weight"<<endl;
        cin>>num>>limit;
        arr = new pack<T>[num];
        cout<<"please input weight first and value second"<<endl;
        for(int i=0;i<num;i++){
            cin>>arr[i].weight>>arr[i].value;
            arr[i].unit_value = arr[i].value / arr[i].weight;
        }
    }
    void greedy_solution();
    void show_result();
    ~solution(){
        delete[] arr;
    }
};
template <typename T>
void solution<T>::greedy_solution(){
    sort(arr, arr+num);
    for(int i=num-1;i>=0;i--){
        if((arr[i].weight+all_weight) <= limit){
            all_weight += arr[i].weight;
            all_value += arr[i].value;
            choice.push(i);
        }else
        {
            // break; //greedy algorithm could't have optimal solution
        } 
    }
    
}
template <typename T>
void solution<T>::show_result(){
    cout<<"max weight is "<<all_weight<<endl;
    cout<<"max value is "<<all_value<<endl;
    cout<<"select pack are below "<<endl;
    cout<<"--weight--value--unit_value--"<<endl;
    while (!choice.empty())
    {
        int temp = choice.front();
        choice.pop();
        cout<<"-----"<<arr[temp].weight<<"-----"<<arr[temp].value<<"-----"<<arr[temp].unit_value<<"-----"<<endl;
    }
}



int main(void){
    solution<double> test;
    test.greedy_solution();
    test.show_result();
    test.~solution();
}
