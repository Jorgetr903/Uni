// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

std::pair <int, int> aguaslimpias(bintree <int> const& arbol) {
    if (arbol.empty()) return { 0, 0 };
    if (arbol.left().empty() && arbol.right().empty()) return { 0, 1 };
    else {
        bintree <int> arbIz = arbol.left();
        bintree <int> arbDr = arbol.right();
        std::pair <int, int> iz, dr;
        iz = aguaslimpias(arbIz);
        dr = aguaslimpias(arbDr);
        int caudal = iz.second + dr.second - arbol.root();
        if (caudal >= 3) return { iz.first + dr.first + 1, caudal };
        if (caudal < 0) caudal = 0;
        else return { iz.first + dr.first, caudal };
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    auto arbol = leerArbol(-1);
    std::pair <int, int> sol = aguaslimpias(arbol);
    if (sol.second >= 3) sol.first--;
    std::cout << sol.first << '\n';
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