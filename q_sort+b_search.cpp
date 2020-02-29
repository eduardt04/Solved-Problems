#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;
ifstream fin("input.in");
void quicksort(vector<pair<int, int> >&v, int st, int dr){
    int i=st, j=dr, piv;
    piv=v[(st+dr)/2].first;
    while(i<dr || j>st){
        while(v[i].first<piv)
            i++;
        while(v[j].first>piv)
            j--;
        if(i<=j){
            swap(v[i].first, v[j].first);
            swap(v[i].second, v[j].second);
            i++;
            j--;
        }
        else {
            if(i<dr)
                quicksort(v, i, dr);
            if(st<j)
                quicksort(v, st, j);
            return;
        }
    }
}
int bsearch(vector<pair<int, int> > v, int st, int dr, int val){
    if(st>dr)
        return -1;
    int mid=(st+dr)/2;
    if(val==v[mid].first)
        return mid;
    else if(val<v[mid].first)
        return bsearch(v, st, mid-1, val);
    else
        return bsearch(v, mid+1, dr, val);
}
int main(){
    int t, k, i, n, money;
    fin>>t;
    for(k=1; k<=t; k++){
        fin>>money>>n;
        vector<pair<int, int> >cost;
        cost.resize(n+1);
        for(i=1; i<=n; i++){
            fin>>cost[i].first;
            cost[i].second=i;
        }
        quicksort(cost, 1, n);
        for(i=1; i<=n; i++){
            int x=bsearch(cost, 1, n, money-cost[i].first);
            if(x!=-1){
                cout<<min(cost[i].second, cost[x].second)<<" ";
                cout<<max(cost[i].second, cost[x].second)<<endl;
                break;
            }
        }
    }
    return 0;
}