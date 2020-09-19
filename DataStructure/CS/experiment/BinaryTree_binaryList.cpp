//BINARY TREE
//storage in binary list
#include<iostream>
using namespace std;

//node 
template <class N>class node{
public:
    node(N a);
    N data;
    node *lchild;
    node *rchild;
};
template<class N> node<N>::node(N a){
    data=a;
    lchild=NULL;
    rchild=NULL;
}

//tree
template<class T>class tree{
public:
    tree();
    ~tree();
    void traverse();
    void preorder(node<T> *point);
    void inorder(node<T> *point);
    void postorder(node<T> *point);
    void help_init(node<T> *point);
    node<T> *root;
};
template<class T>tree<T>::tree(){
    cout<<"请依次输入结点数据，左子树数据，右子树数据，若子树为空，请输入0"<<endl;
    T temp;
    cout<<"请输入根节点";
    cin>>temp;
    root=new node<T>(temp);
    help_init(root);
    cout<<"created successfully!"<<endl;
} 
template<class T>void tree<T>::help_init(node<T> *point){
    T ltemp,rtemp;
    //cout<<"请输入节点值为"<<point->data<<"的左子树";
    cin>>ltemp;
    if(ltemp!=0){
        node<T> *ltem=new node<T>(ltemp);
        point->lchild=ltem;
        help_init(ltem);
    }else{
        //cout<<"节点值为"<<point->data<<"的左子树将为空树"<<endl;
    }
    //cout<<"请输入节点值为"<<point->data<<"的右子树";
    cin>>rtemp;
    if(rtemp!=0){
        node<T> *rtem=new node<T>(rtemp);
        point->rchild=rtem;
        help_init(rtem);
    }else{
        //cout<<"节点值为"<<point->data<<"的右子树将为空树"<<endl;
    }   
}
template<class T>void tree<T>::traverse(){
    //preorder traverse
    cout<<"先序遍历：";
    preorder(root);
    //inorder traverse
    cout<<endl<<"中序遍历：";
    inorder(root);
    //postorder traverse
    cout<<endl<<"后序遍历：";
    postorder(root);
}
template<class T>void tree<T>::preorder(node<T> *point){
    if(point!=NULL){
        cout<<point->data<<" ";
        preorder(point->lchild);
        preorder(point->rchild);
    }
}
template<class T>void tree<T>::inorder(node<T> *point){
    if(point!=NULL){
        inorder(point->lchild);
        cout<<point->data<<" ";
        inorder(point->rchild);
    }
}
template<class T>void tree<T>::postorder(node<T> *point){
    if(point!=NULL){
        postorder(point->lchild);
        postorder(point->rchild);
        cout<<point->data<<" ";
    }
}


//below is main function
int main(){
    tree<int> *testtree=new tree<int>();
    testtree->traverse();
    return 0;
}