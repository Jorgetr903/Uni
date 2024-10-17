// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Pelicula.h"

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int numPeliculas;
    std::cin >> numPeliculas;
    if (numPeliculas == 0)
        return false;

    std::vector<Pelicula> peliculas(numPeliculas);
    for (int i = 0; i < numPeliculas; i++) {
        std::cin >> peliculas[i];
    }

    std::sort(peliculas.begin(), peliculas.end());

    // escribir sol
    for (int i = 0; i < peliculas.size(); i++) {
        std::cout << peliculas[i];
    }
    std::cout << "---" << '\n';
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
