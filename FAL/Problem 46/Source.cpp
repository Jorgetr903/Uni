// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

int resolver(std::vector<int>& v, int ini, int fin) {
    int cambios = 0;
    int cambiosmezcla = 0;
    if (ini + 1 == fin) return cambios;
    else if (ini + 2 == fin) {
        if (v[ini] > v[ini + 1]) {
            std::swap(v[ini], v[ini + 1]);
            cambios++;
            return cambios;
        }
        else {
            return cambios;
        }
    }
    if (ini + 1 < fin) {
        int mitad = (ini + fin) / 2;
        int Iz = resolver(v, ini, mitad);
        int Dr = resolver(v, mitad, fin);

        int i = ini; int j = mitad;
        while (i < mitad && j < fin) {
            if (v[i] > v[j]) {
                cambiosmezcla += (mitad - i);
                j++;
            }
            else i++;
        }
        inplace_merge(v.begin() + ini, v.begin() + mitad, v.begin() + fin);
        return Iz + Dr + cambiosmezcla;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int naves;
    std::cin >> naves;
    if (!std::cin)
        return false;

    std::vector<int> v(naves);
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