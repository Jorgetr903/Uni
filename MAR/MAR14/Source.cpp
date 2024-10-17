// Jorge Torres

#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"
using namespace std;

int dfs(Grafo const& g, int v, vector<bool> &visitado) {
    visitado[v] = true;
    int tam = 1;
    for (int i : g.ady(v)) {
        if (!visitado[i]) {
            tam += dfs(g, i, visitado);
        }
    }
    return tam;
}

int maxGrupoAmigos(Grafo const& g) {
    vector<bool> visitado(g.V(), false);
    int maximo = 0;
    for (int i = 0; i < g.V(); i++) {
        if (!visitado[i]) {
            int tam = dfs(g, i, visitado);
            maximo = max(maximo, tam);
        }
    }
    return maximo;
}


void resuelveCaso() {
    int personas, pares, amigo1, amigo2;
    cin >> personas >> pares;

    Grafo grafo = Grafo(personas);

    for (int i = 0; i < pares; i++) {
        cin >> amigo1 >> amigo2;
        grafo.ponArista(amigo1 - 1, amigo2 - 1);
    }

    int sol = maxGrupoAmigos(grafo);

    cout << sol << '\n';
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


    unsigned int numCasos;
    std::cin >> numCasos;
    // Resolvemos
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }


#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}