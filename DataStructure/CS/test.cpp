# include<iostream>
# include<fstream>
# include<cstring>
# include<cstdlib>//system()
# define maxnum 50 //��̨��������豸����Ϊ50
using namespace std;

//�������
class menu;
class Product;
class graphical;

class graphical//ͼ����
{
public:
    void in();//����ϵͳͼ��
    void out();//�˳�ϵͳͼ��
};
void graphical::out()
{
    int a[15][37]= {0};
    int i,j;
    a[0][18]=1;
    for(j=17; j<20; j++) a[1][j]=1;
    for(j=16; j<21; j++) a[2][j]=1;
    for(j=15; j<22; j++) a[3][j]=1;
    for(j=14; j<23; j++) a[4][j]=1;
    for(j=1; j<36; j++) a[5][j]=1;
    for(j=4; j<33; j++) a[6][j]=1;
    for(j=7; j<30; j++) a[7][j]=1;
    for(j=10; j<27; j++) a[8][j]=1;
    for(j=12; j<25; j++) a[9][j]=1;
    for(j=11; j<26; j++) a[10][j]=1;
    for(j=10; j<18; j++) a[11][j]=1;
    for(j=19; j<27; j++) a[11][j]=1;
    for(j=9; j<15; j++) a[12][j]=1;
    for(j=22; j<28; j++) a[12][j]=1;
    for(j=8; j<12; j++) a[13][j]=1;
    for(j=25; j<29; j++) a[13][j]=1;
    for(j=7; j<9; j++) a[14][j]=1;
    for(j=28; j<30; j++) a[14][j]=1;
    a[15][6]=1,a[15][31]=1;
    for(i=0; i<15; i++)
    {
        for(j=0; j<37; j++)
            if(a[i][j]==1)
                cout<<"*";
            else
                cout<<" ";
        cout<<endl;
    }
    cout<<"�ݰ� ��ӭ�´�������"<<endl;
    cout<<"ϵͳ��̨���ɽ���һ�����ӻƹ�������"<<endl;
}
void graphical::in()
{
    cout<<"----------Dragon be here!----------"<<endl;
    cout<<"  ��������������"<<endl;
    cout<<"�����ߩ��������ߩ�"<<endl;
    cout<<"������������������"<<endl;
    cout<<"��  ��        ����"<<endl;
    cout<<"������          ��"<<endl;
    cout<<"��������        ��"<<endl;
    cout<<"��       ��  �� ��"<<endl;
    cout<<"������������������"<<endl;
    cout<<"������������������"<<endl;
    cout<<"�����������������ޱ���"<<endl;
    cout<<"��������������������BUG��"<<endl;
    cout<<"����������������������"<<endl;
    cout<<"���������������������ǩ�"<<endl;
    cout<<" �� ��������������������"<<endl;
    cout<<"���������������ש�����"<<endl;
    cout<<"���������ϩϡ����ϩ�"<<endl;
    cout<<"���������ߩ������ߩ�"<<endl;
    cout<<"���������������޳�û������������"<<endl;
}


class Product  //��Ʒ��
{
public:
    int ID;  //���
    int PRICE;  //�۸�
    int NUM;  //�������
    string TYPE;  //���  Ϊ���� TV�����ӣ� DVD DT����DVD�ĵ��ӣ�
    string NAME;  //����  �� ���ѵ��ӻ� ���ĵ��ӻ�
    //�����ȡ��Ϣ�ĳ�Ա����
    void getID(int & id)
    {
        ID=id;
    }
    void getPRICE(int & price)
    {
        PRICE=price;
    }
    void getNUM(int & num)
    {
        NUM=num;
    }
    void getTYPE(string & type)
    {
        TYPE=type;
    }
    void getNAME(string & name)
    {
        NAME=name;
    }
    void headdisplay();//��ʾ������˾��Ϣ
    void error();//��ʾ������Ϣ����Ϊ�޲�Ʒ��
};
void Product::headdisplay()
{
    cout<<"�����������������������������������������"<<endl;
    cout<<"��������������ﻶӭ�����������ѹ�˾�����������������"<<endl;
    cout<<"�����������������������������������������"<<endl;
    cout<<"�����������           ���㿴���������          ������������"<<endl;
    cout<<"���������������      �ʹ�����      �����������������"<<endl;
    cout<<"��������������      �Ѿ���Ϊһ��      ����������������"<<endl;
    cout<<"�������������       ���Ѳ�Ʒ���˹�       ���������������"<<endl;
    cout<<"������������            ��ϲ��ϲ            ��������������"<<endl;
}
void Product::error()
{
    cout<<"���󣡣�û�в�Ʒ��Ϣ"<<endl;
    cout<<"�Զ��������˵�"<<endl<<endl;
}


//ȫ�ֶ����Ʒ��Ϣ��
int count=0;
Product pro[maxnum];
//ȫ�ֶ���ͼ�������
graphical b;


class menu: public Product//�˵���̳в�Ʒ��
{
public:
    void Display();//��ʾ�˵���Ϣ
    void use();//�ٿز˵�
    void Add();//���
    void Find();//����
    void Delete();//ɾ��
    void Modify();//�޸�
    void display();//��ʾ��Ʒ��Ϣ
    void Storage();//�Զ������Ʒ��Ϣ
    void storage();//�ֶ������Ʒ��Ϣ����ƭ�û�����Ϊÿһ������֮�󶼻��Զ����� ���������ֶ�
    void Empty();//��ղ�Ʒ�ռ���Ϣ
};
void menu::Display()
{
    cout<<"***��ӭʹ���豸����ϵͳ***"<<endl;
    cout<<"   ***1.����豸��Ϣ***"<<endl;
    cout<<"   ***2.�����豸��Ϣ***"<<endl;
    cout<<"   ***3.ɾ���豸��Ϣ***"<<endl;
    cout<<"   ***4.�޸��豸��Ϣ***"<<endl;
    cout<<"   ***5.����豸��Ϣ***"<<endl;
    cout<<"   ***6.�����豸��Ϣ***"<<endl;
    cout<<"   ***7.һ�������Ϣ***"<<endl;
    cout<<"   ***0.�˳�����ϵͳ***"<<endl;
    cout<<"��ѡ������Ҫ�Ĺ��ܣ�";
}
void menu::use()
{
    int i;
    while(cin>>i)
    {
        switch(i)
        {
        case 1:
            Add();
            system("cls");
            Storage();//�Զ�����
            Display();
            break;
        case 2:
            Find();
            Display();
            break;
        case 3:
            Delete();
            Storage();//�Զ�����
            Display();
            break;
        case 4:
            Modify();
            Storage();//�Զ�����
            Display();
            break;
        case 5:
            display();
            Display();
            break;
        case 6:
            storage();
            Display();
            break;
        case 7:
            Empty();
            Display();
            break;
        case 0:
            Storage();//�Զ�����
            b.out();
            exit(0);
            break;
        default:
            cout<<"ѡ����󣡣�������ѡ�񣡣�"<<endl;
            cout<<"��ѡ������Ҫ�Ĺ��ܣ�";
        }
    }
}
void menu :: Add()
{
    system("cls");
    int _id,_price,_num=1;
    string _type,_name;
//    ��¼�����Ϣ
    cout<<"��ѡ����ӵ��豸���1-3����"<<endl;
    cout<<"1.���ӻ�(TV)   2.DVD(DVD)  3.��DVD�ĵ��ӻ�(DT)"<<endl;
    int i;
    while(cin>>i)
    {
        switch(i)
        {
        case 1:
            _type="TV";
            pro[count].getTYPE(_type);
            break;
        case 2:
            _type="DVD";
            pro[count].getTYPE(_type);
            break;
        case 3:
            _type="DT";
            pro[count].getTYPE(_type);
            break;
        default:
            cout<<"�������󣡣�������ѡ�񣡣�"<<endl;
        }
        if(i==1||i==2||i==3)//��ֹ�û��Ƿ�����
            break;
    }
//    ��¼������Ϣ
    cout<<"�������豸���ƣ�"<<endl;
    cin>>_name;
    pro[count].getNAME(_name);
    // ��¼�����Ϣ
    cout<<"�������豸��ţ���λ�����ԡ�1����ͷ,�硰1000����"<<endl;
    cin>>_id;
    pro[count].getID(_id);
    //��¼�۸���Ϣ
    cout<<"������۸�1-9999����"<<endl;
    cin>>_price;
    pro[count].getPRICE(_price);
    //��¼�����Ϣ
    pro[count].getNUM(_num);
    count++;
}
void menu::Delete()
{
    system("cls");
    if(count==0)
    {
        error();//����޲�Ʒ��Ϣ
        return ;//���û�в�Ʒ����ֹɾ������
    }
    cout<<"��ӭʹ��ɾ�����ܣ���Ʒ��Ϣ���£�"<<endl;
    display();//��ʾ��Ʒ��Ϣ
    cout<<"��������ɾ���Ĳ�Ʒ�ı��:";
    int bian,d,i;
    while(cin>>bian)
    {
        for(i=0; i<count; i++)
        {
            if(pro[i].ID==bian)//�����Ŵ���
            {
                cout<<"�������Ƿ�ȷ��ɾ�����Ϊ"<<pro[i].ID<<"�Ĳ�Ʒ��"<<endl;
                cout<<"1.�� 2.��"<<endl;
                cin>>d;
                if(d==1)//ȷ��ɾ��
                {
                    if(i==count-1)//��������һ�� ����ǰ��
                        count--;
                    else//����������һ�� �������Ʒǰ��
                    {
                        while(1)
                        {
                            pro[i].ID=pro[i+1].ID;
                            pro[i].TYPE=pro[i+1].TYPE;
                            pro[i].NAME=pro[i+1].NAME;
                            pro[i].PRICE=pro[i+1].PRICE;
                            pro[i].NUM =pro[i+1].NUM;
                            count--;
                            i++;
                            if(i==count)//ǰ����Ϻ�����whileѭ��
                                break;
                        }
                    }
                    cout<<"ɾ���ɹ�����"<<endl;
                    return;//ɾ���ɹ��� ֱ����ֹɾ������
                }
                else//����ɾ�� �Զ��������˵�
                {
                    return ;
                }
            }
        }
        if(i==count)//�����Ų�����
            cout<<"������ı����������������"<<endl;
    }
}
void menu::Find()
{
    system("cls");
    if(count==0)
    {
        error();//����޲�Ʒ��Ϣ
        return ;//���û�в�Ʒ����ֹ���Һ���
    }
    cout<<"��ӭʹ�ò��ҹ��ܣ���ѡ����ҷ�ʽ��"<<endl;
    cout<<"1.��� 2.���� "<<endl;
    int c;
    string s_name;
    int bian,i;
    while(cin>>c)
    {
        if(c==1)//���ѡ����
        {
            cout<<"��������:";
            while(cin>>bian)
            {
                for(i=0; i<count; i++)
                {
                    if(pro[i].ID==bian)//�����Ŵ���
                    {
                        cout<<"���������ŵ��豸����Ϣ���£�"<<endl;
                        cout<<"                          "<<endl;
                        cout<<"��ţ�"<<pro[i].ID;
                        cout<<"   ���:"<<pro[i].TYPE;
                        cout<<"   ���ƣ�"<<pro[i].NAME;
                        cout<<"   �۸�"<<pro[i].PRICE;
                        cout<<"   ���������"<<pro[i].NUM<<endl;
                        cout<<"                          "<<endl;
                        return ;
                    }
                }
                if(i==count)//�����Ų�����
                {
                    cout<<"������ı��������ѡ��"<<endl;
                    cout<<"1.�������� 2.��������"<<endl;
                    int ss;
                    while(cin>>ss)
                    {
                        if(ss==1)
                        {
                            cout<<"��������:";
                            break;//����֮�󷵻�
                        }
                        else if(ss==2)
                            return ;//��������
                        else
                            cout<<"ѡ�����������ѡ��"<<endl;
                    }
                }
            }
        }
        if(c==2)//���ѡ������
        {
            cout<<"����������:";
            while(cin>>s_name)
            {
                for(i=0; i<count; i++)
                {
                    if(pro[i].NAME==s_name)//�����Ŵ���
                    {
                        cout<<"�����������Ƶ��豸����Ϣ���£�"<<endl;
                        cout<<"                          "<<endl;
                        cout<<"��ţ�"<<pro[i].ID;
                        cout<<"   ���:"<<pro[i].TYPE;
                        cout<<"   ���ƣ�"<<pro[i].NAME;
                        cout<<"   �۸�"<<pro[i].PRICE;
                        cout<<"   ���������"<<pro[i].NUM<<endl;
                        cout<<"                          "<<endl;
                        return ;
                    }
                }
                if(i==count)//�����Ų�����
                {
                    cout<<"�����������������ѡ��"<<endl;
                    cout<<"1.�������� 2.��������"<<endl;
                    int ss;
                    while(cin>>ss)
                    {
                        if(ss==1)
                        {
                            cout<<"����������:";
                            break;//����֮�󷵻�
                        }
                        else if(ss==2)
                            return ;//��ֹҪ��
                        else
                            cout<<"ѡ�����������ѡ��"<<endl;
                    }
                }
            }
        }
        else
            cout<<"ѡ�����������ѡ��"<<endl;
    }
}
void menu::display()
{
    if(count==0)
    {
        system("cls");
        error();
        return ;
    }
    else
    {
        int i;
        for(i=0; i<count; i++)
        {
            cout<<endl<<"��ţ�"<<pro[i].ID;
            cout<<"   ���:"<<pro[i].TYPE;
            cout<<"   ���ƣ�"<<pro[i].NAME;
            cout<<"   �۸�"<<pro[i].PRICE;
            cout<<"   ���������"<<pro[i].NUM<<endl;
            cout<<"                          "<<endl;
        }
    }
}
void menu::Modify()
{
    system("cls");
    if(count==0)
    {
        error();
        return ;//���û�в�Ʒ����ֹ���Һ���
    }
    cout<<"��ӭʹ���޸Ĺ��ܣ���Ʒ��Ϣ���£�"<<endl;
    display();
    cout<<"���������޸ĵĲ�Ʒ�ı��:";
    int bian,d,i;
    string s_name;
    int s_price,s_num;
    while(cin>>bian)
    {
        for(i=0; i<count; i++)
        {
            if(pro[i].ID==bian)//�����Ŵ���
            {
                cout<<"��������Ҫ�޸ĵ����ݣ�"<<endl;
                cout<<"1.���� 2.�۸� 3.�������"<<endl;
                while(cin>>d)//����ѡ�� ��Ƿ���������������
                {
                    switch(d)
                    {
                    case 1:
                        cout<<"�������µ����֣�";
                        cin>>s_name;
                        pro[i].getNAME(s_name);
                        cout<<endl<<"�޸ĳɹ����Զ��������˵�"<<endl;
                        return ;
                    case 2:
                        cout<<"�������µļ۸�";
                        cin>>s_price;
                        pro[i].getPRICE(s_price);
                        cout<<endl<<"�޸ĳɹ����Զ��������˵�"<<endl;
                        return ;
                    case 3:
                        cout<<"�������µĿ��������";
                        cin>>s_num;
                        pro[i].getNUM(s_num);
                        cout<<endl<<"�޸ĳɹ����Զ��������˵�"<<endl;
                        return ;
                    }
                    cout<<"ѡ�����������ѡ��"<<endl;
                }
            }
        }
        if(i==count)//�����Ų�����
            cout<<"������ı����������������"<<endl;
    }
}
void menu::Storage()
{
    ofstream ofs;
    int i;
    ofs.open("C:\\information.txt",ios::out|ios::trunc);
    if(ofs)//�ж��Ƿ�򿪳ɹ�
    {
        for(i=0; i<count; i++)
        {
            ofs<<endl<<"��ţ�"<<pro[i].ID;
            ofs<<"   ���:"<<pro[i].TYPE;
            ofs<<"   ���ƣ�"<<pro[i].NAME;
            ofs<<"   �۸�"<<pro[i].PRICE;
            ofs<<"   ���������"<<pro[i].NUM<<endl;
            ofs<<endl;
        }
    }
    ofs.close();
}
void menu::storage()
{
    system("cls");
    cout<<"����ɹ�����Ϣ�Ѵ���c�̵�information.txt��"<<endl<<endl;
}
void menu::Empty()
{
    cout<<"�����Ƿ�ȷ�������Ϣ"<<endl;
    cout<<"1.�� 2.��"<<endl;
    int d;
    while(cin>>d)
    {
        if(d==1)
        {
            count=0;
            cout<<"��ճɹ����Զ��������˵�"<<endl;
            return ;
        }
        else if(d==2)
            return ;
        else
            cout<<"ѡ����󣡣� ������ѡ��"<<endl;
    }
}


int main(void)
{
    system("color 3E");//������ɫ
   //����˵���Ķ���
    menu a;

    b.in();//����ͼ����Ľ���ϵͳͼ�κ���
    cout<<"�������׵�С��������һ�»س���"<<endl;
    getchar();
    system("cls");

    a.headdisplay();//���ò˵���̳в�Ʒ�����ʾ��˾����
    a.Display();//���ò˵������ʾ�˵�����
    a.use();//ʹ��ϵͳ
    return 0;
}