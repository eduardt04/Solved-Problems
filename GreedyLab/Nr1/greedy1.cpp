#include <fstream>
#include <vector>
#include <stack>
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");
struct interval {
    int left, right;
    interval(int a, int b) {
        left = a, right = b;
    }
};
/* functie de comparare pentru sort, sortam crescator dupa x, crescator dupa lungime */
bool comparer(const interval &a, const interval &b) {
    if(a.left < b.left)
        return true;
    if(a.left == b.left && a.right < b.right)
        return true;
    return false;
}
/* functie care verifica daca a inclus in b ex: [3,7] inclus in [1,12] */
bool included_in(const interval &a, const interval &b) {
    return (a.left >= b.left && a.right <= b.right);
}
/* functie care verifica daca a intersecteaza "in dreapta" b ex: [3,7] inters dreapta [5,12] in [5,7] */
bool right_to(const interval &a, const interval &b) {
    return (a.left <= b.left && a.right <= b.right && a.right >= b.left);
}
int main() {
    int n, i, x, y, a, b, ct;
    vector<interval> v;
    fin>>a>>b>>n;
    interval goal(a, b);
    for(i = 1; i <= n; i++) {
        fin>>x>>y;
        /* tratam cazul trivial cand avem deja un interval care include [a,b] */
        if(included_in(goal, *(new interval(x, y)))) {
            fout<<x<<" "<<y<<endl;
            return 0;
        }
        v.push_back(*(new interval(x, y)));
    }
    /* sortam intervalele */
    sort(v.begin(), v.end(), comparer);
    /* tratam cazul in care nu se poate efectua o reuniune care sa contina [a,b] */
    /* avand sortat crescator dupa x si lungime, daca nu avem primul interval cu x mai mic sau egal cu a
    si ultimul interval cu y mai mare sau egal b, nu putem face o reuniune sa contina [a,b] */
    if(v[0].left > a && v[n-1].right < b) {
        fout<<-1;
        return 0;
    }
    /* retinem intervalele cautate intr-o stiva */
    stack<interval> sol;
    /* adaugam primul interval in solutie */
    sol.push(v[0]);
    ct = v[0].right;
    for(i = 1; i < n; i++) {
        /* daca intervalul din solutie este inclus in intervalul actual, eliminam intervalul din solutie */
        if(included_in(sol.top(), v[i]) && !sol.empty())
            sol.pop();
        /* mutam primul interval cat se poate de aproape de a cu capatul din stanga, pentru a optimiza solutia */
        if(!sol.empty())
            if(right_to(sol.top(), v[i]) && v[i].left <= a)
                sol.pop();
        /* in ct vom tine y-ul pana la care am ajuns cu intervalele pana la noua adaugare */
        /* de ex daca avem [3,8], [6, 15], ct va tine 8 in ideea ca dupa [6,15] poate aparea
        [7,18] care va imbunatati solutia, dar trebuie verificat ca x-ul sa nu depaseasca y-ul
        cel dinainte, care va fi retinut in ct */
        if(!sol.empty())
            if(right_to(sol.top(), v[i]) && v[i].left <= ct && sol.size() > 1)
                sol.pop();
        /* daca nu avem intervale in solutie(se poate intampla la primul pas) */
        if(sol.empty()) {
            ct = v[i].right;
            sol.push(v[i]);
        }
        else 
            if(!included_in(v[i], sol.top())) {
                ct = sol.top().right;
                sol.push(v[i]);
            }
        /* daca am depasit deja cu y-ul b, nu mai are sens sa continuam parcurgerea,
        am gasit deja reuniunea de cardinal minim */
        if(sol.top().right >= b)
            break;
    }
    while(!sol.empty()) {
        fout<<sol.top().left<<" "<<sol.top().right<<endl;
        sol.pop();
    }
    return 0;
}
/* 
*** ideea agoritmului este de a alege succesiv intervalele din stanga lui a cu un 
capat in [a,b] la inceput, pana il alegem pe cel cu capat maxim in stanga lui a 
si cu lungimea intervalului maxima. apoi noul y devine a(ct) si cauta noul interval
cu capat maxim in stanga lui ct si cu lungime maxima. algoritmul se va opri cand 
un capat drept al intervalului ales depaseste b.

*** retinem pe rand intervalele in solutia temporara intr-o stiva fie [sa, sb] intervalul 
curent din varful stivei si [va, vb] cel de la pasul curent in vector.

*** [va, vb] va inlocui [sa, sb] in stiva daca;
- [va, vb] contine [sa, sb], deci clar imbunatateste solutia
- va <= a, sa <= a si vb >= sb, deci ambele sunt in stanga intervalului [a,b], dar 
[va, vb] cuprinde o parte mai mare din [a,b]
- [va, vb] se afla la dreapta lui [sa, sb], dar nu este disjunct cu intervalul aflat
inaintea lui [sa, sb] in solutie, adica va <=ct din algoritm

*** alegand mereu intervalul maxim ca lungime dar si ca valoare a lui x ne garanteaza
ca vom obtine o reuniune de cardinal minim.

*** Complexitatea timp: O(nlogn) data de sortarea vectorului.
(am folosit sort pentru simplitatea scrierii, se putea folosi qsort, dar
am preferat sa ma axez pe metoda greedy nu pe comanda din cstdlib)
Constructia stivei se face in O(n) deoarece fiecare interval este adaugat si eliminat
maxim o singura data pe parcursul algoritmului. 
*/