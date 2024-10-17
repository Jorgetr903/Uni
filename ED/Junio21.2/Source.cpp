// Problema El regreso de los enanos

// IMPORTANTE

// Nombre y apellidos del alumno
// Usuario del juez de clase
// Usuario que has utilizado en esta prueba


#include <iostream>
#include <fstream>
#include <string>
#include "bintree_eda.h"
using namespace std;
// Explicación del algoritmo



// Coste de la función. Para justificar el coste se debe indicar la recurrencia utilizada para calcularlo. Indicar el coste para árboles equilibrados y para árboles degenerados




// Aqui las funciones del alumno

pair<string, int> enanos(bintree<std::string> arbol) {
    if (arbol.empty()) return {};
    else if (arbol.left().empty() && arbol.right().empty()) return { arbol.root(), 1 };
    else {
        pair<string, int> Iz = enanos(arbol.left());
        pair<string, int> Dr = enanos(arbol.right());
        pair<string, int> sol;
        if (Iz.second > Dr.second) sol = { Iz.first, Iz.second + Dr.second };
        else if (Iz.second < Dr.second) sol = { Dr.first, Iz.second + Dr.second };
        else sol = { min(Iz.first, Dr.first), Iz.second + Dr.second };
        if (arbol.root() == "Orcos") sol = { sol.first, sol.second / 2 };
        return sol;
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    std::string vacio = ".";
    bintree<std::string> arbol = leerArbol(vacio);
    // LLamada a la función ue resuelve el problema
    pair<string, int> sol = enanos(arbol);

    // Escribir los resultados
    if (sol.second > 0) {
        cout << sol.first << " " << sol.second << '\n';
    }
    else {
        cout << "Ninguno\n";
    }
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos; std::cin >> numCasos; std::cin.ignore();
    for (int i = 0; i < numCasos; ++i) { resuelveCaso(); }

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}

