#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("input.in");
int main(){
    unsigned long long q, k, n, i, m, x;
    fin>>q;
    for(k=1; k<=q; k++){
        unsigned long long sbest=0;
        unsigned long long s=0;
        fin>>n>>m;
        for(i=1; i<=n; i++){
            fin>>x;
            if((s%m+x%m)%m>x%m)
                s=(s%m+x%m)%m;
            else s=x%m;
            sbest=max(sbest, s);
        }
        cout<<sbest<<endl;
    }
    return 0;
}
