// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

// función que resuelve el problema
bool resolver(std::vector<int> const& v, int k, int ini, int fin) {
    if (ini + 1 == fin) return true; // Un elemento
    else { // Dos o más elementos
        int mitad = (ini + fin) / 2;
        bool Iz = resolver(v, k, ini, mitad);
        bool Dr = resolver(v, k, mitad, fin);
        return Iz && Dr && k <= abs(v[ini] - v[fin - 1]);
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int elementos, k;
    std::cin >> elementos >> k;
    if (!std::cin)
        return false;

    std::vector<int> v(elementos);
    for (int i = 0; i < v.size(); i++) {
        std::cin >> v[i];
    }

    if (resolver(v, k, 0, v.size())) std::cout << "SI\n";
    else std::cout << "NO\n";

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