#include<iostream>
using namespace std;
/*
思路如下：
首先使用create函数给链表一一赋值，并以回车符号作结束；
调用move_max函数：
    遍历链表记录max；
    找到后继续遍历找到最后一个节点添加一个值为max的结点；
    删除第一个为max的结点
    （具体断开与连接很简单不详述）
调用show函数展示链表所有结点的值
*/
struct node{
    int data;
    node *link;
};
class linklist{
public:
    linklist(){
        node *list=new node();
        list->data=0;
        list->link=NULL;
    }
    void create();
    void move_max();
    void show();
    node *list;
};
void linklist::move_max(){
    int max=-1;
    node *tem=new node();
    tem=list;
    max=tem->link->data;
    //search for max
    while(tem->link!=NULL){
        tem=tem->link;
        if(max<tem->data){
            max=tem->data;
        }
    }
    //link the end with the max
    node *p=new node();
    p->data=max;
    p->link=NULL;
    tem->link=p;
    node *pre=new node();
    pre=list;
    while(pre->link->data!=max){
        pre=pre->link;
    }
    //delete orignal max node
    node *h=new node();
    h=pre->link;
    pre->link=h->link;
    delete h;
}
void linklist::create(){
    node *tem=new node();
    tem=list;
    char a='0';
    while(a=cin.get()!='\n'){
        node *q=new node();
        tem->link=q;
        cin.unget();
        cin>>q->data;
        q->link=NULL;
        tem=q;
    }
}
void linklist::show(){
    node *tem=new node();
    tem=list;
    while(tem->link!=NULL){
        tem=tem->link;
        cout<<tem->data<<" ";
    }
}
int main(){
    linklist *l=new linklist();
    l->create();
    l->move_max();
    l->show();
    return 0;
}