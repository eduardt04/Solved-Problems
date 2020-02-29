#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("input.in");
int main(){
    long long n, m, i, j, st, dr, x, ct=0;
    fin>>n>>m;
    vector<long long> d;
    d.resize(n+2);
    d.assign(n+2, 0);
    for(i=1; i<=m; i++){
        fin>>st>>dr>>x;
        d[st]+=x;
        d[dr+1]-=x;
    }
    x=0;
    for(j=1; j<=n; j++){
        x+=d[j];
        ct=max(x, ct);
    }
    cout<<ct;
    return 0;
}