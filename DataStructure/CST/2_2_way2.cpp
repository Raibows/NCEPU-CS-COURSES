#include<iostream>
using std::cout;
using std::cin;
using std::endl;
const int mmp=10000;
class queue{
    public:
    int rear; //rear pointer
    int front; //front pointer
    int num[mmp];
    void init_queue() {
        rear=0;
        front=0;
    }
    void in_queue(int x) {
        if(full_queue()) {
            cout << "Queue is full" << endl;
            return;
        }
        rear=(rear+1)%mmp;
        num[rear]=x;
    }
    int out_queue() {
        if(empty_queue()) {
            cout <<"Queue is empty"<<endl;
            return 0;
        } else {
            front=(front+1)%mmp;
            return num[front];
        }
    }
    bool full_queue(){
        return (rear+1)%mmp==front?true:false;
    }
    bool empty_queue(){
        return rear==front?true:false;
    }
};
class stack{
    public:
    int top;
    int num[mmp];
    void init_stack(){
        top=0;
    }
    void push_stack(int x){
        if(full_stack()){
            cout<<"Stack is full"<<endl;
        }
        else{
        num[top]=x;
        top++;
        }
    }
    int pop_stack(){
        top--;
        if(empty_stack()){
            cout<<"Stack is empty"<<endl;
            return 0;
        }
        else{

        return num[top];
        }
    }
    bool empty_stack(){
        return top==-1?true:false;
    }
    bool full_stack(){
        return top==mmp?true:false;
    }
};
int main(){
    queue q;
    stack s;
    q.init_queue();
    s.init_stack();
    int n=0;
    cin>>n;
    for(int i=0;i<n;i++){
        int tem=0;
        cin>>tem;
        q.in_queue(tem);
    }
    for(int i=0;i<n;i++){
        int tem=0;
        tem=q.out_queue();
        s.push_stack(tem);
    }
    for(int i=0;i<n;i++){
        cout<<s.pop_stack()<<" ";
    }
    cout<<endl;
}