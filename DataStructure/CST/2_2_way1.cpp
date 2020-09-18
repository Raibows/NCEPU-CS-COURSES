#include<iostream>
using namespace std;

const int mmp=10000; //stack is full with 5 elements
class stack{
    public:
    void init(void){ //initial the stack
        top=0;
    }
    void push(int x); //pushing function
    int pop(void); //poping stack
    int gettop(){ //get the top pointer
        return top;
    }
    private:
    int num[mmp]; //deposite the stack
    int top; //top pointer
    bool isfull(){
        return top==mmp?true:false;
    }
    bool isempty(){
        return top==-1?true:false;
    }
};

void stack::push(int x) {
 if(isfull()) {
 cout << "Stack is full!" << endl;
 return;
 };
 num[top]=x;
 top++;
} 
int stack::pop(void){
    top--;
    if(isempty()){
        cout<<"Stack is empty"<<endl;
        return 0;
    };
    return num[top];
}
int main(){
    stack s;
    s.init();
    int n=0;
    cin>>n;
    for(int i=0;i<n;i++){
        int tem=0;
        cin>>tem;
        s.push(tem);
    }
    for(int i=0;i<n;i++){
        cout<<s.pop()<<" ";
    }
    cout<<endl;
    system("pause");
    return 0;
}
