#include <iostream>
using namespace std;

//L形骨牌问题
int title = 1;
class board{
public:
    int size = 1;
    int k;
    int **g;
    board(){
        cin>>k;
        for(int i=1;i<=k;i++){
            size *= 2;
        }
        g = new int *[size];
        for(int i=0;i<size;i++){
            g[i] = new int [size];
        }
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                g[i][j] = -1;
            }
        }  
    }
    void fill(int r, int c, int s, int dr, int dc);
};
void board::fill(int r, int c, int s, int dr, int dc){
    if(s==1){
        return;
    }
    int t = title++;
    int ss = s/2;  //divide it into 4 small problems
    if((dr<r+ss)&&(dc<c+ss)){ //top left corner
        g[r+ss-1][c+ss] = t;
        g[r+ss-1][c+ss-1] = t;
        g[r+s]
    }
}


int main(void){




}