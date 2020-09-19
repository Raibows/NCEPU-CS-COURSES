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
	void insert_list(int position, int x);
	Node *locate_list(int x);
	void delete_list(int position);
    int length_list();
    void add_list(int x);
    int getlast_list();
    int getfirst_list();
    void show_list();
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
            //cout<<position<<" has been deleted successfully"<<endl;
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
int Linklist::getfirst_list(){
    if(empty_list()){
        cout<<"the linklist is empty"<<endl;
    }
    else{
        return head->next->data;
    }
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
    Linklist *L1=new Linklist();
	Linklist *L2=new Linklist();
    int n1=0; //the count of the 1st polynomial
	int n2=0; //the count of the 2nd polynomial
    cout<<"WARNING! you are using plan 1, you need to input the polynomial which has higher power first, or it may not work!"<<endl;
	cout<<"please input the 1st and the 2nd count in turn"<<endl; 
    cin>>n1>>n2;
	//create dynamic arrays to record the cofficient
	float *co1=new float[n1];
	float *co2=new float[n2];
	cout<<"now is the 1st polynomial"<<endl;
	for(int i=0;i<n1;i++){
		cout<<"please input the "<<(i+1)<<" coefficient"<<endl;
		cin>>co1[i];
	}
	cout<<"please input the power in turn"<<endl;
	L1->create_list(n1);

	cout<<"now is the 2nd polynomial"<<endl;
	for(int i=0;i<n2;i++){
		cout<<"please input the "<<(i+1)<<" coefficient"<<endl;
		cin>>co2[i];
	}
	cout<<"please input the power in turn"<<endl;
	L2->create_list(n2);
	
	//above is input procedure
	//below is calculate and output procedure

	Linklist *L3=new Linklist();  //to record the final result
	int n3=n1+n2;
	float *co3=new float[n3];
	Node *tem1=new Node(0);  //temporary variable
	Node *tem2=new Node(0);
	Node *tem3=new Node(0);
    tem1=L1->head->next;
	tem2=L2->head->next;
	tem3=L3->head;
    //use plan 1
    int judge=0;
    int k=0;
    int j=0;
    for(int i=0;i<n1;i++){
        cout<<"now is in 0"<<endl; //test
        judge=0;
        while((j<n2)&&(tem2!=NULL)){
            if(tem2==NULL){
                judge=0;
                cout<<"now is in 1"<<endl; //test
                break;
            }
            if(tem1->data==tem2->data){
                judge=1;
                co3[k]=co1[i]+co2[j];
                k++;
                j++;
                L3->add_list(tem1->data);
                tem1=tem1->next;
                tem2=tem2->next;
                cout<<"now is in 2"<<endl; //test
                break;
            }
            if(tem1->data>tem2->data){
                co3[k]=co2[j];
                j++;
                k++;
                L3->add_list(tem2->data);
                tem2=tem2->next;
                cout<<"now is in 3"<<endl; //test
                continue;
            }
            if(tem1->data<tem2->data){
                judge=0;
                break;
            }
        }
        if(judge==0){
            co3[k]=co1[i];
            k++;
            L3->add_list(tem1->data);
            tem1=tem1->next;
            cout<<"now is in 4"<<endl; //test
        }
    }

    //test
    L1->show_list();
    L2->show_list();
    L3->show_list();
    //test

    //now let's check it 
    for(int i=0;i<k;i++){
        cout<<co3[i]<<"x^"<<L3->getfirst_list()<<"+";
        L3->delete_list(L3->getfirst_list());
    }
    cout<<endl;
    system("pause");
	return 0;
}

//plan 2
   /*
	int k=0;
    int j=0;
	for(int i=0;i<n1;i++){
        tem1=tem1->next;
		for(j;j<n2;j++){
			if(tem1->data==tem2->data){
				co3[k]=co1[i]+co2[j];
                cout<<"now the co3 is "<<co3[k]; //test
                L3->add_list(tem1->data);
                k++;
                j++;
                tem2=tem2->next;
                break;
			}
            else if(tem1->data>tem2->data){
                tem2=tem2->next;
                continue;
            }
            else if(tem1->data<tem2->data){
                co3[k]=co1[i];
                L3->add_list(tem1->data);
                k++;
                break;
            }
		}
	}*/
