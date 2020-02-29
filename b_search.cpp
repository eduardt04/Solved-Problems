#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;
ifstream fin("input.in");
int main(){
    long long n, goal, i, ans=0;
    fin>>n>>goal;
    vector<long long> d(n);
    for(i=0; i<d.size(); i++)
        fin>>d[i];
    long long low=1;
    long long high=1e18;
    while(low<=high){
        long long mid=high+(low-high)/2;
        long long done=0;
        for(i=0; i<d.size(); i++){
            done+=mid/d[i];
            if(done>=goal)
                break;
        }
        if(done>=goal){
            high=mid-1;
            ans=mid;
        }
        else 
            low=mid+1;
    }
    cout<<ans<<endl;
    return 0;
}