// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Horas.h"

// función que resuelve el problema
int resolver(std::vector<Horas> const& tren, Horas const& consulta) {
    int ini = 0;
    int fin = tren.size();
    while (ini <= fin) {
        if (ini == fin) return fin;
        int m = (ini + fin) / 2;
        if (consulta < tren[m]) fin = m;
        else if (consulta == tren[m]) return m;
        else ini = m + 1;
    }
    return tren.size();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    Horas consulta;
    int trenes, horas;
    std::cin >> trenes >> horas;
    if (trenes == 0 && horas == 0)
        return false;

    std::vector<Horas> tren(trenes);
   
    for (int i = 0; i < trenes; i++) {
        std::cin >> tren[i];
    }
    for (int i = 0; i < horas; i++) {
        try {
            std::cin >> consulta;
            int pos = resolver(tren, consulta);
            if (pos < tren.size() && consulta <= tren[pos]) {
               std::cout << tren[pos];
            }
            else std::cout << "NO" << '\n';
        }
        catch (std::invalid_argument& ia) {
            std::cout << "ERROR" << '\n';
        }
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
