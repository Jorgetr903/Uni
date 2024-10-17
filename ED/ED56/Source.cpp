// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

std::pair<std::string, int> enanos(bintree<std::string> arbol) {
    if (arbol.empty()) return {};
    else if (arbol.left().empty() && arbol.right().empty()) return { arbol.root(), 1 };
    else {
        std::pair<std::string, int> Iz = enanos(arbol.left());
        std::pair<std::string, int> Dr = enanos(arbol.right());
        std::pair<std::string, int> sol;
        if (Iz.second > Dr.second) sol = { Iz.first, Iz.second + Dr.second };
        else if (Dr.second > Iz.second) sol = { Dr.first, Iz.second + Dr.second };
        else sol = { min(Iz.first, Dr.first), Iz.second + Dr.second };
        if (arbol.root() == "Orcos") return { sol.first, sol.second / 2 };
        else return sol;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    std::string a = ".";
    bintree<std::string> arbol = leerArbol(a);
    std::pair<std::string, int> sol = enanos(arbol);
    if (sol.second == 0) {
        cout << "Ninguno \n";
    }
    else {
        cout << sol.first << " " << sol.second << '\n';
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