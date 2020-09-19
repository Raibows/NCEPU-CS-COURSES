#include<iostream>
using namespace std;
class node{
public:
    node(int x,int y);
    ~node();
    int num;
    int score;
    node *next;
};
node::node(int x,int y){
    num=x;
    score=y;
    next=NULL;
}
node::~node(){
}
class linklist{
public:
    node *head;
    linklist();
    void create();
    void show();
};
linklist::linklist(){
    node *head=new node(0,0);
}
void linklist::create(){
    node *tem=new node(0,0);
    tem=head;
    for(int i=0;i<3;i++){
        node *p=new node(0,0);
        cin>>p->num>>p->score;
        tem->next=p;
        tem=p;
        p->~node();
    }
}
void linklist::show(){
    node *tem=new node(0,0);
    tem=head->next;
    while(tem!=NULL){
        cout<<"[num="<<tem->num<<",score="<<tem->score<<"]"<<endl;
        tem=tem->next;
    }
}
int main(){
    linklist *l=new linklist();
    l->create();
    l->show();
    return 0;
}