/* given 2 sorted arrays(A, B), find the median of the reunion of the 2 - O(logn(min(A.size, B.size))) */
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");
vector<int> a, b;
int n, m;

int findMid(int left, int right) {
    if(left <= right) {
        int a_part = (left + right) / 2;
        int b_part = ((n + m + 1) / 2) - a_part; 

        if(a_part < n && b_part > 0 && b[b_part - 1] > a[a_part])
            return findMid(a_part + 1, right);
        
        else if(a_part > 0 && b_part < m && b[b_part] < a[a_part - 1])  
            return findMid(left, a_part - 1);
        
        else {
            if(a_part == 0) 
                return b[b_part];
            if(b_part == 0) 
                return a[a_part - 1];
            else 
                return min(a[a_part - 1], b[b_part]);
        }
    }
    else {
        fout<<"error";
        return 0;
    }
}

int main() {
    int i, x;
    fin>>n;
    for(i = 1; i <= n; i++) {
        fin>>x;
        a.push_back(x);
    }
    fin>>m;
    for(i = 1; i <= m; i++) {
        fin>>x;
        b.push_back(x);
    }
    
    if(n > m) {
        vector<int> copy;
        copy.assign(a.begin(), a.end());
        a.assign(b.begin(), b.end());
        b.assign(copy.begin(), copy.end());
        swap(n, m);
    }
    fout<<findMid(0, n);
    return 0;
}