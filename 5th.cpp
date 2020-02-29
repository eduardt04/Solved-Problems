#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("input.in");
int main(){
    int n, d, i;
    vector<int> v;
    fin>>n>>d;
    v.resize(n);
    for(i=0; i<n; i++)
        fin>>v[i];
    for(i=0; i<n; i++)
        cout<<v[(i+d)%n]<<" ";
    return 0;
}