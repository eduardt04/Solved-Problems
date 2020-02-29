#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream fin("input.in");
class DSF {
    vector<int> father;
    vector<int> height;
    public:
        DSF(int);
        int Find(int);
        void Union(int, int);
};
DSF::DSF(int size){
    height.assign(size+1, 0);
    father.resize(size+1);
    for(int i=1; i<=size; i++)
        father[i]=i;
}
int DSF::Find(int node){
    int y, root=node;
    while(root!=father[root])
        root=father[root];
    while(node!=father[node]){
        y=father[node];
        father[node]=root;
        node=y;
    }
    return root;
}
void DSF::Union(int x, int y){
    int rx=Find(x);
    int ry=Find(y);
    if(height[rx]>=height[ry])
        father[ry]=rx;
    else father[rx]=ry;
    if(height[rx]==height[ry])
        height[rx]++;
}
struct edge {
    int l, r, c;
};
bool compareedges(const edge a, const edge b){
    if(a.c!=b.c)
        return a.c>b.c;
    else 
        if(a.l!=b.l)
            return a.l>b.l;
    return a.r>b.r;
}
int main(){
    int n, k, i, x, y;
    vector<edge> g;
    fin>>n>>k;
    g.resize(n-1);
    for(i=0; i<n-1; i++)
        fin>>g[i].l>>g[i].r>>g[i].c;
    sort(g.begin(), g.end(), compareedges);
    vector<bool> m;
    m.assign(n, false);
    for(i=1; i<=k; i++){
        fin>>x;
        m[x]=true;
    }
    DSF P(n);
    int total_cost=0;
    for(i=0; i<n-1; i++){
        int rx=P.Find(g[i].l);
        int ry=P.Find(g[i].r);
        if(m[rx]==false || m[ry]==false){
            P.Union(g[i].l, g[i].r);
            if(m[rx]==true || m[ry]==true)
                m[P.Find(g[i].l)]=true;
        }
        else
            total_cost+=g[i].c;
    }
    cout<<total_cost;
    return 0;
}