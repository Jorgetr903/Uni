#include <iostream>
#include <fstream>
#include "camiones.h"
using namespace std;


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int V, A;
    cin >> V >> A;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> grafo(V);
    for (int i = 0; i < A; i++) {
        int v1, v2, valor;
        cin >> v1 >> v2 >> valor;
        grafo.ponArista({ v1 - 1, v2 - 1, valor });
    }

    int consultas;
    cin >> consultas;

    for (int i = 0; i < consultas; i++) {
        int origen, destino, anchura;
        cin >> origen >> destino >> anchura;
        camiones c({ grafo, origen - 1, destino - 1, anchura });
        c.camino() ? cout << "SI\n" : cout << "NO\n";
    }

    // escribir sol

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}