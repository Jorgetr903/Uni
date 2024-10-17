//Jorge Torres
//A66

#include <iomanip>
#include <fstream>
#include <iostream>
#include "linked_list_ed.h"

bool resuelveCaso() {
    // Lectura de datos
    int n;
    std::cin >> n;
    if (n == -1) return 0;
    linked_list_ed_plus<int> l;
    linked_list_ed_plus<int> lNegativos;
    for (int i = 0; i < n; ++i) {
        int valor; std::cin >> valor;
        l.push_back(valor);
    }
    // llamada a la función separar
    l.separar(lNegativos);
    // Para depurar
    l.rotar();
    lNegativos.rotar();
    // Mostrar resultados
    l.print();
    lNegativos.print();

    return true;
}


int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // Para restablecer entrada. 
#ifndef DOMJUDGE 
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}

