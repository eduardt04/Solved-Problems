/// 2-SAT problem polynomial time
/// Complexity: O(N + M)
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <cmath>
using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

enum colors {
    white, grey, black
};

int n, counter = 1;
vector<int> scc;
/// scc[x] = to which strongly connected component(SCC) does x belong
stack<int> dfs_stack;
/// store every node traversed in the direct DFS in dfs_stack
vector<vector<int> > a;
/// a is the adjacency matrix
vector<bool> dfs_color;
/// dfs_color[x] = white - unused, grey - in use, black - ended
vector<bool> inverse_dfs_color;
/// inverse_dfs_color[x] = same as DFS

int neg(int x) {
    /// computes the index for !x 
    return (x = (x > n) ? x - n : x + n);
}

/// DFS on direct graph
void dfs(int node) {
    dfs_color[node] = grey;
    for(int i = 1; i <= 2*n; i++)
        if(a[node][i] && dfs_color[i] == white)
            dfs(i);
    /// store nodes in traversal order in a stack
    dfs_stack.push(node);
    dfs_color[node] = black;
}

/// DFS on inverse graph
void dfs_inverse(int node) {
    inverse_dfs_color[node] = grey;
    for(int i = 1; i <= 2*n; i++) {
        if(a[i][node] && inverse_dfs_color[i] == white)
            dfs_inverse(i);
    }
    /// on the inverse DFS also mark the SCC of each node
    scc[node] = counter;
    inverse_dfs_color[node] = black;
}

int main() {
    int m; // n variables, m clauses of 2 variables each
    // index variables from [1...n] - positive and [n+1...2n] - negative
    fin>>n>>m;
    
    int i, j;
    a.resize(2*n + 1);
    for(i = 0; i < 2*n + 1; i++)
        a[i].resize(2*n + 1);

    int x, y;
    for(i = 1; i <= m; i++) {
        fin>>x>>y;
        /// if a value is < 0 (so it's a negative variable, get the absolute value
        /// and add n to it => value in [n+1...2n])
        x = (x < 0) ? abs(x) + n : x;
        y = (y < 0) ? abs(y) + n : y;
        /// for each clause x v y, add in the graph edges from !x to y and from x to !y
        /// that is equivalent to x v y <=> (!x => y) and (x => !y)
        a[neg(x)][y] = 1;
        a[x][neg(y)] = 1;
    }

    /// initialize the arrays for Kosaraju's Algorithm for SCC
    scc.assign(2*n+1, 0);
    dfs_color.assign(2*n+1, white);
    inverse_dfs_color.assign(2*n+1, white);

    /// use DFS on the direct graph
    for(i = 1; i <= 2*n; i++)
        if(dfs_color[i] == white)
            dfs(i);
    /// traverse nodes in the stack and then use inverse DFS on each one
    while(!dfs_stack.empty()) {
        int node = dfs_stack.top();
        dfs_stack.pop();

        if(inverse_dfs_color[node] == white) {
            dfs_inverse(node);
            counter++;
        }
    }

    for(i = 1; i <= n; i++) {
        if(scc[i] == scc[i+n]) {    
            fout<<"Non-sat"<<endl;
            return 0;
        }
    }

    for(i = 1; i <= 2*n; i++) {
        for(j = 1; j <= 2*n; j++)
            fout<<a[i][j]<<" ";
        fout<<endl;
    }

    fout<<"sat"<<endl;
    
    return 0;
}