/// given n Domino pieces, find the maximum-length array of matching pieces
/// Time complexity - O(nˆ2)

#include <fstream>
#include <vector>
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");

struct var {
    int left, right;
    var(int x = 0, int y = 0) : left(x), right(y) {};
};

int main() {
    int n, i, x, y, curr_max = 0, pos_max = 0;
    fin>>n;
    vector<int> best(n), number(n), prev(n), count(n);
    /// best[i] = the right-most piece that matches with i
    /// count[i] = the number of arrays of max-length that end with the i-th piece
    /// prev[i] = the previous piece that matches i in the max-length array
    vector<var> d;
    d.reserve(sizeof(int) * n);
    for(i = 0; i < n; i++) {
        bool found = false;
        fin>>x>>y;
        d.push_back(*(new var(x, y)));
        for(int j = i - 1; j >= 0; j--) {
            if(best[i] == best[j] + 1 && number[j] == x)
                count[i]++;
            if(number[j] == x && best[i] <= best[j]) {
                best[i] = best[j] + 1;
                count[i] = 1;
                prev[i] = j;
                found = true;
            }
        }
        if(!found) {
            best[i] = 1;
            prev[curr_max] = -1;
        }
        number[i] = y;
        if(curr_max <= best[i]) {
            curr_max = best[i];
            pos_max = i;
        }
    }
    int total = 0;
    for(i = 0; i < n; i++)
        if(best[i] == curr_max)
            total += count[i];
    fout<<total<<endl;
    while(pos_max != -1) {
        fout<<d[pos_max].left<<" "<<d[pos_max].right<<endl;
        pos_max = prev[pos_max];
    }
    return 0;
}