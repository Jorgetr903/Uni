#include <iostream>
#include <iomanip>
#include <fstream>
#include "GrafoValorado.h"
#include "bicicletas.h"
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int islas, puentes;
    int i1, i2, coste;
    cin >> islas >> puentes;

    if (!std::cin)
        return false;

    GrafoValorado<int> grafo(islas);

    for (int i = 0; i < puentes; i++) {
        cin >> i1 >> i2 >> coste;
        grafo.ponArista({ i1 - 1, i2 - 1, coste });
    }

    bicicletas bici(grafo, puentes);

    pair<int, bool> sol = bici.solucion();
    if (sol.second) {
        cout << sol.first << '\n';
    }
    else {
        cout << "No hay puentes suficientes\n";
    }
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