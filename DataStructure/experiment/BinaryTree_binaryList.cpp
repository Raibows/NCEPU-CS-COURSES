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
    cout<<"���������������ݣ����������ݣ����������ݣ�������Ϊ�գ�������0"<<endl;
    T temp;
    cout<<"��������ڵ�";
    cin>>temp;
    root=new node<T>(temp);
    help_init(root);
    cout<<"created successfully!"<<endl;
} 
template<class T>void tree<T>::help_init(node<T> *point){
    T ltemp,rtemp;
    //cout<<"������ڵ�ֵΪ"<<point->data<<"��������";
    cin>>ltemp;
    if(ltemp!=0){
        node<T> *ltem=new node<T>(ltemp);
        point->lchild=ltem;
        help_init(ltem);
    }else{
        //cout<<"�ڵ�ֵΪ"<<point->data<<"����������Ϊ����"<<endl;
    }
    //cout<<"������ڵ�ֵΪ"<<point->data<<"��������";
    cin>>rtemp;
    if(rtemp!=0){
        node<T> *rtem=new node<T>(rtemp);
        point->rchild=rtem;
        help_init(rtem);
    }else{
        //cout<<"�ڵ�ֵΪ"<<point->data<<"����������Ϊ����"<<endl;
    }   
}
template<class T>void tree<T>::traverse(){
    //preorder traverse
    cout<<"���������";
    preorder(root);
    //inorder traverse
    cout<<endl<<"���������";
    inorder(root);
    //postorder traverse
    cout<<endl<<"���������";
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