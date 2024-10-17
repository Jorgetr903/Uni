// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

// función que resuelve el problema
int resolver(std::vector<int> const& v, int numero, int ini, int fin) {
    if (ini == fin - 1) {
        if (v[ini] - ini == numero) return v[ini];
        else if (v[fin] - fin == numero) return v[fin];
        else return 0;
    }
    else {
        int mitad = (fin + ini) / 2;
        if (v[mitad] - mitad > numero) return resolver(v, numero, ini, mitad);
        else return resolver(v, numero, mitad, fin);
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int elementos, numero;
    std::cin >> elementos >> numero;
    std::vector<int> v(elementos);
    for (int i = 0; i < v.size(); i++) {
        std::cin >> v[i];
    }
    int sol1 = resolver(v, numero, 0, v.size());
    // escribir sol
    if (sol1 != 0) {
        std::cout << sol1 << '\n';
    }
    else std::cout << "NO" << '\n';
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