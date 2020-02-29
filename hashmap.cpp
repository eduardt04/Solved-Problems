#include <fstream>
#include <iostream>
#include <map>
using namespace std;
ifstream fin("input.in");
int main(){
    int k, t, n, x, i, money;
    fin>>t;
    for(k=1; k<=t; k++){
        fin>>money>>n;
        map<int, int> hash;
        hash.clear();
        fin>>x;
        hash.insert(make_pair(x, 1));
        for(i=2; i<=n; i++){
            fin>>x;
            if(hash.find(money-x)!=hash.end()){
                int a=hash.find(money-x)->second;
                cout<<min(i, a)<<" "<<max(i, a)<<endl;
            }
            hash.insert(make_pair(x, i));
        }
    }
    return 0;
}