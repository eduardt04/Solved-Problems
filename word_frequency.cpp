#include <fstream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;
ifstream fin("input1.in");
ifstream fin2("input2.in");
ofstream fout("output.out");

int main() {
    bool found;
    int n = 0, i;
    vector<string> words;
    vector<int> app1, app2;
    string read;
    while(fin>>read) {
        found = false;
        for(i = 0; i < n; i++)
            if(read.compare(words[i]) == 0) {
                found = true;
                break;
            }
        if(found == true) 
            app1[i]++;
        else {
            n++;
            app1.push_back(1);
            app2.push_back(0);
            words.push_back(read);
        }
    }
    while(fin2>>read) {
        found = false;
        for(i = 0; i < n; i++)
            if(read.compare(words[i]) == 0) {
                found = true;
                break;
            }
        if(found == true) 
            app2[i]++;
        else {
            n++;
            app1.push_back(0);
            app2.push_back(1);
            words.push_back(read);
        }
    }
    float suma1 = 0, patr1 = 0, patr2 = 0;
    for(i = 0; i < n; i++) {
        suma1 += app1[i] * app2[i];
        patr1 += app1[i] * app1[i];
        patr2 += app2[i] * app2[i];
    }
    patr1 = sqrt(patr1);
    patr2 = sqrt(patr2);
    fout<<suma1/(patr1 * patr2);
    return 0;
}
