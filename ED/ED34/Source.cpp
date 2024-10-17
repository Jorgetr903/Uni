// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

pair <int, int> diametro(bintree <char>& arbol) {
    if (arbol.empty()) return {0, 0};
    int diam = 0;

    pair <int, int> iz = { 0, 0 }, dr = { 0, 0 };
    bintree <char> arbIz = arbol.left();
    bintree <char> arbDr = arbol.right();
    iz = diametro(arbIz);
    dr = diametro(arbDr);
    diam = max(max(iz.first, dr.first), iz.second + dr.second + 1);
    return { diam, max(iz.second, dr.second) + 1};
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada

    bintree <char> arbol = leerArbol('.');
    // escribir sol
    cout << diametro(arbol).first << '\n';

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