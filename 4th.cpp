#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("input.in");
int main(){
    int a[6][6], i, j, s=0, smax=-63;
    for(i=0; i<=5; i++)
        for(j=0; j<=5; j++)
            fin>>a[i][j];
    for(i=0; i<=3; i++)
        for(j=0; j<=3; j++){
            s=0;
            s+=a[i][j];
            s+=a[i][j+1];
            s+=a[i][j+2];
            s+=a[i+1][j+1];
            s+=a[i+2][j];
            s+=a[i+2][j+1];
            s+=a[i+2][j+2];
            smax=max(s, smax);
        }
    cout<<smax;
    return 0;
}