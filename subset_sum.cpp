/// Given an array and an integer s, find whether that integer can be obtained as a sum
/// from the elements in the array
/// Complexity (O(N * (high-low)))
#include <fstream>
#include <vector>
using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

/// sub[i][j] = true if sum j can be obtained using numbers from v[1..i]
/// because negative numbers are allowed, the sub 2D array has to be shifted
/// to left with the value of the lowest sum possible obtained in the array

int main() {
    int n, sum, i, j, x;
    /// high, low - highest and lowest sums in the array
    int high = 0, low = 0;
    vector<int> v;
    fin>>n>>sum;

    /// find the highest and lowest sums possible in the array
    for(i = 0; i < n; i++) {
        fin>>x;
        v.push_back(x);
        high = max(high, high + x);
        low = min(low, low + x);
    }

    vector<vector<bool> > sub;
    sub.assign(n+1, vector<bool>(high - low + 1));
    
    /// iterate over every element in the array
    for(i = 1; i <= n; i++) {
        /// mark that sum v[i - 1] is obtainable (current number) 
        sub[i][v[i-1] - low] = true;
        for(j = low; j <= high; j++) {
            /// iterate over all the possible sums
            if(sub[i-1][j - low] == true) {
                /// if we got an already existing sum from the previous step
                sub[i][j - low] = true;
                /// mark the sum obtainable at the current step and then calculate the new sum
                /// from the previous sum + the current element
                if(j + v[i - 1] <= high)
                    sub[i][j + v[i - 1] - low] = true;
            }
        }
    }
    if(sub[n][sum - low] == true)
        fout<<"Sum can be obtained"<<endl;
    else fout<<"Sum can not be obtained"<<endl;
    fout<<endl;
    return 0;
}