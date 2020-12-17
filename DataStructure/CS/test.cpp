# include<iostream>
# include<fstream>
# include<cstring>
# include<cstdlib>//system()
# define maxnum 50 //后台定义最大设备数量为50
using namespace std;

//类的声明
class menu;
class Product;
class graphical;

class graphical//图形类
{
public:
    void in();//进入系统图形
    void out();//退出系统图形
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
    cout<<"拜拜 欢迎下次再来玩"<<endl;
    cout<<"系统由台湾高山族第一美男子黄广独立完成"<<endl;
}
void graphical::in()
{
    cout<<"----------Dragon be here!----------"<<endl;
    cout<<"  ┏┓　　　┏┓"<<endl;
    cout<<"┏┛┻━━━┛┻┓"<<endl;
    cout<<"┃　　　　　　　┃"<<endl;
    cout<<"┃  ■        ■┃"<<endl;
    cout<<"┃　　          ┃"<<endl;
    cout<<"┃　　　        ┃"<<endl;
    cout<<"┃       ◎  　 ┃"<<endl;
    cout<<"┃　　　　　　　┃"<<endl;
    cout<<"┗━┓　　　┏━┛"<<endl;
    cout<<"　　┃　　　┃神兽保佑"<<endl;
    cout<<"　　┃　　　┃代码无BUG！"<<endl;
    cout<<"　　┃　　　┗━━━┓"<<endl;
    cout<<"　　┃　　　　　　　┣┓"<<endl;
    cout<<" 　 ┃　　　　　　　┏┛"<<endl;
    cout<<"　　┗┓┓┏━┳┓┏┛"<<endl;
    cout<<"　　　┃┫┫　┃┫┫"<<endl;
    cout<<"　　　┗┻┛　┗┻┛"<<endl;
    cout<<"━━━━━━神兽出没━━━━━━"<<endl;
}


class Product  //产品类
{
public:
    int ID;  //编号
    int PRICE;  //价格
    int NUM;  //库存数量
    string TYPE;  //类别  为三种 TV（电视） DVD DT（带DVD的电视）
    string NAME;  //名称  如 康佳电视机 美的电视机
    //五个获取信息的成员函数
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
    void headdisplay();//显示南阳公司信息
    void error();//显示错误信息（因为无产品）
};
void Product::headdisplay()
{
    cout<<"★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★"<<endl;
    cout<<"★★★★★★★★★★★★★★欢迎来到南阳康佳公司★★★★★★★★★★★★★★★★"<<endl;
    cout<<"★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★"<<endl;
    cout<<"★★★★★★★★★★           当你看到这个界面          ★★★★★★★★★★★"<<endl;
    cout<<"★★★★★★★★★★★★★★      就代表你      ★★★★★★★★★★★★★★★★"<<endl;
    cout<<"★★★★★★★★★★★★★      已经成为一名      ★★★★★★★★★★★★★★★"<<endl;
    cout<<"★★★★★★★★★★★★       康佳产品搬运工       ★★★★★★★★★★★★★★"<<endl;
    cout<<"★★★★★★★★★★★            恭喜恭喜            ★★★★★★★★★★★★★"<<endl;
}
void Product::error()
{
    cout<<"错误！！没有产品信息"<<endl;
    cout<<"自动返回主菜单"<<endl<<endl;
}


//全局定义产品信息组
int count=0;
Product pro[maxnum];
//全局定义图形类对象
graphical b;


class menu: public Product//菜单类继承产品类
{
public:
    void Display();//显示菜单信息
    void use();//操控菜单
    void Add();//添加
    void Find();//查找
    void Delete();//删除
    void Modify();//修改
    void display();//显示产品信息
    void Storage();//自动储存产品信息
    void storage();//手动储存产品信息（欺骗用户）因为每一个操作之后都会自动储存 所以无需手动
    void Empty();//清空产品日记信息
};
void menu::Display()
{
    cout<<"***欢迎使用设备管理系统***"<<endl;
    cout<<"   ***1.添加设备信息***"<<endl;
    cout<<"   ***2.查找设备信息***"<<endl;
    cout<<"   ***3.删除设备信息***"<<endl;
    cout<<"   ***4.修改设备信息***"<<endl;
    cout<<"   ***5.输出设备信息***"<<endl;
    cout<<"   ***6.储存设备信息***"<<endl;
    cout<<"   ***7.一键清空信息***"<<endl;
    cout<<"   ***0.退出管理系统***"<<endl;
    cout<<"请选择所需要的功能：";
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
            Storage();//自动储存
            Display();
            break;
        case 2:
            Find();
            Display();
            break;
        case 3:
            Delete();
            Storage();//自动储存
            Display();
            break;
        case 4:
            Modify();
            Storage();//自动储存
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
            Storage();//自动储存
            b.out();
            exit(0);
            break;
        default:
            cout<<"选择错误！！请重新选择！！"<<endl;
            cout<<"请选择所需要的功能：";
        }
    }
}
void menu :: Add()
{
    system("cls");
    int _id,_price,_num=1;
    string _type,_name;
//    记录类别信息
    cout<<"请选择添加的设备类别（1-3）："<<endl;
    cout<<"1.电视机(TV)   2.DVD(DVD)  3.带DVD的电视机(DT)"<<endl;
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
            cout<<"输入有误！！请重新选择！！"<<endl;
        }
        if(i==1||i==2||i==3)//防止用户非法输入
            break;
    }
//    记录名称信息
    cout<<"请输入设备名称："<<endl;
    cin>>_name;
    pro[count].getNAME(_name);
    // 记录编号信息
    cout<<"请输入设备编号（四位数，以“1”开头,如“1000”）"<<endl;
    cin>>_id;
    pro[count].getID(_id);
    //记录价格信息
    cout<<"请输入价格（1-9999）："<<endl;
    cin>>_price;
    pro[count].getPRICE(_price);
    //记录库存信息
    pro[count].getNUM(_num);
    count++;
}
void menu::Delete()
{
    system("cls");
    if(count==0)
    {
        error();//输出无产品信息
        return ;//如果没有产品则终止删除函数
    }
    cout<<"欢迎使用删除功能，产品信息如下："<<endl;
    display();//显示产品信息
    cout<<"请输入想删除的产品的编号:";
    int bian,d,i;
    while(cin>>bian)
    {
        for(i=0; i<count; i++)
        {
            if(pro[i].ID==bian)//如果编号存在
            {
                cout<<"请问您是否确认删除编号为"<<pro[i].ID<<"的产品？"<<endl;
                cout<<"1.是 2.否"<<endl;
                cin>>d;
                if(d==1)//确认删除
                {
                    if(i==count-1)//如果是最后一个 无需前移
                        count--;
                    else//如果不是最后一个 则后续产品前移
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
                            if(i==count)//前移完毕后跳出while循环
                                break;
                        }
                    }
                    cout<<"删除成功！！"<<endl;
                    return;//删除成功后 直接终止删除函数
                }
                else//否认删除 自动返回主菜单
                {
                    return ;
                }
            }
        }
        if(i==count)//如果编号不存在
            cout<<"您输入的编号有误，请重新输入"<<endl;
    }
}
void menu::Find()
{
    system("cls");
    if(count==0)
    {
        error();//输出无产品信息
        return ;//如果没有产品则终止查找函数
    }
    cout<<"欢迎使用查找功能，请选择查找方式："<<endl;
    cout<<"1.编号 2.名称 "<<endl;
    int c;
    string s_name;
    int bian,i;
    while(cin>>c)
    {
        if(c==1)//如果选择编号
        {
            cout<<"请输入编号:";
            while(cin>>bian)
            {
                for(i=0; i<count; i++)
                {
                    if(pro[i].ID==bian)//如果编号存在
                    {
                        cout<<"您所输入编号的设备的信息如下："<<endl;
                        cout<<"                          "<<endl;
                        cout<<"编号："<<pro[i].ID;
                        cout<<"   类别:"<<pro[i].TYPE;
                        cout<<"   名称："<<pro[i].NAME;
                        cout<<"   价格："<<pro[i].PRICE;
                        cout<<"   库存数量："<<pro[i].NUM<<endl;
                        cout<<"                          "<<endl;
                        return ;
                    }
                }
                if(i==count)//如果编号不存在
                {
                    cout<<"您输入的编号有误，请选择"<<endl;
                    cout<<"1.继续查找 2.结束查找"<<endl;
                    int ss;
                    while(cin>>ss)
                    {
                        if(ss==1)
                        {
                            cout<<"请输入编号:";
                            break;//跳出之后返回
                        }
                        else if(ss==2)
                            return ;//结束查找
                        else
                            cout<<"选择错误，请重新选择"<<endl;
                    }
                }
            }
        }
        if(c==2)//如果选择名称
        {
            cout<<"请输入名称:";
            while(cin>>s_name)
            {
                for(i=0; i<count; i++)
                {
                    if(pro[i].NAME==s_name)//如果编号存在
                    {
                        cout<<"您所输入名称的设备的信息如下："<<endl;
                        cout<<"                          "<<endl;
                        cout<<"编号："<<pro[i].ID;
                        cout<<"   类别:"<<pro[i].TYPE;
                        cout<<"   名称："<<pro[i].NAME;
                        cout<<"   价格："<<pro[i].PRICE;
                        cout<<"   库存数量："<<pro[i].NUM<<endl;
                        cout<<"                          "<<endl;
                        return ;
                    }
                }
                if(i==count)//如果编号不存在
                {
                    cout<<"您输入的名称有误，请选择"<<endl;
                    cout<<"1.继续查找 2.结束查找"<<endl;
                    int ss;
                    while(cin>>ss)
                    {
                        if(ss==1)
                        {
                            cout<<"请输入名称:";
                            break;//跳出之后返回
                        }
                        else if(ss==2)
                            return ;//终止要求
                        else
                            cout<<"选择错误，请重新选择"<<endl;
                    }
                }
            }
        }
        else
            cout<<"选择错误，请重新选择"<<endl;
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
            cout<<endl<<"编号："<<pro[i].ID;
            cout<<"   类别:"<<pro[i].TYPE;
            cout<<"   名称："<<pro[i].NAME;
            cout<<"   价格："<<pro[i].PRICE;
            cout<<"   库存数量："<<pro[i].NUM<<endl;
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
        return ;//如果没有产品则终止查找函数
    }
    cout<<"欢迎使用修改功能，产品信息如下："<<endl;
    display();
    cout<<"请输入想修改的产品的编号:";
    int bian,d,i;
    string s_name;
    int s_price,s_num;
    while(cin>>bian)
    {
        for(i=0; i<count; i++)
        {
            if(pro[i].ID==bian)//如果编号存在
            {
                cout<<"请输入想要修改的内容："<<endl;
                cout<<"1.名字 2.价格 3.库存数量"<<endl;
                while(cin>>d)//输入选项 如非法输入则重新输入
                {
                    switch(d)
                    {
                    case 1:
                        cout<<"请输入新的名字：";
                        cin>>s_name;
                        pro[i].getNAME(s_name);
                        cout<<endl<<"修改成功，自动返回主菜单"<<endl;
                        return ;
                    case 2:
                        cout<<"请输入新的价格：";
                        cin>>s_price;
                        pro[i].getPRICE(s_price);
                        cout<<endl<<"修改成功，自动返回主菜单"<<endl;
                        return ;
                    case 3:
                        cout<<"请输入新的库存数量：";
                        cin>>s_num;
                        pro[i].getNUM(s_num);
                        cout<<endl<<"修改成功，自动返回主菜单"<<endl;
                        return ;
                    }
                    cout<<"选择错误，请重新选择"<<endl;
                }
            }
        }
        if(i==count)//如果编号不存在
            cout<<"您输入的编号有误，请重新输入"<<endl;
    }
}
void menu::Storage()
{
    ofstream ofs;
    int i;
    ofs.open("C:\\information.txt",ios::out|ios::trunc);
    if(ofs)//判断是否打开成功
    {
        for(i=0; i<count; i++)
        {
            ofs<<endl<<"编号："<<pro[i].ID;
            ofs<<"   类别:"<<pro[i].TYPE;
            ofs<<"   名称："<<pro[i].NAME;
            ofs<<"   价格："<<pro[i].PRICE;
            ofs<<"   库存数量："<<pro[i].NUM<<endl;
            ofs<<endl;
        }
    }
    ofs.close();
}
void menu::storage()
{
    system("cls");
    cout<<"储存成功，信息已存在c盘的information.txt下"<<endl<<endl;
}
void menu::Empty()
{
    cout<<"请问是否确认清空信息"<<endl;
    cout<<"1.是 2.否"<<endl;
    int d;
    while(cin>>d)
    {
        if(d==1)
        {
            count=0;
            cout<<"清空成功，自动返回主菜单"<<endl;
            return ;
        }
        else if(d==2)
            return ;
        else
            cout<<"选择错误！！ 请重新选择"<<endl;
    }
}


int main(void)
{
    system("color 3E");//设置颜色
   //定义菜单类的对象
    menu a;

    b.in();//调用图形类的进入系统图形函数
    cout<<"请用你洁白的小手轻轻点击一下回车键"<<endl;
    getchar();
    system("cls");

    a.headdisplay();//调用菜单类继承产品类的显示公司函数
    a.Display();//调用菜单类的显示菜单函数
    a.use();//使用系统
    return 0;
}