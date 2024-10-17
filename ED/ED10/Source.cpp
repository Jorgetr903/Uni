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
    int num, num1, num2;
    linked_list_ed_plus <int> lista;
    linked_list_ed_plus <int> lista2;

    std::cin >> num;
    num1 = num;
    while (num != 0) {
        lista.push_back(num);
        std::cin >> num;
    }

    std::cin >> num;
    num2 = num;
    while (num != 0) {
        lista2.push_back(num);
        std::cin >> num;
    }

    if (num1 < num2) {
        lista.mezclar(lista2);
        lista.mostrar();
    }
    else {
        lista2.mezclar(lista);
        lista2.mostrar();
    }

    return true;

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