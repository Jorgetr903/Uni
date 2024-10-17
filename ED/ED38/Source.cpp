// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
#include <queue>


bintree <int> acumular(bintree <int> const& arbol) {

    if (arbol.empty()) return bintree <int>();
    if (arbol.left().empty() && arbol.right().empty()) return arbol;
    else {
        bintree <int> iz = arbol.left();
        bintree <int> dr = arbol.right();
        if (!iz.empty() && !dr.empty()) {
            iz = acumular(iz);
            dr = acumular(dr);
            return bintree <int> (iz, iz.root() + dr.root(), dr);
        }
        else if (iz.empty() && !dr.empty()) {
            dr = acumular(dr);
            return bintree <int> (iz, dr.root(), dr);
        }
        else {
            iz = acumular(iz);
            return bintree <int>(iz, iz.root(), dr);
        }
    } 
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    auto arbol = leerArbol(-1);
    auto arbol2 = acumular(arbol);

    if (!arbol2.empty()) {
        std::vector<int> vector = arbol2.preorder();
        std::cout << vector[0];
        for (int i = 1; i < vector.size(); i++) {
            std::cout << ' ' << vector[i];
        }
        std::cout << '\n';
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