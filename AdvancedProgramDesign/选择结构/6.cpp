#include<iostream>
using namespace std;
int main()
{
	int month,year;
	cin>>year>>month;
	if (month==1||month==3||month==5||month==7||month==8||month==10||month==12)  
    {cout<<"31"<<'\n';}
	else if(month==4||month==6||month==9||month==11)
	{cout<<"30"<<'\n';}
	else if(year%4!=0&&month==2||year%4==0&&year%100==0&&year%400!=0&&month==2)
	{cout<<"28"<<endl;}
	else if(year%4==0&&year%100!=0&&month==2||year%400==0&&month==2)
	{cout<<"29"<<endl;}
	return 0;
}
