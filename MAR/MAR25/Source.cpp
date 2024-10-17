#include <iostream>
#include <iomanip>
#include <fstream>
#include "GrafoDirigidoValorado.h"
#include "cole.h"
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int intersecciones, calles;
    int i1, i2, longuitud;
    cin >> intersecciones >> calles;
    if (!std::cin)
        return false;

    DigrafoValorado<int> grafo(intersecciones);
    for (int i = 0; i < calles; i++) {
        cin >> i1 >> i2 >> longuitud;
        grafo.ponArista({ i1 - 1, i2 - 1, longuitud });
    }

    cole cole(grafo);

    cout << cole.sol();

    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}