// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

// función que resuelve el problema
int resolver(std::vector<int> const& v, int ini, int fin) {
    if (ini + 1 == fin) return v[ini];
    else if (ini + 2 == fin) {
        if (v[ini] % 2 == 0) return v[ini + 1];
        else return v[ini];
    }
    else {
        int mitad = (ini + fin) / 2;
        if (v[mitad] == v[ini] + 2 * mitad) return resolver(v, mitad, fin);
        else return resolver(v, ini, mitad + 1);
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int elementos;
    std::cin >> elementos;
    if (elementos == 0)
        return false;
    std::vector<int> v(elementos);
    for (int i = 0; i < v.size(); i++) {
        std::cin >> v[i];
    }
    int sol = resolver(v, 0, v.size());

    // escribir sol
    std::cout << sol << '\n';
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
