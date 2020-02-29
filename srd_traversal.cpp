#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
ifstream fin("input.in");
struct Nod{
    int st, dr, h;
};
vector<Nod> d;
void SRD(int nod){
    if(d[nod].st!=-1)
        SRD(d[nod].st);
    cout<<nod<<" ";
    if(d[nod].dr!=-1)
        SRD(d[nod].dr);
}
int main(){
    int n, i, x, y, k, t, p;
    fin>>n;
    d.resize(n+1);
    d[1].h=1;
    for(i=1; i<=n; i++){
        fin>>d[i].st>>d[i].dr;
        d[d[i].st].h=d[i].h+1;
        d[d[i].dr].h=d[i].h+1;
    }
    fin>>t;
    for(k=1; k<=t; k++){
        fin>>p;
        for(i=1; i<=n; i++)
            if(d[i].h%p==0)
                swap(d[i].st, d[i].dr);
        SRD(1);
        cout<<endl;
    }
    return 0;
}