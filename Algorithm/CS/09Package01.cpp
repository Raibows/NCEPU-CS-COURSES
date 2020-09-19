//0-1 package problem
//backtrack algorithm
#include <iostream>
using namespace std;
#define num 3
int best_value = 0;
int weight[num] = {20,15,15};
int value[num] = {40,25,25};
int limit = 30;
int solution[3];
int final_solution[3];

void copy(int a[], int b[]){
    for(int i=0;i<num;i++){
        a[i] = b[i];
    }
}


void backtrack(int k, int current_weight, int current_value){//construct the solution space {x0,x1,xi---xn-1} xi = 0 or 1
    if(k==0){
        current_weight = 0;
        current_value = 0;
    }
    if(k==num){
        if(current_value > best_value){
            best_value = current_value;
            copy(final_solution, solution);
        }
        return;
    }
    for(int i=0;i<2;i++){
        solution[k] = i;
        current_weight += solution[k] * weight[k];
        if(current_weight > limit){
            // cout<< current_weight << "www"<<endl;
            break;
        }
        current_value += solution[k] * value[k];
        backtrack(k+1, current_weight, current_value);
    }
}


int main(void){
    int current_value,current_weight;
    current_value=current_weight=0;
    backtrack(0, current_weight, current_value);
    cout<<best_value<<endl;
    for(int i=0;i<num;i++){
        cout<<final_solution[i]<<" ";
    }
}

