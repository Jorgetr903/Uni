// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
#include <queue>


std::pair <int, int> nodosAcumuladores(bintree <int> const& arbol) {
    int cont = 0;
    if (arbol.empty()) return {0, 0};
    if (arbol.left().empty() && arbol.right().empty()) {
        if (arbol.root() == 0) return { 1, arbol.root() };
        else return { 0, arbol.root() };
    }
    else {
        bintree <int> arbIz = arbol.left();
        bintree <int> arbDr = arbol.right();
        std::pair <int, int> iz, dr;
        if (!arbIz.empty() && !arbDr.empty()) {
            iz = nodosAcumuladores(arbIz);
            dr = nodosAcumuladores(arbDr);
        }
        else if (arbIz.empty() && !arbDr.empty()) {
            dr = nodosAcumuladores(arbDr);
        }
        else {
            iz = nodosAcumuladores(arbIz);
        }
        if (arbol.root() == iz.second + dr.second) cont++;
        cont += iz.first + dr.first;
        return { cont, iz.second + dr.second + arbol.root() };
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    auto arbol = leerArbol(-1);
    std::cout << nodosAcumuladores(arbol).first << '\n';
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