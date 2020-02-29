#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
ifstream fin("input.in");
vector<int> f;
int main(){
    int n, i, x, count=0;
    fin>>n;
    f.resize(101);
    for(i=1; i<=n; i++){
        fin>>x;
        f[x]++;
        if(f[x]%2==0)
            count++;
    }
    cout<<count;
    return 0;
}