#include <iostream>
using namespace std;
/*
用分治求树高
*/
template <class T>
struct Node{
    T data;
    Node <T> *l,*r;
};

template <class T>
int getHeight(Node <T> *root){
    if(root==NULL){
        return 0;
    }else
    {
        Node <T> *lt=root->l;
        Node <T> *rt=root->r;
        int lh=getHeight(lt);
        int rh=getHeight(rt);
        return 1+(lh>rh?lh:rh);
    }
    
}



int main(void){

}