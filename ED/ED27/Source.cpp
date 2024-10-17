// Nombre del alumno:
// Usuario del Juez:


#include <iostream>
#include <iomanip>
#include <fstream>

#include "list_eda.h"


template <class T>
T Mysearch(T const& ini1, T const& fin1, T const& ini2, T const& fin2) {
    auto it1 = ini1; auto it2 = ini2;
    while (it1 != fin1 && it2 != fin2) {
        if (*it1 == *ini2) { // recorre el subrango
            auto aux1 = it1; it2 = ini2;
            while (aux1 != fin1 && it2 != fin2 && *aux1 == *it2) {
                ++aux1;
                ++it2;
            }
            if (it2 != fin2) ++it1;
        }
        else ++it1;
    }
    return it1;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    list<int> lista1;
    list<int> lista2;

    int N1, N2, valor;
    std::cin >> N1 >> N2;
    if (N1 == 0 && N2 == 0)
        return false;

    for (int i = 0; i < N1; i++) {
        std::cin >> valor;
        lista1.push_back(valor);
    }

    for (int i = 0; i < N2; i++) {
        std::cin >> valor;
        lista2.push_back(valor);
    }
    auto ini1 = lista1.begin();

    while (ini1 != lista1.end()) {
        auto it = Mysearch(ini1, lista1.end(), lista2.begin(), lista2.end());

        if (it != lista1.end()) {
            for (int i = 0; i < N2; i++) {
                it = lista1.erase(it);
            }
        }
        ini1 = it;
    }
    
    // Escribe la lista
    auto it = lista1.begin();
    if (it != lista1.end()) {
        std::cout << *it;
        ++it;
    }
    for (; it != lista1.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
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
