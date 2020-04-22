#include <iostream>
using namespace std;
int main()
{
    char a;
    int b;
    cin>>a;
    if(a>=97&&a<123)
    {
     a=a-32;
     cout<<a<<endl;

     
    }
    else if(a<=90&&a>=65)
    {
        a=a+32;
        cout<<a<<endl;

    }
    
    else if(a>=48&&a<=57)
    {  b=a-'0';
      cout<<b*b<<endl;
    
    }
    else
    {cout<<a<<endl;}
    return 0;
}
    

