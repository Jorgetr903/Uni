﻿// Nombre del alumno: Jorge Tores
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int accidentes, victimas;
    std::string expr;

    std::cin >> accidentes;
    if (!std::cin)
        return false;

    std::stack<std::pair <std::string, int>> pila;
    for (int i = 0; i < accidentes; i++) {
        std::cin >> expr >> victimas;
        if (pila.empty()) {
            pila.push({ expr, victimas });
            std::cout << "NO HAY\n";
        }
        else {
            while (!pila.empty() && pila.top().second <= victimas) pila.pop();
            if (pila.empty()) std::cout << "NO HAY\n";
            else std::cout << pila.top().first << '\n';
            pila.push({ expr , victimas });
        }
    }
    std::cout << "---\n";
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