// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
#include <queue>

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracion, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    char caso;
    std::cin >> caso;
    std::pair <int, int> sol;
    if (caso == 'N') {
        int valor;
        std::cin >> valor;
        auto arbol = leerArbol(-1);
        sol = arbol.resolver(valor);
    }
    else {
        char valor;
        std::cin >> valor;
        auto arbol = leerArbol('.');
        sol = arbol.resolver(valor);
    }
    // escribir sol
    if (sol.first >= 2) {
        std::cout << sol.second << '\n';
    }
    else {
        std::cout << "NO EXISTE" << '\n';

    }
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}