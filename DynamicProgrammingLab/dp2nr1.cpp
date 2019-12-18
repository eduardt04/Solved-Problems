/// Given a 2D array n x m with a value assigned for each position, find a path of maximum value from [1,1] to [n,m]
/// walking just south or east
/// Time complexity: O(n * m)
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");

int main() {
    int n, m, i, j, x;
    fin>>n>>m;
    int a[n][m], d[n][m];
    /// d[i][j] = max value path from [1,1] to [i,j]
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            fin>>a[i][j];
    d[0][0] = a[0][0];
    /// pre-calculate for first row and first collumn where there can only be east moves, respectively south moves
    for(i = 1; i < n; i++)
        d[i][0] = a[i][0] + d[i - 1][0];
    for(j = 1; j < m; j++)
        d[0][j] = a[0][j] + d[0][j - 1];
    for(i = 1; i < n; i++)
        for(j = 1; j < m; j++)
            /// there are only 2 position from where [i,j] can be reached: [i-1, j] walking south or [i, j-1] walking east
            /// having the subproblems already calculated, we just add the max value of the 2 to the value of the [i,j]
            d[i][j] = a[i][j] + max(d[i - 1][j], d[i][j - 1]);
    fout<<d[n - 1][m - 1]<<endl;
    i = n - 1, j = m - 1;
    do {
        fout<<i + 1<<" "<<j + 1<<endl;
        if(d[i][j] == a[i][j] + d[i - 1][j])
            i--;
        else j--;
    } while(i !=0 || j != 0);
    fout<<1<<" "<<1;
    return 0;
}