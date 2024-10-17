// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66

#include <iostream>
#include <iomanip>
#include <fstream>
#include "linked_list_ed_plus.h"

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int elementos;
    char c;
    std::cin >> elementos;
    if (elementos == -1)
        return false;

    linked_list_ed_plus <char> lista;

    for (int i = 0; i < elementos; i++) {
        std::cin >> c;
        lista.push_back(c);
    }

    lista.quitarRepetidos();
    lista.mostrar();

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
