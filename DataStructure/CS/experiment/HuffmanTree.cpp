#include<iostream>
using namespace std;
class Node{
public:
    int weight;
    int lchild;
    int rchild;
    int parent;
};
class HuffmanTree{
public:
    int n;
    int m;
    int hufnum;
    Node *huf;
    Node *select;
    void sort(Node a[],int b);
    void move(int a,int temsum);
    void newtree();
    void show();
    void init();
    int find(int a);
    int finds(int a);
    HuffmanTree();
};
void HuffmanTree::sort(Node a[],int b){
    for(int i=0;i<b-1;i++){
        for(int j=0;j<b-i-1;j++){
            if(a[j].weight>a[j+1].weight){
                int x=a[j+1].weight;
                a[j+1].weight=a[j].weight;
                a[j].weight=x;
            }
        }
    }
}
void HuffmanTree::move(int a,int temsum){
    for(int i=2;i<a;i++){
        select[-2+i].weight=select[i].weight;
    }
    select[a-2].weight=temsum;
}
void HuffmanTree::newtree(){
            int c=select[0].weight+select[1].weight;
            huf[hufnum].weight=select[0].weight;
            huf[hufnum].parent=hufnum+2;
            hufnum++;
            huf[hufnum].weight=select[1].weight;
            huf[hufnum].parent=hufnum+1;
            hufnum++;
            huf[hufnum].weight=c;
            huf[hufnum].lchild=hufnum-2;
            huf[hufnum].rchild=hufnum-1;    
}
int HuffmanTree::find(int a){
    for(int i=0;i<hufnum;i++){
        if((huf[i].weight==a)&&(huf[i].parent==-2)){
            return i;
        }
    }
    return -1;
}
void HuffmanTree::show(){
    cout<<"local"<<" "<<"weight"<<" "<<"parent"<<" "<<"lchild"<<" "<<"rchild"<<endl;
    for(int i=0;i<m;i++){
        cout<<i<<"      "<<huf[i].weight<<"      "<<huf[i].parent<<"      "<<huf[i].lchild<<"      "<<huf[i].rchild<<endl;
    }
}
void HuffmanTree::init(){
    for(int i=0;i<n;i++){
        select[i].lchild=-1;
        select[i].rchild=-1;
        select[i].parent=-1;
        select[i].weight=-1;
    }
    for(int i=0;i<m;i++){
        huf[i].lchild=-1;
        huf[i].rchild=-1;
        huf[i].parent=-1;
        huf[i].weight=-1;
    }
}
HuffmanTree::HuffmanTree(){
    hufnum=0;
    cin>>n;
    m=2*n-1;
    huf=new Node[m];
    select=new Node[n];
    init();
    for(int i=0;i<n;i++){
        cin>>select[i].weight;
    }   
    for(int i=0;i<(n-1)&&hufnum<m;i++){
        sort(select,n-i);
        int temsum=0;
        if((n-i)==1){
            cout<<"wrong in line 35"<<endl;
            //huf[hufnum].weight=temsum;
            //hufnum++;
        }else{
            temsum=select[0].weight+select[1].weight;
            huf[hufnum].weight=temsum;
            huf[hufnum].parent=-2;
            int tem2=hufnum;
            hufnum++;
            int tem0=find(select[0].weight);
            if(tem0!=-1){
                huf[tem0].parent=tem2;
                huf[tem2].lchild=tem0;
            }else{
                huf[hufnum].weight=select[0].weight;
                huf[hufnum].parent=tem2;
                huf[tem2].lchild=hufnum;
                hufnum++;
            }
            int tem1=find(select[1].weight);
            if(tem1!=-1){
                huf[tem1].parent=tem2;
                huf[tem2].rchild=tem1;
            }else{
                huf[hufnum].weight=select[1].weight;
                huf[hufnum].parent=tem2;
                huf[tem2].rchild=hufnum;
                hufnum++;
            }
            //newtree();
        }
        move(n-i,temsum);
    }
}
void calculate(HuffmanTree *a){
    int tem=-1;
    int sum=0;
    for(int i=0;i<a->m;i++){
        tem=-1;
        if(a->huf[i].lchild==-1&&a->huf[i].rchild==-1){
            tem=a->huf[i].parent;
            int branch=0;
            while(tem>=0){
                branch++;
                tem=a->huf[tem].parent;
            }
            sum=sum+branch*a->huf[i].weight;
        }
    }
    cout<<sum<<endl;
}

int main(){
    HuffmanTree *testtest=new HuffmanTree();
    testtest->show();   //show the detail of the tree
    calculate(testtest);   //get the  PL
    return 0;
}