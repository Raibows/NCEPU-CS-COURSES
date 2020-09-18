#include<iostream>
#include<string>
using namespace std;
class EdgeNode{
public:
    int tag;
    int weight;
    EdgeNode *next;
    EdgeNode(int a,int b);
};
EdgeNode::EdgeNode(int a,int b){
    tag=a;
    weight=b;
    next=NULL;
}
class VertexNode{
public:
    string data;
    int indegree;
    EdgeNode *next;
    VertexNode();
    void createlink(EdgeNode *a);
};
VertexNode::VertexNode(){
    data="error";
    next=NULL;
    indegree=0;
}
void VertexNode::createlink(EdgeNode *a){
    if(next==NULL){
        next=a;
    }else{
        EdgeNode *tem=new EdgeNode(-1,-1);
        tem=next;
        while(tem->next!=NULL){
            tem=tem->next;
        }
        tem->next=a;
    }

}
class AdjList{
public:
    int vertex_num;
    int edge_num;
    int find(string a);
    VertexNode *list;
    AdjList();
    ~AdjList();
    int find_zero_indegree();
    int *visited;
};
AdjList::~AdjList(){
    cout<<"object has been deleted"<<endl; 
}
AdjList::AdjList(){
    cin>>vertex_num>>edge_num;
    list=new VertexNode[vertex_num];
    visited=new int[vertex_num];
    for(int i=0;i<vertex_num;i++){
        visited[i]=0;
    }
    for(int i=0;i<vertex_num;i++){
        cin>>list[i].data;
    }
    for(int i=0;i<edge_num;i++){
        string tem1,tem2;
        int weight=0;
        cin>>tem1>>tem2;
        //cin>>weight;   //input the start and the end and the weight
        int pos1=find(tem1);
        int pos2=find(tem2);
        list[pos2].indegree++;  //add indegree
        EdgeNode *temp=new EdgeNode(pos2,weight);
        list[pos1].createlink(temp);
    }
    cout<<"graph sueccessfully created !"<<endl;
}
int AdjList::find(string a){
    for(int i=0;i<vertex_num;i++){
        if(a==list[i].data){
            return i;
        }
    }
    return -1;
}
int AdjList::find_zero_indegree(){
    for(int i=0;i<vertex_num;i++){
        if(visited[i]==0&&list[i].indegree==0){
            return i;
        }
    }
    return -1;
}
void AOV(AdjList *a){
    for(int i=0;i<a->vertex_num;i++){
        int tem=a->find_zero_indegree();
        if(tem!=-1){
            cout<<a->list[tem].data<<"-->";
            a->visited[tem]=1;
            EdgeNode *del=new EdgeNode(-1,-1);
            del=a->list[tem].next;
            while(del!=NULL){
                a->list[del->tag].indegree--; //reduce the indegree
                del=del->next;
            }
            a->list[tem].next=NULL;
            delete del;            
        }
    } 
}
int main(){
    AdjList *test=new AdjList();
    AOV(test);
    test->~AdjList();
    delete test;
    return 0;
}