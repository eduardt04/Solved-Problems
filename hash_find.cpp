#include <fstream>
#include <cmath>
#include <string>
#include <unordered_map>
using namespace std;
ifstream fin("input1.in");
ifstream fin2("input2.in");
ofstream fout("output.out");

int main() {
    unordered_map<string, pair<int, int> > hash;
    string read;
    while(fin>>read) {
        if(hash.find(read) == hash.end())
            hash.insert(make_pair(read, make_pair(1, 0)));
        else 
            hash[read].first++;
    }
    while(fin2>>read) {
        if(hash.find(read) == hash.end())
            hash.insert(make_pair(read, make_pair(0, 1)));
        else 
            hash[read].second++;
    }
    unordered_map<string, pair<int, int> > :: iterator itr;
    float sum1 = 0, p1 = 0, p2 = 0;
    for(itr = hash.begin(); itr != hash.end(); itr++){
        sum1 += itr->second.first * itr->second.second;
        p1 += itr->second.first * itr->second.first;
        p2 += itr->second.second * itr->second.second; 
    }
    p1 = sqrt(p1), p2 = sqrt(p2);
    fout<<sum1/(p1 * p2);
    return 0;
}