/// Given an array of integers, find whether there exists a triplet that sums to 0
/// Complexity O(Nˆ2)
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

int main() {
    int n, i, x;
    vector<int> v;
    fin>>n;

    for(i = 0; i < n; i++) {
        fin>>x;
        v.push_back(x);
    }

    /// sort the array in ascending order
    sort(v.begin(), v.end());
    
    /// set the first index of the triplet
    for(i = 0; i <= n-2; i++) {
        /// iterate with 2 other indexes one from the end and one from the beginning
        int l = i + 1, r = n-1;
        /// as long as the 2 indexes don't overlap
        while (l < r) {
            /// if they sum to 0, then print the triplet and continue the iteration
            if(v[i] + v[l] + v[r] == 0) {
                fout<<v[i]<<" + "<<v[l]<<" + "<<v[r]<<" = 0"<<endl;
                return 0;
            }
            /// if the sum is less than 0, then increase the left index, because numbers are
            /// sorted ascending and that will incease triplet's sum
            else if(v[i] + v[l] + v[r] < 0)
                l++;
            /// if sum is more than 0, decrease the right index => decrease the sum
            else r--;
        }
    }
    fout<<"There is no triplet that sums to 0.";
    return 0;
}