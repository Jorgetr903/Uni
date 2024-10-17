// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

// función que resuelve el problema
int resolver(std::vector<int> const& v, std::vector<int> const& w, int ini, int fin) {
    if (ini == fin) return v[ini]; // vector bacío
    else {
        if (ini == fin - 1) {
            if (w[ini] == v[ini]) return v[fin];
            else return v[ini];
        }
        else {
            int mitad = (fin + ini) / 2;
            if (w[mitad] > v[mitad]) return resolver(v, w, ini, mitad);
            else return resolver(v, w, mitad, fin);
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int elementos;
    std::cin >> elementos;
    std::vector<int> v(elementos);
    std::vector<int> w(elementos - 1);
    for (int i = 0; i < v.size(); i++) {
        std::cin >> v[i];
    }
    for (int i = 0; i < w.size(); i++) {
        std::cin >> w[i];
    }

    int sol1 = resolver(v, w, 0, w.size());
    // escribir sol

    std::cout << sol1 << '\n';
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