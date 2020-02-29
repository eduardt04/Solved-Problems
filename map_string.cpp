#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
using namespace std;
ifstream fin("input.in");
int main(){
    int n, i;
    long nr;
    fin>>n;
    string s;
    map<string, long> my_map;
    for(i=0; i<n; i++){
        fin>>s;
        fin>>nr;
        my_map.insert(make_pair(s, nr));
    }
    while(getline(fin>>ws, s)){
        map<string, long>::iterator it;
        it=my_map.find(s);
        if(it!=my_map.end())
            cout<<s<<"="<<(*it).second<<endl;
        else cout<<"Not found"<<endl;
    }
    return 0;
}