#include<iostream>
#include<stdio.h>
using namespace std;
int main()
{
	int a[100],n,i,j,k,b[100],c[100]={0},gs=0,cz=0,max=0,t;
	cin>>n;
	for(i=0;i<n;i++) cin>>a[i];//����n����
	for(i=0;i<n;i++)
		for(j=0;j<n-1;j++)
			if(a[j]>a[j+1])
			{ t=a[j]; a[j]=a[j+1]; a[j+1]=t;}
	//for(i=0;i<n;i++) cout<<a[i]<<" ";
	for(i=0;i<n;i++)//������a��ÿһ��Ԫ��
	{
		cz=0;//�ж��Ƿ���b�����г���
		for(j=0;j<gs;j++)
			if(a[i]==b[j])//��������˵Ļ������±�Ϊj
			{
				cz=1;//�����
				break;//������
			}
		if(cz==0)//���������
		{
			b[gs]=a[i];//��a[i]�ŵ�b������
			c[gs]++;//��Ӧ��a[i]���ֵĴ�����һ
			gs++;//b������Ԫ�ظ�����һ
		}
		else//������ڵĻ�
		{
			c[j]++;//��jΪa[i]��b������±꣬��Ӧc������Ԫ�ظ�����һ
		}
	}
	for(i=0;i<gs;i++)//c�������ҳ��ֵĴ������ֵ
		if(c[i]>max) max=c[i];

	for(i=0;i<gs;i++)
	{
		if(c[i]==max)//�����Ӧ��b�����е���
			cout<<b[i]<<" "<<max<<endl;
	}
	
}

