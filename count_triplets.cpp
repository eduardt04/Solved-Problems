#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
ifstream fin("input.in");
long triplets(vector<int> a, vector<int> b, vector<int> c) {

        long totalTriplets = 0;

        set<int> setA;
        for(int i : a){ setA.insert(i); }
        a.assign(setA.begin(), setA.end());

        set<int> setB;
        for(int i : b){ setB.insert(i); }
        b.assign(setB.begin(), setB.end());

        set<int> setC;
        for (int i : c) { setC.insert(i); }
        c.assign(setC.begin(), setC.end());

        for (int i = 0; i < b.size(); i++) {
            long numA = upper_bound(a.begin(), a.end(), b[i]) - a.begin();
            long numC = upper_bound(c.begin(), c.end(), b[i]) - c.begin();
            totalTriplets += numA * numC;
        }

        return totalTriplets;
}
int main(){
    int la, lb, lc, i, j, k;
    fin>>la>>lb>>lc;
    vector<int> a;
    vector<int> b;
    vector<int> c;
    a.resize(la);
    for(i=0; i<a.size(); i++)
        fin>>a[i];
    b.resize(lb);
    for(j=0; j<b.size(); j++)
        fin>>b[j];
    c.resize(lc);
    for(k=0; k<c.size(); k++)
        fin>>c[k];
    cout<<triplets(a, b, c);
    return 0;
}
