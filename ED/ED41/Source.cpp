// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

std::pair <bool, std::pair <int, int>> binarioBusqueda(bintree <int> const& arbol) {
    if (arbol.empty()) return { true, {} };
    if (arbol.left().empty() && arbol.right().empty()) return { true, {arbol.root(), arbol.root()} };
    else {
        bintree <int> arbIz = arbol.left();
        bintree <int> arbDr = arbol.right();
        std::pair <bool, std::pair <int, int>> iz, dr;
        if (!arbIz.empty() && !arbDr.empty()) {
            iz = binarioBusqueda(arbIz);
            dr = binarioBusqueda(arbDr);
            return { iz.first && dr.first && arbol.root() > iz.second.second && arbol.root() < dr.second.first, {std::min(std::min(iz.second.first, dr.second.first), arbol.root()), std::max(std::max(iz.second.second, dr.second.second), arbol.root()) } };
        }
        else if (arbIz.empty() && !arbDr.empty()) {
            dr = binarioBusqueda(arbDr);
            return{ dr.first && arbol.root() < dr.second.first, {std::min(dr.second.first, arbol.root()), std::max(dr.second.second, arbol.root()) } };
        }
        else {
            iz = binarioBusqueda(arbIz);
            return{ iz.first && arbol.root() > iz.second.second, {std::min(iz.second.first, arbol.root()), std::max(iz.second.second, arbol.root()) } };
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    auto arbol = leerArbol(-1);
    if (binarioBusqueda(arbol).first) std::cout << "SI\n";
    else std::cout << "NO\n";
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