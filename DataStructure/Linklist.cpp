#include<iostream>
using namespace std;
class Node {
public:
    Node(int d);
    ~Node();
	int data;
	Node *next;
};
Node::Node(int d){
    data = d;
    next = NULL;
}
Node::~Node(){
}

class Linklist {
public:
	Linklist() {
		head = new Node(0);
	}
    ~Linklist(){
        cout<<"this linklist has been destroyed"<<endl;
    }
    void create_list(int n);
	bool empty_list();
	void insert_list(int position, int x);  //insert a new node after the position
	Node *locate_list(int x); //return the node whose data is x first in the linklist
	void delete_list(int position);
    int length_list();
    void add_list(int x); //add new node in the end
    int getlast_list();
    void show_list();
private:
	Node *head;
};
int Linklist::length_list(){
    int n=0;
    Node *tem;
    tem=head;
    while(tem->next!=NULL){
        n++;
        tem=tem->next;
    }
    return n;
}
void Linklist::create_list(int n){
    if(n<=0){
        cout<<"wrong number!"<<endl;
    }
    else{
        Node *tem=new Node(0);
        tem=head;
        for(int i=1;i<=n;i++){
            Node *p=new Node(0);
            cout<<"please input the"<<i<<"node"<<endl;
            cin>>p->data;
            tem->next=p;
            tem=p;
            p->~Node();
        }
    }
    cout<<"the linklist has been created successfully"<<endl;
}
bool Linklist::empty_list() {
	return head->next == NULL ? true : false;
}
void Linklist::insert_list(int position,int x){
    if(!empty_list()){
        if(locate_list(position)->data!=position){
            cout<<"there is no "<<position<<" in this linklist"<<endl;
        }
        else{
            Node *tem=new Node(0);
            tem->data=x;
            tem->next=locate_list(position)->next;
            locate_list(position)->next=tem;
            cout<<"Finished Successfully"<<endl;
        }
    }
    else{
        cout<<"this linklist is empty"<<endl;
    }
}
Node *Linklist::locate_list(int x){
    Node *tem=new Node(0);
    tem=head->next;
    while((tem!=NULL)&&(tem->data!=x)){
        tem=tem->next;
    }
    return tem;
}
void Linklist::delete_list(int position){
    if(!empty_list()){
        if(locate_list(position)->data!=position){
            cout<<"there is no "<<position<<" in this linklist"<<endl;
        }
        else{
            Node *tem=new Node(0);
            tem=head;
            while(tem->next->data!=position){
            }
            tem->next=locate_list(position)->next;
            locate_list(position)->~Node();
            cout<<position<<" has been deleted successfully"<<endl;
        }
    }
    else{
        cout<<"this linklist is empty"<<endl;
    }
}
void Linklist::add_list(int x){
    Node *tem=new Node(0);
    tem=head;
    while(tem->next!=NULL){
        tem=tem->next;
    }
    Node *p=new Node(0);
    tem->next=p;
    p->data=x;
    cout<<"the node has been added successfully"<<endl;
}
int Linklist::getlast_list(){
    Node *tem=new Node(0);
    tem=head;
    while(tem->next!=NULL){
        tem=tem->next;
    }
    return tem->data;
}
void Linklist::show_list(){
    Node *tem=new Node(0);
    tem=head;
    while(tem->next!=NULL){
        tem=tem->next;
        cout<<tem->data<<" ";
    }
    cout<<endl;
}

int main(){
    Linklist *l=new Linklist();
    int n=0;
    cin>>n;
    l->create_list(n);
    cin>>n;
    l->add_list(n);
    cout<<l->getlast_list()<<endl;






    system("pause");
	return 0;
}



