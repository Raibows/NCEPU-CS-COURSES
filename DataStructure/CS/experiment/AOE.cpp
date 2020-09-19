#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
class storage_node{
public:
    int start;
    int end;
    int weight;
    storage_node(){
        start=0;
        end=0;
        weight=0;
    };
};
class edge_node{
public:
    double weight;
    int local;
    edge_node *next;
    edge_node();
};
edge_node::edge_node(){
    weight=0;
    local=-1;
    next=NULL;
}
class vertex_node{
public:
    int in_degree;
    string name;
    edge_node *next;
    vertex_node();
};
vertex_node::vertex_node(){
    in_degree=0;
    name="error";
    next=NULL;
}
class adjlist{
public:
    vertex_node *list;
    int vertex_num;
    int side_num;
    int find_local(string a);
    adjlist();
    void create_link(int a,int b,int c);
    void show();
    void dfs(int start); //use dfs to help judge whether the graph has a loop
    int *visited; //if visited,visited[vertex_num]=v;set a guard
    void initial_visited();
    int judge_loop(); //return 1 if the graph has loop
    int find_zero_indegree();
    void AOE();
};
adjlist::adjlist(){
    cin>>vertex_num>>side_num;
    visited=new int[vertex_num+1];
    initial_visited();
    list=new vertex_node[vertex_num];
    for(int i=0;i<vertex_num;i++){
        cin>>list[i].name;
    }
    for(int i=0;i<side_num;i++){
        string tem1,tem2;
        tem1=tem2="error";
        int weight=-1;
        cin>>tem1>>tem2>>weight;
        int local_1=find_local(tem1);
        int local_2=find_local(tem2);
        create_link(local_1,local_2,weight);
    }
}
int adjlist::find_local(string a){
    for(int i=0;i<vertex_num;i++){
        if(list[i].name==a){
            return i;
        }
    }
    return -1;
}
void adjlist::create_link(int a,int b,int c){
    edge_node *cursor=new edge_node();
    cursor->local=b;
    cursor->weight=c;
    cursor->next=list[a].next;
    list[a].next=cursor;
    list[b].in_degree++;
}
void adjlist::show(){
    for(int i=0;i<vertex_num;i++){
        edge_node *cursor=new edge_node();
        cursor=list[i].next;
        cout<<list[i].name;
        while(cursor!=NULL){
            cout<<" -> "<<list[cursor->local].name;
            cursor=cursor->next;
        }
        cout<<endl;
    }
}
void adjlist::dfs(int start){
    edge_node *cursor=new edge_node();
    cursor=list[start].next;
    visited[start]=1;
    while(cursor!=NULL&&visited[vertex_num]!=-999){
        if(visited[vertex_num]==cursor->local){
            visited[vertex_num]=-999; //999 is the tag for loop
            break;
        }else{
            dfs(cursor->local);
            cursor=cursor->next;
        }
    }
}
void adjlist::initial_visited(){
    for(int i=0;i<vertex_num+1;i++){
        visited[i]=-1;
    }
}
int adjlist::judge_loop(){
    for(int i=0;i<vertex_num;i++){
        if(visited[vertex_num]==-999){
            return 1;
        }
        visited[vertex_num]=i;
        dfs(i);
    }
    return 0;
}
void adjlist::AOE(){
    if(judge_loop()==0){
        initial_visited();
        int *tag=new int[vertex_num];
        for(int i=0;i<vertex_num;i++){
            tag[i]=0;
        }
        for(int start=0;start<vertex_num;start++){
            edge_node *cursor=new edge_node();
            cursor=list[start].next;
            while(cursor!=NULL){
                if((tag[start]+cursor->weight)>tag[cursor->local]){
                    tag[cursor->local]=cursor->weight+tag[start];
                }
                cursor=cursor->next;
            }
        }
        sort(tag,tag+vertex_num);
        cout<<tag[vertex_num-1]<<endl;
        /*
        int tem=find_zero_indegree();
        while(list[tem].next!=NULL){
            int tem=find_zero_indegree();
            cout<<list[tem].name<<"-->";
            visited[tem]=1;
            edge_node *cursor=new edge_node();
            cursor=list[tem].next;
            int tag_num=0;
            storage_node *tag=new storage_node[vertex_num];
            while(cursor!=NULL){
                tag[tag_num].end=cursor->local;
                tag[tag_num].start=tem;
                tag[tag_num].weight=cursor->weight;
                tag_num++;
                list[cursor->local].in_degree--;
                cursor=cursor->next;
            }
            for(int i=0;i<tag_num;i++){
                tag[i].start=tag[i].end;
            }
        }*/
    }
}
int adjlist::find_zero_indegree(){
    for(int i=0;i<vertex_num;i++){
        if(list[i].in_degree==0&&visited[i]==-1){
            return i;
        }
    }
    return -1;
}


int main(){
    adjlist *test=new adjlist();
    test->show();
    test->initial_visited();
    cout<<test->judge_loop()<<endl;
    test->AOE();
    return 0;
}