//line 84 undirected graph

#include<iostream>
#include<string>
#include<queue>
using namespace std;
class EdgeNode{
public:
    int adjvex;
    double weight;
    EdgeNode *next;
    EdgeNode(int a,double b);
    void createlink(EdgeNode *a);
};
EdgeNode::EdgeNode(int a,double b){
    adjvex=a;
    weight=b;
    next=NULL;
}
void EdgeNode::createlink(EdgeNode *a){
    next=a;
}

class VertexNode{
public:
    VertexNode();
    string data;
    EdgeNode *next;
    void init(string a);
    void createlink(EdgeNode *a);  //if it does not have the first edgenode ,return 1;else return 0;
};
VertexNode::VertexNode(){
    next=NULL;
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
    int *visited;
    int vertexnum;
    int sidenum;
    VertexNode *list;
    AdjList();
    int find(string a);
};
AdjList::AdjList(){
    //cout<<"请依次输入顶点数，边数"<<endl;
    cin>>vertexnum>>sidenum;
    visited=new int[vertexnum];
    list=new VertexNode[vertexnum];
    for(int i=0;i<vertexnum;i++){
        //cout<<"请输入第"<<(i+1)<<"个顶点"<<endl;
        cin>>list[i].data;
    }
    for(int i=0;i<sidenum;i++){
        string tem1,tem2;
        double weight;
        //cout<<endl<<"请输入第"<<(i+1)<<"个边的信息"<<endl;
        //cout<<"请输入起点";
        cin>>tem1;
        //cout<<"请输入终点";
        cin>>tem2;
        //cout<<"请输入权值";
        //cin>>weight;
        int temp1=find(tem1);
        int temp2=find(tem2);
        EdgeNode *hh=new EdgeNode(temp2,weight=0); //for test weight=0
        list[temp1].createlink(hh);
        EdgeNode *tt=new EdgeNode(temp1,weight=0); //undirected graph
        list[temp2].createlink(tt);
    }
    cout<<"created successfully"<<endl;
}
int AdjList::find(string a){
    for(int i=0;i<vertexnum;i++){
        if(list[i].data==a){
            return i;
        }
    }
    cout<<"未找到名为"<<a<<"的顶点"<<endl;
    return -1;
}


void dfs(int a,AdjList *b){
    cout<<b->list[a].data<<" ";
    b->visited[a]=1;
    EdgeNode *tem;
    tem=b->list[a].next;
    while(tem!=NULL){
        if(b->visited[tem->adjvex]!=1){
            dfs(tem->adjvex,b);
        }
        tem=tem->next;
    }
    
    for(int i=0;i<b->vertexnum;i++){//fei
        if(b->visited[i]!=1){
            dfs(i,b);
        }
    }
}
void bfs(int a,AdjList *b){
    queue<int> tem;
    tem.push(a);
    while(1){
        EdgeNode *hh;
        hh=b->list[a].next;        
        while(hh!=NULL){
            if(b->visited[hh->adjvex]!=-1){
                tem.push(hh->adjvex);
            }
            hh=hh->next;
        }
        if(b->visited[a]!=-1){      
            cout<<b->list[a].data<<" ";
            b->visited[a]=-1;
        }
        tem.pop();
        if(!tem.empty()){
            a=tem.front();
        }else{
            break;
        }
    }
    
    for(int i=0;i<b->vertexnum;i++){ //fei
        if(b->visited[i]!=-1){
            bfs(i,b);
        }
    }
}

int main(){
    AdjList *test=new AdjList();
    dfs(0,test);
    cout<<endl;
    bfs(0,test);
    return 0;
}
