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
    /* in caz ca avem vectorul mai mare primul, interschimbam */
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
/*
*** Idee de rezolvare:
    ** partitionam elementele din ambii vectori astfel incat sa obtinem 2 jumatati
    egale ca numar de elemente la inceput, si prin comparatii vom partitiona in
    continuare folosind vectorul de dimensiune mai mica pentru a obtine 2 partitii
    in care toate elementele din partitia stanga sa fie mai mici decat cele din
    dreapta
    ** avand vectorii a si b, trebuie ca a sa fie vectorul de dimensiune mai mica
    sa fie primul pentru a putea fi partitionat
*/