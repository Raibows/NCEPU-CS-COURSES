#include<iostream>
#include<string>
#include<fstream>
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
    void insert(string a,string b,string c);
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
void HashMap::insert(string a,string b,string c){
    Node *tem=new Node();
    tem->name=a;
    tem->phone=b;
    tem->address=c;
    int local=hashfuc(tem->phone);
    Node *cursor=new Node();
    cursor=addressof(map[local]);
    while(cursor->next!=NULL){
        cursor=cursor->next;
    }
    cursor->next=tem;
}
void HashMap::find(){
    string key="error";
    cin>>key;
    int tag=0;
    int local=hashfuc(key);  
    Node *cursor=new Node();
    cursor=map[local].next;
    while(cursor!=NULL){
        if(cursor->phone==key){
            cout<<"name: "<<cursor->name<<"  phone: "<<cursor->phone<<"  address: "<<cursor->address<<endl;
            tag=1;
            break;
        }else{
            cursor=cursor->next;
        }
    }
    if(tag==0){
        cout<<"there is no object's phone is "<<key<<endl;
    }
}
void HashMap::del(){
    string key="error";
    int tag=0;
    cin>>key;
    int local=hashfuc(key);
    Node *cursor=new Node();
    Node *pre=addressof(map[local]);
    cursor=pre->next;
    while(cursor!=NULL){
        if(cursor->phone==key){
            pre->next=cursor->next;
            delete cursor;
            tag=1;
            break;
        }else{
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
void read_txt(HashMap *a){
    ifstream infile;
    infile.open("C:/Users/Raibows/Desktop/test.txt",ios::in);
    string tem1,tem2,tem3;
    infile>>tem1;
    while(tem1!="#"){
        infile>>tem2>>tem3;
        a->insert(tem1,tem2,tem3);
        infile>>tem1;
    }
    cout<<"read successfully"<<endl;
    infile.close();
}
int main(){
    HashMap *test=new HashMap();
    read_txt(test); //READ THE INFO FROM THE EXTERNAL FILE
    string x="error";
    cout<<"I:insert, F:find, D:delete, E:exit"<<endl;
    cin>>x;
    while(x!="E"){
        if(x=="I"){
            string name,phone,address;
            cin>>name>>phone>>address;
            test->insert(name,phone,address);
        }else if(x=="F"){
            test->find();
        }else if(x=="D"){
            test->del();
        }else if(x=="E"){
            break;
        }else{
            cout<<"input error,please input again!"<<endl;
        }
        cout<<"I:insert, F:find, D:delete, E:exit"<<endl;
        cin>>x;
    }
    return 0;
}
