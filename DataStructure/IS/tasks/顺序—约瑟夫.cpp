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
		cout<<"�����ڣ�";
		return ;
	}
	if(L->length>=MAXSIZE){
		cout<<"�������";
	return ;
	}
}
 

PSeqList Init_SeqList(){
	PSeqList L=new SeqList;

	cout<<"����Լɪ�򻷵�����:";
	cin>>L->length;
 
	cout<<"����������";
	for(int i=0;i<L->length;i++){
		cin>>L->data[i];
	}
 
	return L;
}

 

void Delete_SeqList(PSeqList L,int i){
	
	panduan(L);//�ж����Ա��Ƿ�Ϊ��
	
	if(i<1 || i>L->length+1){
		cout<<"ɾ��ʧ�ܣ�";
		return;
	}

	int j=i-1;
	for(j=i-1;j<L->length;j++){
		L->data[j]=L->data[j+1];//ɾ����iλ��
	}

	L->length--;//���ȼ�һ
}
 

//sλ�ÿ�ʼ,ɾ����mλ
void yue_SeqList(PSeqList L,int s,int m){
	panduan(L);	
	int j=1;
	int s1=s-1;
	
	cout<<"\n���Լɪ�����У�\n";

	int i=L->length;
	for( i=L->length;i>0;i--){
		s1=(s1+m-1)%i;
		cout<<"��"<<j<<"�����е����ǣ�"<<L->data[s1]<<endl;
		Delete_SeqList(L,s1+1);
		j++;
	}
}	 



int main(){

 
	PSeqList L=Init_SeqList();
	int s;
	int m;
	cout<<"������Լɪ�򻷵���ʼ���s�ͼ���ֵm��ֵ�ֱ��ǣ�";
	cin>>s>>m;
	yue_SeqList(L,s,m);
 
	return 0;
 
	}


