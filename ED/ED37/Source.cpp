// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
#include <queue>

std::pair<int, int> barreraPrimos(bintree <int> const& arbol) {
    std::queue <std::pair <int, bintree <int>>> cola;
    if (!arbol.empty())
    cola.push({ 1, arbol });
    while (!cola.empty()) {
        auto const& par = cola.front();
        auto const& a = par.second;
        bool primo = true;
        
        for (int i = 2; i <= a.root() / 2; i++) {
            if (a.root() % i == 0) {
                primo = false;
                i = a.root();
            }
        }
        if (!primo) {
            if (a.root() % 7 == 0) {
                return { a.root(), par.first };
            }
            if (!a.left().empty()) {
                cola.push({ par.first + 1 , a.left() });
            }
            if (!a.right().empty()) {
                cola.push({ par.first + 1 , a.right() });
            }
        }
        cola.pop();
    }
    return { 0, 0 };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    std::pair <int, int> sol;
    auto arbol = leerArbol(-1);
    sol = barreraPrimos(arbol);
    if (sol.first > 0) {
        std::cout << sol.first << " " << sol.second << '\n';
    }
    else {
        std::cout << "NO HAY" << '\n';
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