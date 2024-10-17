// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "polinomio.h"

// funcio?n que resuelve el problema


// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio?n, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int grado, coef, numvariables;
    std::cin >> coef;
    if (!std::cin)
        return false;
    std::cin >> grado;
    polinomio p;

    while (grado != 0 || coef != 0) {
        p.monomio(coef, grado);
        std::cin >> coef;
        std::cin >> grado;
    }

    std::cin >> numvariables;
    int var;
    int puestos = 0;
    for (int i = 0; i < numvariables; i++) {
        std::cin >> var;
        long long int sol = p.resolver(var);
        std::cout << sol;
        if (puestos < numvariables - 1) {
            std::cout << " ";
        }
    }
    std::cout << '\n';

    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}