#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;
ifstream fin("input.in");
int main(){
    int n, m, i, x, y, t;
    fin>>n>>m;
    vector<list<int> >g;
    g.assign(n+1, list<int>());
    vector<int> culoare;
    culoare.assign(n+1, 0);
    vector<bool> viz; 
    viz.assign(n+1, false);
    for(i=1; i<=m; i++){
        fin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    queue<int> q;
    for(i=1; i<=n; i++)
        fin>>culoare[i];
    fin>>t;
    vector<int> d;
    d.assign(n+1, 0);
    for(i=1; i<=n; i++)
        if(culoare[i]==t){
            q.push(i);
            d[i]=1;
        }
    while(!q.empty()){
        int curent=q.front();
        viz[curent]=true;
        list<int>::iterator it;
        for(it=g[curent].begin(); it!=g[curent].end(); it++)
            if(!viz[*it]){
                q.push(*it);
                if(!d[*it])
                    d[*it]=d[curent]+1;
                else {
                    cout<<d[*it]+d[curent]-1<<endl;
                    return 0;
                }
            }
        q.pop();
    }
    cout<<-1<<endl;
    return 0;
}