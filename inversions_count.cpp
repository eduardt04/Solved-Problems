#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("input.in");
int main(){
    int t, k, i, j, n;
    vector<int> d;
    fin>>t;
    for(k=1; k<=t; k++){
        fin>>n;
        d.resize(n+1);
        d.assign(n+1, 0);
        int inv=0;
        bool chaos=false;
        for(i=1; i<=n; i++){
            fin>>d[i];
            if(d[i]-i>2)
                chaos=true;
        }
        for(i=n; i>=1; i--)
            for(j=max(1, d[i]-2); j<i; j++)
                if(d[j]>d[i])
                    inv++;
        if(chaos==false)
            cout<<inv<<endl;
        else cout<<"Too chaotic"<<endl;
    }
    return 0;
}