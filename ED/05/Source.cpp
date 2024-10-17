// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "linked_list_ed_plus.h"

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    std::string c;
    std::cin >> c;

    if (!std::cin) return false;

    linked_list_ed_plus <std::string> lista;
    std::string str;
    getline(std::cin, str); // para saltar el final de linea
    getline(std::cin, str); // lee la linea del caso
    std::stringstream ss(str); // construye el objeto ss de tipo stringstream
    while (ss) {
        std::string aux;
        ss >> aux;
        lista.push_back(aux);
    }
    lista.mostrarPropiedad(empiezaPor(c));

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