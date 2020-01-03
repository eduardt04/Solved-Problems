// binary search to find an index with v[i] = i in a sorted array - O(logn)
#include <fstream>
#include <vector>
using namespace std;

// input - output stream
ifstream fin("input.in");
ofstream fout("output.out");

// binary search function
int bsearch(vector<int> v, int left, int right) {
    // if left overcame right, the recursion is over and an index was not found
    if(left > right)
        return -1;

    // we choose to divide the elements from left to right by the middle position
    int mid = (left + right) / 2;
    
    // if the middle position matches v[x] = x, a solution has been found and it is returned
    if(v[mid] == mid) 
         return mid;
    
    // if a solution has not been found, then:
    
    // call the function for the left part ( left, mid -1 ) if the value is lower than the index
    else if(v[mid] < mid)
        return bsearch(v, mid + 1, right);

    // call the function for the right part ( mid + 1, right) if the value is higher than the index
    else return bsearch(v, left, mid - 1);
}

int main() {
    int i, n, x;
    vector<int> v;
    fin>>n;

    for(i = 1; i <= n; i++) {
        fin>>x;
        v.push_back(x);
    }
    
    fout<<bsearch(v, 0, n-1);
    return 0;
}
