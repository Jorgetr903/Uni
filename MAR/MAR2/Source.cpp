// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

struct avl {
    bool equilibrado;
    int maximo, minimo, nivel;
};

avl AVL(bintree<int> arb) {
    if (arb.empty()) return { true, 0, INT16_MAX, 0 };
    else {
        avl arbIz = AVL(arb.left());
        avl arbDr = AVL(arb.right());
        
        return {
            arbIz.equilibrado && arbDr.equilibrado && (abs(arbIz.nivel - arbDr.nivel) <= 1) && arbIz.maximo < arb.root() && arbDr.minimo > arb.root(),
            max(max(arbIz.maximo, arbDr.maximo), arb.root()),
            (arb.left().empty() && arb.right().empty()) ? arb.root() : min(min(arbIz.minimo, arbDr.minimo), arb.root()),
            max(arbIz.nivel, arbDr.nivel) + 1
        };
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    bintree<int> arbol;
    arbol = leerArbol(-1);
    // leer los datos de la entrada

    avl sol = AVL(arbol);
    if (sol.equilibrado) {
        cout << "SI" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    // escribir solución
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}