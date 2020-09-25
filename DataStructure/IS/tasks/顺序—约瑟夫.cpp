#include<iostream>
#include<malloc.h>
#define MAXSIZE 100
using namespace std;

typedef struct SeqList{
	int data[MAXSIZE];
	int length; 
}* PSeqList;

 

void panduan(PSeqList L){
	if(!L){
		cout<<"表不存在！";
		return ;
	}
	if(L->length>=MAXSIZE){
		cout<<"表溢出！";
	return ;
	}
}
 

PSeqList Init_SeqList(){
	PSeqList L=new SeqList;

	cout<<"输入约瑟夫环的人数:";
	cin>>L->length;
 
	cout<<"输入人名：";
	for(int i=0;i<L->length;i++){
		cin>>L->data[i];
	}
 
	return L;
}

 

void Delete_SeqList(PSeqList L,int i){
	
	panduan(L);//判断线性表是否为空
	
	if(i<1 || i>L->length+1){
		cout<<"删除失败！";
		return;
	}

	int j=i-1;
	for(j=i-1;j<L->length;j++){
		L->data[j]=L->data[j+1];//删除了i位置
	}

	L->length--;//长度减一
}
 

//s位置开始,删除第m位
void yue_SeqList(PSeqList L,int s,int m){
	panduan(L);	
	int j=1;
	int s1=s-1;
	
	cout<<"\n输出约瑟夫序列：\n";

	int i=L->length;
	for( i=L->length;i>0;i--){
		s1=(s1+m-1)%i;
		cout<<"第"<<j<<"个出列的人是："<<L->data[s1]<<endl;
		Delete_SeqList(L,s1+1);
		j++;
	}
}	 



int main(){

 
	PSeqList L=Init_SeqList();
	int s;
	int m;
	cout<<"请输入约瑟夫环的起始序号s和计数值m的值分别是：";
	cin>>s>>m;
	yue_SeqList(L,s,m);
 
	return 0;
 
	}


