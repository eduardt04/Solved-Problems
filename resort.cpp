#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("input.in");
int main(){
    int n, i, counter=0;
    vector<int> v;
    fin>>n;
    v.resize(n+1);
    for(i=1; i<=n; i++)
        fin>>v[i];
    for(i=1; i<=n; i++)
        while(v[i]!=i){
            swap(v[v[i]], v[i]);
            counter++;
        }
    cout<<counter<<endl;
    return 0;
}