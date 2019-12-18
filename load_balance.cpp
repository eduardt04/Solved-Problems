/// Given n tasks each with their duration time and n ressources to work the tasks
/// find a pairing of task - ressource to minimize the total duration
/// Complexity O(N*logN)
#include <fstream>
#include <utility>
#include <vector>
#include <queue>
using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

int main() {
    int n, i, x, m;
    vector<int> v;
    fin>>n>>m;
    
    for(i = 1; i <= n; i++) {
        fin>>x;
        v.push_back(x);
    }

    /// assign succesively tasks to each ressource as soon as it ends
    /// introduce in a heap each ressource with an end-time     
    priority_queue<pair<int, int> > heap;
    for(i = 0; i < m; i++) {
        heap.push(make_pair(-v[i], i+1));
        fout<<"Task "<< i+1 <<" to the ressource "<< i+1 <<endl;
    }

    /// find the earliest ressource that ends and start reusing it for a different task
    for(i = m; i < n; i++) {
        int current_low = heap.top().first;
        int current_res = heap.top().second;
        heap.pop();
        heap.push(make_pair(current_low - v[i], current_res));
        fout<<"Task "<< i+1 <<" to the ressource "<< current_res <<endl;
    }
    return 0;
}