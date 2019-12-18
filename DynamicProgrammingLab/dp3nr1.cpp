/// editing distance between 2 strings with 3 operations possible: replace, insert, delete
/// each operation has a cost attached => find the minimum cost of editing a into b
/// time complexity : O(n*m), n = length(a), m = length(b)

#include <fstream>
#include <vector>
#include <string>
#define min3(x, y, z) min(x, min(y, z))
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");

int main() {
    string s1, s2;
    fin>>s1>>s2;
    int c1, c2, c3, i, j;
    fin>>c1>>c2>>c3;
    /// c1 - insert
    /// c2 - remove
    /// c3 - replace
    int n = s1.length();
    int m = s2.length();
    int dp[m + 1][n + 1];

    for(i = 0; i <= m; i++)
        for(j = 0; j <= n; j++) {
            /// if a is empty, we have to do length(b) inserts
            if(i == 0)
                dp[i][j] = j * c1;
            /// if b is empty, we have to do length(a) deletes
            else if(j == 0)
                dp[i][j] = i * c2;
            /// if the letters at the current positions are the same, no editing is needed, so take the result
            /// of the subproblems where the current positions are ignored
            else if(s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            /// else take the lowest cost from the 3 possible operations applied on the current word
            else dp[i][j] = min3(c1 + dp[i][j - 1], c2 + dp[i - 1][j], c3 + dp[i - 1][j - 1]);
        }
    fout<<dp[m][n];
    return 0;
}