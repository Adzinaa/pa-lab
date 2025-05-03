// SPDX-License-Identifier: BSD-3-Clause

#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    // n = numar de noduri, m = numar de muchii/arce
    int n, m;

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
    vector<int> adj[NMAX];

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y; // arc (x, y)
            adj[x].push_back(y);
        }
        fin.close();
    }

    void dfsRec(vector<bool> &visited, int curr, stack<int> &s) {
        visited[curr] = true;

        for (int i : adj[curr]) {
            if(!visited[i]) {
                dfsRec(visited, i, s);
            }
        }

        s.push(curr);
    }


    vector<int> get_result() {
        // TODO: Faceti sortarea topologica a grafului stocat cu liste de adiacenta din adj.
        // *******
        // ATENTIE: nodurile sunt indexate de la 1 la n.
        // *******
        vector<int> topsort;

        vector<bool> visited (n + 1, false);
        //vreau sa stiu cand vizitez pereche nod - timp
        stack<int> s;

        for (int i = 1; i <= n; i++) {
            if(visited[i] == false) {
                    dfsRec(visited, i, s);
            }
        }

        while(!s.empty()) {
            int aux = s.top();
            topsort.push_back(aux);
            s.pop();
        }

        return topsort;
    }

    void print_output(const vector<int>& topsort) {
        ofstream fout("out");
        for (auto node : topsort) {
            fout << node << ' ';
        }
        fout << '\n';
        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main() {
    // * se aloca un obiect Task pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (nothrow) Task(); // hint: cppreference/nothrow
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
