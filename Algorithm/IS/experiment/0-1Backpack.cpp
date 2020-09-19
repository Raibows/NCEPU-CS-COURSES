#include <iostream>
#include<cstdio>
#define N 100
#define MAX(a,b) a < b ? b : a
using namespace std;

struct goods{
int wight;//��Ʒ����
int value;//��Ʒ��ֵ
};

int n,C;//��Ʒ��������������
int X[N];//���մ洢״̬
struct goods goods[N];

int KnapSack(int n,struct goods a[],int C,int x[]){
    int V[N][10*N];
    for(int m = 0; m <= n; m++)//��ʼ����0��
        V[m][0] = 0;
    for(int l = 0; l <= C; l++)//��ʼ����0��
        V[0][l] = 0;
    for(int k = 1; k <= n; k++)
        for(int j = 1; j <= C; j++)
        if(j < a[k-1].wight)
            V[k][j] = V[k-1][j];
        else
            V[k][j] = MAX(V[k-1][j],V[k-1][j-a[k-1].wight] + a[k-1].value);

    for(int i = n,j = C; i > 0; i--){
        if(V[i][j] > V[i-1][j]){
            x[i-1] = 1;
            j = j - a[i-1].wight;
        }
        else
            x[i-1] = 0;
    }
    return V[n][C];
}
int main()
{
    printf("��Ʒ����n��");
    scanf("%d",&n);
    printf("��������C��");
    scanf("%d",&C);
    for(int i = 0; i < n; i++){
        printf("��Ʒ%d������w[%d]�����ֵv[%d]��",i+1,i+1,i+1);
        scanf("%d%d",&goods[i].wight,&goods[i].value);
    }
    int sum2 = KnapSack(n,goods,C,X);
     printf("��̬�滮�����0/1��������:\nX=[");
     for(int j = 0; j < n; j++)
        cout<<X[j]<<" ";//�������X[n]����
     printf("]   װ���ܼ�ֵ%d\n", sum2);
     return 0;
}
