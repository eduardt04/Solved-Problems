#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("input.in");
vector<int> t;
vector<int> h;
vector<int> c;
int nrc, n;
int getroot(int x){
    int r=x, y;
    while(t[r]!=r)
        r=t[r];
    while(t[x]!=x){
        y=t[x];
        t[x]=r;
        x=y;
    }
    return r;
}
void unite(int x, int y){
    if(h[x]>=h[y]){
        t[y]=x;
        c[x]+=c[y];
    }
    else {
        t[x]=y;
        c[y]+=c[x];
    }
    if(h[x]==h[y])
        h[x]++;
}
int main(){
    int k, q;
    fin>>q;
    for(k=1; k<=q; k++){
        long long m, clib, croad, i, x, y;
        fin>>n>>m>>clib>>croad;
        if(m==0)
            cout<<n*clib<<endl;
        else if(clib<=croad){
            cout<<clib*n<<endl;
            for(i=1; i<=m; i++)
                fin>>x>>y;
        }
        else {
            t.resize(n+1);
            for(i=1; i<=n; i++)
                t[i]=i;
            h.assign(n+1, 0);
            c.assign(n+1, 1);
            for(i=1; i<=m; i++){
                fin>>x>>y;
                int a=getroot(x);
                int b=getroot(y);
                if(a!=b)
                    unite(a, b);
            }
            long long cost=0;
            for(i=1; i<=n; i++)
                if(t[i]==i)
                    cost+=(c[i]-1)*croad+clib;
            cout<<cost<<endl;
           
        }
    }
    return 0;
}