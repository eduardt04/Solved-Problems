/// Given n arrays of natural numbers find an array of n numbers with the properties:
/// each number is selected from a different arrays
/// the sum of the array is a given constant k
/// solved in O(m * k), m = total number of elements in the n arrays

#include <fstream>
#include <vector>
#include <string>
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");

int main() {
    int n, k, i, j, m, x, p;
    fin>>n>>k;
    vector<int> dp[n+1], prev[n+1];
    
    for(i = 0; i <= n; i++)
        dp[i].resize(k+1), prev[i].resize(k+1);
    /// dp[i][j] = 1, if sum j can be obtained with one element from each array 1 ... i, or 0 if not
    /// solution is found in dp[n][k]
    /// recursion is given by taking every sum obtained at step i-1 (max k) and adding it with every number in the i-th array
    for(i = 1; i <= n; i++) {
        fin>>m;
        for(j = 1; j <= m; j++) {
            fin>>x;
            if(i == 1)
                dp[i][x] = 1;
            for(p = 0; p <= k; p++)
                if(dp[i-1][p] == 1 && p + x <= k) {
                    dp[i][p + x] = 1;   
                    prev[i][p + x] = p;
                }
        }
    }

    int step = n, value = k;
    while(step > 0) {
        fout<<value - prev[step][value]<<" ";
        value = prev[step][value];
        step--;
    }
    return 0;
}