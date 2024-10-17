#include <iostream>
#include <queue>
#include <vector>
#include "Digrafo.h"
using namespace std;

class Tareas {

private:
    deque<int> orden;
    vector<bool> visitados;
    vector<bool> apilado;
    bool hayciclo;

public:
    Tareas(Digrafo const& gr) : visitados(gr.V(), false), apilado(gr.V(), false), hayciclo(false) {
        for (int a = 1; a < gr.V(); a++) {
            if (!visitados[a]) {
                dfs(gr, a);
            }
        }
    };

    void dfs(Digrafo const& g, int n) {
        apilado[n] = true;
        visitados[n] = true;
        for (int w : g.ady(n)) {
            if (hayciclo) // si hemos encontrado un ciclo terminamos
                return;
            if (!visitados[w]) { // encontrado un nuevo vértice, seguimos
                dfs(g, w);
            }
            else if (apilado[w]) {
                hayciclo = true;
            }
        }
        apilado[n] = false;
        orden.push_front(n);
    }
    pair<deque<int>, bool> sol() const {
        pair<deque<int>, bool> s;
        s.first = orden;
        s.second = hayciclo;
        return s;
    }
};