/// Minimum TSP-problem with Branch-and-Bound method - O(2ˆn * nˆ2)
#include <fstream>
#include <vector>
#include <climits>
#include <list>
using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

struct Path {
    /// each path has its own links 2D-array
    vector<vector<int> > links;
    /// mark the nodes that have already been traversed
    vector<bool> nodes;
    /// calculate the f_value and the length of the path, also keep the last node traversed
    int length, f_value, last_node;
};

int n;
/// list of all the paths at the current moment, always get the minimum path
list<Path> L;

/// function to reduce the values in the 2D-arrays to give a better estimation for f_value
int null_mat(vector<vector<int> > &a) {
    int i, j, min_line, min_col;
    bool test_line, test_col, min_found;
    int reduct = 0;

    /// each line or collumn that has only strictly positive values (i != j) can be reduced with
    /// the minimum number on that line, and that ammount is added to f_value 
    for(i = 1; i <= n; i++) {
        test_line = true;
        min_found = false;
        min_line = INT_MAX;

        /// test if the line has zero values and calculate the min value
        for(j = 1; j <= n; j++) {
            if(a[i][j] == 0)
                test_line = false;
            else if(a[i][j] > 0) {
                min_found = true;
                min_line = min(min_line, a[i][j]);
            }
        }

        /// if the line has no zero values (i!=j) then reduce each positive element by min
        if(test_line && min_found) {
            /// add the min value to the reduction value
            reduct += min_line;
            for(j = 1; j <= n; j++)
                a[i][j] = max(-1, a[i][j] - min_line);
        }
    }

    /// same procedure, but for collumns
    for(i = 1; i <= n; i++) {
        test_col = true;
        min_col = INT_MAX;
        min_found = false;

        for(j = 1; j <= n; j++) {
            if(a[j][i] == 0)
                test_col = false;
            else if(a[j][i] > 0) {
                min_col = min(min_col, a[j][i]);
                min_found = true;
            }
        }

        if(test_col && min_found) {
            reduct += min_col;
            for(j = 1; j <= n; j++)
                a[j][i] = max(-1, a[j][i] - min_col);
        }
    }
    return reduct;
}

void tsp() {
    /// iterate over the list of paths and get the one with minimum f_value
    Path lowest_f;
    lowest_f.f_value = INT_MAX;
    
    list<Path> :: iterator it, it_to_min;
    for(it = L.begin(); it != L.end(); it++)
        if((*it).f_value < lowest_f.f_value) {
            lowest_f = *it;
            it_to_min = it;
        }
    L.erase(it_to_min);

    /// for each unvisited node in the path, start a new branch and calculate the values
    int i, j;
    for(i = 1; i <= n; i++) {
        if(lowest_f.nodes[i] == false) {
            int traversal_value = lowest_f.links[lowest_f.last_node][i];
            vector<int> cp_line, cp_col;
            Path next_p = lowest_f;

            for(j = 1; j <= n; j++) {
                cp_line.push_back(next_p.links[lowest_f.last_node][j]);
                cp_col.push_back(next_p.links[j][i]);
                next_p.links[lowest_f.last_node][j] = -1;
                next_p.links[j][i] = -1;
            }

            next_p.links[i][lowest_f.last_node] = -1;
            next_p.length = lowest_f.length + 1;
            next_p.last_node = i;
            next_p.nodes[i] = true;
            next_p.f_value = lowest_f.f_value + traversal_value + null_mat(next_p.links);
            
            if(next_p.length == n)
                for(it = L.begin(); it != L.end(); it++)
                    if((*it).f_value >= next_p.f_value) {
                        it = L.erase(it);
                        it--;
                    }

            L.push_back(next_p);
        }
    }
    if(L.size() > 1)
        tsp();
}

int main() {
    int i, j;
    fin>>n;
    
    vector<vector<int> > a;
    a.resize(n+1);

    for(i = 1; i <= n; i++) {
        a[i].resize(n+1);
        for(j = 1; j <= n; j++)
            fin>>a[i][j];
    }

    /// start the path from node 1, with length 1, f_value is just the reduction of the 2D-array
    Path p;
    p.nodes.resize(n+1);
    p.nodes[1] = true;
    p.length = p.last_node = 1;
    p.links = a;
    p.f_value = null_mat(p.links);
    L.push_back(p);
    
    tsp();
    
    fout<<"Minimum TSP cost: "<<L.front().f_value;

    return 0;
}