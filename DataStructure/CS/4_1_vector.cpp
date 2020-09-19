#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int numberA,numberB;
    cin>>numberA>>numberB;
    int number=numberA+numberB;
    vector <vector<int>> a;
    a.resize(number,vector<int>(3));
    for(int i=0;i<numberA;i++){
        for(int j=0;j<3;j++){
            cin>>a[i][j];
        }
    }
    int row,column,value;
    for(int i=0;i<numberB;i++){
        int flag=0;
        cin>>row>>column>>value;
        for(int k=0;k<numberA;k++){
            if(row==a[k][0]&&column==a[k][1]){
                a[k][2]+=value;
                number--;
                flag=1;
            }
        }
        if(flag==0){
            a[numberA][0]=row;
            a[numberA][1]=column;
            a[numberA][2]=value;
            numberA++;
        }
    }
    int numberOut=number;
    for(int i=0;i<number;i++){
        if(a[i][2]==0){
            numberOut--;
            continue;
        }
        for(int j=0;j<3;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    if(numberOut==0){
        cout<<-1<<" "<<-1<<" "<<-1;
    }
    cout<<endl; 

    

    return 0;
}
