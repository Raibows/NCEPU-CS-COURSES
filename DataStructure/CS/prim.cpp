/*
prim
storage in array
*/
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

#define inf 0x3f3f3f3f

const int n=53;


class solution{
public:
	double cost[n][n];
	int set_v[n];
	solution();
	void read();
	void prim();
};
solution::solution(){
	for(int i=0;i<n;i++){
		set_v[i]=0;
		for(int j=0;j<n;j++){
			cost[i][j]=inf;
		}
	}
}
void solution::read(){
	ifstream infile;
	infile.open("c:/users/raibows/downloads/hello.txt",ios::in);
	string temp1;
	string temp2;
	string temp3;
	infile>>temp1;
	while(temp1!="#"){
		infile>>temp2>>temp3;
		int start,end;
		double weight;
		start=atoi(temp1.c_str())-1;
		end=atoi(temp2.c_str())-1;
		weight=atof(temp3.c_str());
		//cout<<temp1<<"   "<<temp2<<"  "<<temp3<<endl;
		//cout<<start<<"   "<<end<<"  "<<weight<<endl;
		if(weight<cost[start][end]){
			cost[start][end]=weight;
			cost[end][start]=weight;
		}
		infile>>temp1;
	}
	infile.close();	

}
void solution::prim(){
	set_v[49]=1;
	while(1){
		double min=inf;
		int temp_start=-1;
		int temp_end=-1;
		for(int i=0;i<n;i++){
			if(set_v[i]==1){
				for(int j=0;j<n;j++){
					if(set_v[j]==0&&cost[i][j]<min){
						min=cost[i][j];
						temp_end=j;
						temp_start=i;
					}
				}
			}
		}
		if(temp_end==-1){
			break;
		}else
		{
			cout<<temp_start<<"---->"<<temp_end<<" costs "<<min<<endl;
			set_v[temp_end]=1;
		}		
	}
	

	
}



int main(void){
	solution test;
	test.read();
	test.prim();
	system("pause");
}