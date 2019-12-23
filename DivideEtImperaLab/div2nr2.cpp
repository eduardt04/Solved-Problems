#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");
/* folosim un hash pt a retine pozitia pe care apare nodul i in inordine */
unordered_map<int, int> hasht;
queue<int> preorder;
vector<int> post;
/* structura pt nodurile arborelui */
struct Node {
    int value;
    Node *left, *right;
    Node(int val) {
        value = val;
        left = NULL, right = NULL;
    }
};
/* functia care va construi arborele, explicata mai jos */
Node* build(int left, int right, int* pos) {
    /* cazul trivial */
    if(left > right)
        return NULL;
    /* cautam numarul care sa ne dea partitia folosind postordinea */
    int head = post[*pos];
    Node* nou = new Node(head);
    /* scadem indexul din parcurgerea din postordine, pentru a continua recursia
    corect si pentru a selecta bine urmatorul parinte */
    (*pos)--;
    /* daca partitia a ajuns la un singur element, il putem returna, deoarece
    el nu mai are alte noduri in stanga sau dreapta */
    if(left == right)
        return nou;
    /* daca nu am ajuns la o partitie de dimensiune 1, trebuie sa continuam
    partitionarea, cautand capatul in inordine, pentru a separa subarb stang
    de subarb drept */
    int pos_inord = hasht[head];
    /* acum trebuie sa partitionam in 2 nodurile ramase in inordine */
    nou->right = build(pos_inord + 1, right, pos);
    nou->left = build(left, pos_inord - 1, pos); 
    /* la final dupa ce constructia este terminata, returnam nodul care va fi
    de fapt radacina arborelui */
    return nou;
}

void preord(Node* curr) {
    if(curr == NULL)
        return;
    preorder.push(curr->value);
    preord(curr->left);
    preord(curr->right);
}

int main() {
    int n, i, x;
    fin>>n;
    /* citim inainte postordinea, apoi inordinea */
    for(i = 1; i <= n; i++) {
        fin>>x;
        post.push_back(x);
    }
    for(i = 0; i < n; i++) {
        fin>>x;
        hasht.insert(make_pair(x, i));
    }
    int p_pos = n - 1;
    Node* root = build(0, n - 1, &p_pos);
    preord(root);
    /* daca parcurgerile nu sunt bune algoritmul va mai pune 0-uri in plus si va creste
    dimensiune parcurgerii, de aceea verificam daca avem dimensiune n, inseamna ca
    parcurgerile au fost valide, daca nu, parcurgerile nu au fost bune */
    if(preorder.size() != n) 
        fout<<"parcurgerile nu sunt bune";
    else {
        while(!preorder.empty()) {
            fout<<preorder.front()<<" ";
            preorder.pop();
        }
    }
    return 0;
}
/*
*** idee de rezolvare: plecam de la niste concepte de teorie a parcurgerilor:
    ** in postordine(SDR), radacina arborelui va fi mereu ultimul element
    ** cautam aceasta radacina in parcurgerea in inordine(SRD), sa zicem ca este
    pe indexul i, atunci ce este de la 0 la i - 1 este subarborele stang, iar de
    la i + 1 la n - 1 subarborele drept, deci vom aplica o partitie a vectorului
    de inordine in 2, pentru a construi ambii subarbori.
    ** in continuare, dupa ce am luat radacina de pe pozitia n - 1 din vectorul
    de postordine, pe pozitia n - 2 vom gasi radacina subarborelui drept, pe care
    din nou o cautam in inordine, si daca in partitia curenta mai are numere
    in stanga si in dreapta, continuam sa construim subarborii
    ** vom aplica metoda de divide folosind o functie cu 3 indici:
        - left: indicele stang din partitia curenta a vectorului de inordine
        - right: indicele drept din partitia curenta a vect de inordine
        - pos: care este pozitia pe care am ajuns in postordine, plecand de la final
    ** practic la fiecare pas, pentru o radacina pe care o gasim in parcurgerea in
    postordine, mergem in inordine si vedem daca ea are subarbore stang sau drept,
    in caz pozitiv partitionam in functie de acestia, in caz negativ adaugam nodul
    curent la arbore.
    ** la inceput vom apela cu (0, n - 1, n - 1), deoarece nu avem nimic partitionat
    si incepem cu radacina (pos = n - 1 in postordine)
    ** cautam unde apare radacina pos[n - 1] in parcurgerea in inordine, fie 
    acest index pos_inord
    ** clar la stanga lui pos_inord avem nodurile din subarborele stang si
    la dreapta avem nodurile din subarborele drept, deci vom aplica recurenta
    pt stanga cu (left, pos_inord - 1, pos) si (pos_inord + 1, right, pos),
    astfel reducand problema la 2 subprobleme similare.
    ** cand left == right inseamna ca mai avem un singur nod de adaugat, deci
    il vom adauga direct (conditia de oprire )
    ** important: deoarece postordinea este SDR si noi parcurgem de la final spre
    inceput, este obligatoriu sa apelam recursia pentru subarborele drept
    prima data, deoarece in aceasta ordine apar nodurile, deci algoritmul
    va construi complet subarborele drept, apoi pe cel stang, deci prin vect
    de postordine iteram cu pos si de fiecare data vom scadea valoarea sa cu 1
    ** functia se va numi build si va avea ca return value un nod pentru a putea
    construi arborele, iar la final ea va returna radacina
    ** recursia se va face folosind nodul de la pasul curent si vom apela pentru
    nod->right si nod->left functia build.
    ** corectitudinea este data de elementele de teorie a parcurgerilor si din 
    modul in care acestea sunt efectuate, ni se garanteaza ca plecand de la final
    spre inceput in postordine vom gasi radacina arborelui, radacinile din subarborele
    drept, apoi cele din subarborele stang, apoi in inordine putem separa in functie
    de radacina in 2 sub vectori pt a construi in continuare
*** Complexitatea timp: O(n)
    ** Problema in varianta neoptimizata (cu o cautare secventiala a pozitiei radacinii
    in inordine), ar fi echivalenta cu o recursie de forma:
        T(n) = T(k) + T(n-k) + O(n)
    ** nu stim ca arborele ar fi echilibrat, deci nu putem presupune ca partitia
    va face un 2*n/2 sau n/k si k deoarece nu stim numarul exact de noduri, deci
    vom folosi n-k si k
    ** daca am folosi hash table pentru cautarea indicelui in postordine, O(n) va
    deveni O(1) deoarece toate operatiile din build se fac in timp constant
    ** vom folosi un hash table (unordered_map) unde pentru fiecare nod vom pune
    indicele sau din parcurgerea in inordine
    ** avand in vedere ca avem doar valori distincte, deci nu pot aparea coliziuni
    cand construim hash-ul, functia de hashing va fi optima si avand numar minim
    de "bucket-uri" cautarea va fi in medie O(1)
    ** Deci complexitatea va fi rezultatul recursiei:
        T(n) = T(k) + T(n-k) + O(1)
        Pp ca pentru orice n, T(n) este O(n) => T(n) <= cn - 1 ( este functie de gradul 1 deci
        ramanem in 0(n), dar ne simplifica demonstratia )
        Dem relatia si pentru n + 1
            T(n+1) = T(k) + T(n + 1 - k) + 1
            k si n + 1 - k sunt <= n, deci putem aplica presupunerea =>
            T(n+1) <= ck - 1 + c(n + 1 - k) - 1 + 1 <=> T(n+1) <= ck + cn + c - ck - 1 <=> 
            <=> T(n+1) <= cn + c - 1 <=> T(n+1) <= c(n+1) - 1 =>
        relatia se pastreaza si pt T(n+1) => inductie relatia este adevarata, deci
        recursia este O(n), la fel ca si complexitatea algoritmului.
*/