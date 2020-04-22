 #include <iostream>
 using namespace std;
 int main ()
 {
     int i,k,a,b,c;
     cin>>k;
     for(i=100;i<=k;i++)
     {a=i/100;
     b=i%10;
     c=i/10%10;
     if(a*a*a+b*b*b+c*c*c==i)
     {cout<<i<<" ";}}
     return 0;
 }
     
     
