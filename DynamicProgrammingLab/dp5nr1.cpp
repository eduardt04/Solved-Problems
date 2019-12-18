/// Weighted Interval Scheduling problem - O(n * logn)
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");

/// for an interval keep the start and end time, its value, and its index at reading
struct var {
    int left, right, val, index;
    var(int x = 0, int y = 0, int z = 0, int t = 0) : left(x), right(y), val(z), index(t) {};
};

/// heap comparer to keep intervals sorted in ascending order by their end time
struct HeapComparer {
    bool operator()(const var &a, const var &b) {
        return a.right > b.right;
    }
};

/// function to test if 2 intervals do not overlap ( a starts after b )
bool isCompatible(const var &a, const var &b) {
    return (a.left >= b.right);
}

int main() {
    priority_queue<var, vector<var>, HeapComparer> h;
    int n, i, x, y, z;
    fin>>n;

    vector<var> v;
    vector<int> best;
    /// best[i] = the right-most interval which does not overlap with i
    best.assign(n+1, 0);
    v.reserve(n * sizeof(var));

    for(i = 1; i <= n; i++) {
        fin>>x>>y>>z;
        var current = *(new var(x, y, z, i));
        v.push_back(current);

        bool found = false;
        var out;

        /// extract elements from the heap as long as they don't overlap with the current element
        /// the last one that matches the criteria is best[i] and is introduced back in the heap
        if(!h.empty()) {
            while(isCompatible(current, h.top()) && !h.empty()) {
                found = true;
                out = h.top();
                h.pop();
            }
        }

        if(found == true) {
            best[i] = out.index;
            h.push(out);
        }
        h.push(current);
    }

    /// the recursion takes the max value from the prev subproblem or the best[i] subproblem
    vector<int> dp;
    dp.assign(n+1, 0);
    for(i = 1; i <= n; i++)
        dp[i] = max(v[i].val + dp[best[i]], dp[i-1]);
    
    fout<<dp[n]<<endl;

    /// walk back through the dp vector and show the intervals that make the solution
    int index = n;
    while(index != 0) {
        if(v[index].val + dp[best[index] >= dp[index - 1]]) {
            fout<<v[index].left<<" "<<v[index].right<<endl;
            index = best[index];
        }
        else index--;
    }
    return 0;
}