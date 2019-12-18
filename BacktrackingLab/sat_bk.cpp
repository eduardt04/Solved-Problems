/// SAT problem - backtracking version
/// Complexity - O(2ˆN)
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

bool sat_solution = false;
int n, m, unsatisfied_clauses;
vector<int> values, length, st;
vector<bool> satisfied;
vector<vector<int> >a;

void bk(int k) {
    if(k > n && unsatisfied_clauses)
        return;
    /// there are no more clauses to satisfy - we got a solution
    if(unsatisfied_clauses == 0) {
        cout<<"The boolean formula is satisfiable for the values: ";
        for(int i = 1; i <= n; i++)
            cout<<values[i]<<" ";
        cout<<endl;
        return;
    }
    for(int b = 0; b <= 1; b++) {
        /// assign false and true values to each variable - k is the current one
        values[k] = b;
        for(int i = 1; i <= m; i++)
            if(a[k][i] != 0 && satisfied[i] == false) {
                if((a[k][i] == -1 && values[k] == 0) || (a[k][i] == 1 && values[k] == 1)) {
                    satisfied[i] = true;
                    unsatisfied_clauses--;
                    bk(k+1);
                    unsatisfied_clauses++;
                    satisfied[i] = false;
                } 
                else {
                    st[k] = a[k][i];
                    a[k][i] = 0;
                    length[i]--;
                    if(length[i] == 0) {
                        unsatisfied_clauses--;
                        satisfied[i] = true;
                    }
                    else 
                        bk(k+1);
                    length[i]++;
                    if(length[i] == 1) {
                        unsatisfied_clauses++;
                        satisfied[i] = false;
                    }
                    a[k][i] = st[k];
                }
            }
    }
}

int main() {
    int i, j; /// n variables, m clauses
    fin>>n>>m;
    a.assign((n+1), vector<int>(m+1));

    /// numbers of variables in a clause - length
    length.assign(m+1, 0);

    /// a[i][j] = 1 if xi is included in the j-th clause
    /// a[i][j] = -1 if !xi is included in the j-th clause
    /// a[i][j] = 0 if neither xi nor !xi is included in the j-th clause
    
    string line;
    int current_line = 1;

    while(fin>>line) {
        if(line.compare("/") == 0) {
            current_line++;
            continue;
        }
        else if(line.compare("v") == 0)
            continue;
        else if(line[0] == '!') 
            a[line[2] - '0'][current_line] = -1;
        else 
            a[line[1] - '0'][current_line] = 1;
        length[current_line]++;
    }

    /// numbers of clauses that are yet to be satisfied - unsatisfied_clauses
    unsatisfied_clauses = m;
    /// values of each variable in backtracking
    values.assign(n+1, -1);
    /// satisfied[i] = clause i is satisfied
    satisfied.assign(m+1, false);
    st.assign(n+1, 0);

    bk(1);

    if(sat_solution == false)
        cout<<"The formula is non-satisfiable";
    return 0;
}