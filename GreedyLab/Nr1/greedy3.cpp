#include <fstream>
#include <vector>
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");
vector<vector<int> > a;
vector<int> capete;
int counter = 1;

void bsearch(int x) {
    int left = 0, right = counter;
    /* cautam binar in ce subsir putem include x */
    while(left < right) {
        int mid = (left + right)/2;
        /* daca gasim 2 valori consecutive in care sa il incadram pe x el va 
        fi inclus in vectorul in care este mai mic decat capatul, stim clar ca
        nu este alt vector care sa aiba o valoare mai mica decat el ( vectorul de 
        capete este sortat ) */
        if(capete[mid-1] < x && x < capete[mid]) {
            right = mid;
            break;
        } 
        if(capete[mid] < x && x < capete[mid+1]) {
            right = mid + 1;
            break;
        }
        /* continuam sa cautam binar */
        if(x > capete[mid])
            left = mid + 1;
        else right = mid;
    }
    /* daca este fix capatul, trebuie adaugat un nou capat si alt vector */
    if(right == counter) {
        a.push_back(vector<int>());
        counter++;
        capete.push_back(x);
    }
    /* adaugam valoarea pentru afisare si actualizam capatul */
    a[right].push_back(x);
    capete[right] = x;
}

int main() {
    int n, x, i, j;
    fin>>n>>x;
    a.push_back(vector<int>());
    capete.push_back(x);
    a[0].push_back(x);
    for(i = 2; i <= n; i++) {
        fin>>x;
        bsearch(x);
    }
    for(i = 0; i < a.size(); i++) {
        for(j = 0; j < a[i].size(); j++)
            fout<<a[i][j]<<" ";
        fout<<endl;
    }
    return 0;
}
/*
*** ideea algoritmului: parcurgem vectorul si folosim un vector de capete
pentru a retine cel mai mic numar aflat la momentul curent in subsirul i ("capatul")
*** se va incepe cu un subsir continand primul numar, apoi se va cauta binar
in vectorul de capete in ce vector putem adauga valoarea curenta x
*** ni se garanteaza ca vectorul este sortat prin faptul ca noi cautand valoarea
x binar de la inceput, o vom adauga in vectorul cu valoarea maxima mai mica sau
egala cu el in capat, care va fi inlocuita de acesta
*** daca gasim o valoare mai mare decat ultimul capat, vom crea un nou capat
si un nou vector
*** practic cand gasim o valoare x astfel incat sa creem un capat nou, inseamna
ca ea era deja > decat orice alt capat => vectorul de capete ramane sortat
*** folosim si un vector de vectori pt a pastra solutia cu subsirurile

*** Complexitatea timp: O(nlogn) 
*** pentru fiecare numar din vector cautam binar in ce vector trebuie sa fie inclus
*** n cautari * O(logn) => O(nlogn)
*/