#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
ifstream fin("input.in");
vector<vector<int> >g;
int dx[]={-1, -1, -1, 0, 1, 1, 1, 0}, n;
int dy[]={-1, 0, 1, 1, 1, 0, -1, -1}, m, ct;
void dfs(int x, int y){
    int i, xx, yy;
    bool found=false;
    g[x][y]=-1;
    for(i=0; i<8; i++){
        xx=x+dx[i];
        yy=y+dy[i];
        if(xx>=1 && xx<=n && yy>=1 && yy<=m)
            if(g[xx][yy]==1){
                found=true;
                ct++;
                dfs(xx, yy);
            }
    }
}
int main(){
    int i, j, maxsize=0;
    fin>>n>>m;
    g.resize(n+1);
    for(i=0; i<=n; i++)
        g[i].assign(m+1, 0);
    for(i=1; i<=n; i++)
        for(j=1; j<=m; j++)
            fin>>g[i][j];
    for(i=1; i<=n; i++)
        for(j=1; j<=m; j++)
            if(g[i][j]==1){
                ct=1;
                dfs(i, j);
                maxsize=max(maxsize, ct);
            }
    cout<<maxsize;
    return 0;
}