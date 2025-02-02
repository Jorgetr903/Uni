﻿// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66

#include <iostream>
#include <iomanip>
#include <fstream>
#include "set_eda.h"

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num, valor;
    std::cin >> num;
    if (num == 0)
        return false;

    set <int> cjto;
    for (int i = 0; i < num; i++) {
        std::cin >> valor;
        cjto.insert(valor);
    }

    std::cin >> num;
    for (int i = 0; i < num; i++) {
        std::cin >> valor;
        if (cjto.lower_bound(valor).first) std::cout << cjto.lower_bound(valor).second << '\n';
        else std::cout << "NO HAY\n";
    }
    std::cout << "---\n";
    
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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
