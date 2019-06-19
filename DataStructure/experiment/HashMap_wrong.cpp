#include<iostream>
#include<string>
using namespace std;
class Node{
public:
    string name;
    string address;
    string phone;
    Node *next;
    Node();
};
Node::Node(){
    name="error";
    address="error";
    phone="error";
    next=NULL;
}
class HashMap{
public:
    int size;
    Node *map;
    int hashfuc(string a);
    void find();
    void insert();
    void del();
    HashMap();
};
HashMap::HashMap(){
    size=8;
    map=new Node[8];
}
int HashMap::hashfuc(string a){
    int x=0;
    for(int i=0;i<a.length();i++){
       x+=int(a[i]);
    }   
    return x%7;
}
void HashMap::insert(){
    Node *tem=new Node();
    cin>>tem->name>>tem->phone>>tem->address;
    int local=hashfuc(tem->phone);
    if(map[local].name=="error"){
        map[local].name=tem->name;
        map[local].address=tem->address;
        map[local].phone=tem->phone;
    }else{
        Node *cursor=new Node();
        cursor=addressof(map[local]);
        while(cursor->next!=NULL){
            cursor=cursor->next;
        }
        cursor->next=tem;
    }
}
void HashMap::find(){
    string key="error";
    int tag=0;
    cin>>key;
    int local=hashfuc(key);  
    Node *cursor=new Node();
    cursor=addressof(map[local]);
    while(cursor!=NULL){
        if(cursor->phone==key){
            cout<<"name: "<<cursor->name<<"  phone: "<<cursor->phone<<"  address: "<<cursor->address<<endl;
            tag=1;
            break;
        }
        cursor=cursor->next;
    }
    if(tag==0){
        cout<<"input error:no object's phone is "<<key<<endl;
    }
}
void HashMap::del(){
    string key="error";
    int tag=0;
    cin>>key;
    int local=hashfuc(key);
    if(map[local].phone==key){
        if(map[local].next==NULL){
            map[local].address="error";
            map[local].name="error";
            map[local].phone="error";
            tag=1;
        }else{
            Node *tem=new Node();
            tem=map[local].next;
            map[local].address=tem->address;
            map[local].name=tem->name;
            map[local].phone=tem->phone;
            map[local].next=tem->next;
            delete tem;
            tag=1;           
        }
    }else if(map[local].next!=NULL){
        Node *cursor=new Node();
        Node *pre=new Node();
        pre=addressof(map[local]);
        cursor=pre->next;
        while(cursor!=NULL){
            if(cursor->phone==key){
                pre->next=cursor->next;
                delete cursor;
                tag=1;
                break;
            }
            pre=cursor;
            cursor=cursor->next;
        }
    }
    if(tag==0){
        cout<<"there is no object's phone is "<<key<<endl;
    }else{
        cout<<"delete successfully !"<<endl;
    }

}

int main(){
    HashMap *test=new HashMap();
    string x="error";
    cout<<"I:insert, F:find, D:delete, E:exit"<<endl;
    cin>>x;
    while(x!="E"){
        if(x=="I"){
            test->insert();
        }else if(x=="F"){
            test->find();
        }else if(x=="D"){
            test->del();
        }else if(x=="E"){
            break;
        }
        cout<<"I:insert, F:find, D:delete, E:exit"<<endl;
        cin>>x;
    }
    return 0;
}