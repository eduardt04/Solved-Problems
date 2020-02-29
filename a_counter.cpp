#include <fstream>
#include <iostream>
#include <string>
using namespace std;
ifstream fin("input.in");
int main(){
    string s;
    fin>>s;
    long long n, i, count=0, extra=0;
    fin>>n;
    for(i=0; i<s.length(); i++)
        if(s[i]=='a')
            count++;
    for(i=0; i<n%s.length(); i++)
        if(s[i]=='a')
            extra++;
    count=count*(n/s.length())+extra;
    cout<<count;
    return 0;
}