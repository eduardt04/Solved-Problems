#include <fstream>
#include <vector>
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");

struct activity {
    int limit_time, length, index;
};
/* functie de comparare, sortam activitatile dupa timpul limita crescator */
bool comparer(const activity &a, const activity &b) {
    return a.limit_time < b.limit_time;
}

int main() {
    int n, i, x, y, time = 0, late = 0;
    vector<activity> acts;
    fin>>n;
    for(i = 1; i <= n; i++) {
        fin>>x>>y;
        acts.push_back((activity){y, x, i});
    } 
    /* sortam crescator dupa timp limita */  
    sort(acts.begin(), acts.end(), comparer);
    for(i = 0; i < n; i++){
        fout<<time<<" ";
        /* de fiecare data adaugam timpul necesar ca sa vedem la ce moment am ajuns */
        time += acts[i].length;
        /* calculam intarzierea maxima */
        late = max(late, time - acts[i].limit_time);
        fout<<time<<" "<<late<<endl;
    }
    fout<<late;
    return 0;
}
/*
*** algoritm clasic de greedy O(nlogn) in care sortam ( de aici complexitatea ) si apoi 
alegem elementele pe rand in ordinea aleasa din sortare - O(n)
*** de ce functioneaza si ne garanteaza corectitudinea:
sortare dupa timpul limita al fiecarei activitati, in ordine crescatoare? avem 2
date in problema, durata si timpul limita, deci avem 3 criterii posibile de sortare,
sau macar 3 criterii relevante: dupa durata, dupa durata - timp limita(efort) si dupa
timp limita
*** daca am sorta dupa durata unei activitati:
    sa presupunem ca avem:
        activitatea 1 cu durata 1 si timp limita 100
        activitatea 2 cu durata 10 si timp limita 10
    sortand dupa durata am efectua 1-2 si am obtine intarziere 1
    daca sortam dupa timp limita am efectua 2-1 si intarzierea ar fi 0
    => sortarea dupa durata nu este eficienta

*** daca am sorta dupa timp limita - durata:
    daca am avea:
        activitatea 1 cu durata 1 si timp limita 2
        activitatea 2 cu durata 10 si timp limita 10
    sortand dupa timp limita - durata am efectua 2-1 si am obtine intarziere 9
    sortand dupa timp limita am efectua 1-2 si am obtine intarziere 1
    => sortarea dupa timp limita - durata nu este eficienta

*** idee de demonstratie teoretica:
    ** sa presupunem ca avem solutia greedy G
    ** definim ca si inversiune o pereche de activitati i si j cu timplimita[i] < timplimita[j],
    dar i este executat dupa j
    ** intarzierea maxima intr-un program fara intreruperi este aceeasi daca i si j
    sunt interschimbate intre ele, daca timplimita[i] == timplimita[j]
    ** algoritmul Greedy nu are inversiuni deoarece sortam dupa timplimita 
    ** orice program fara inversiuni are aceeasi intarziere
    ** daca am avea inversiuni intr-un program, am avea 2 pozitii consecutive unde
    timpul limita ar scadea 
    ** cautam aceste 2 activitati consecutive si verificam daca le putem interschimba
    fara a incrementa intarzierea maxima
    ** prin interschimbare se schimba doar intarzierile la i si j, dar avand timplimita[i] <= timplimita[j],
    este evident ca obtinem o intarziere mai mica in ambele pozitii, deci nu incrementam
    intarzierea maxima prin acest procedeu
    ** pp ca G nu ar fi optim si luam G'cu numar minim de inversiuni fata de G un program
    optim.
        * daca nu ar avea inversiuni, am avea aceeasi intarziere ca la G => contradictie
        * daca am avea o singura inversiune i-j adiacenta, nu am creste intarzierea prin 
        interschimbarea lui i cu j
        => nu se mai poate optimiza G, deci este optima
*/