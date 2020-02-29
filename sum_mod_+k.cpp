#include <iostream>
#include <fstream>
#include <map>
#include <utility>
using namespace std;
ifstream fin("input.in");
int main(){
    map<int, int> hash;
    int n, k, i, j, ct=0, x;
    fin>>n>>k;
    for(i=1; i<=n; i++){
        fin>>x;
        hash.insert(make_pair(x, i));
        if(hash.find(x-k)!=hash.end())
            ct++;
        if(hash.find(x+k)!=hash.end())
            ct++;
    }
    cout<<ct;
    return 0;
}