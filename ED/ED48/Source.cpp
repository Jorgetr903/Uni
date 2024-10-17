//Jorge Torres
//A66

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

std::pair<int, int> caminoPares(bintree<int> const& a) {
    if (a.empty()) return { 0, 0 };
    else {
        pair<int, int> Iz = caminoPares(a.left()); // numero de pares, camino más largo de pares
        pair<int, int> Dr = caminoPares(a.right());

        int numPares = max(Iz.first, Dr.first);
        int caminoAct = Iz.first + Dr.first;
        if (a.root() % 2 == 0) {
            numPares++;
            caminoAct++;
        }
        else {
            numPares = 0;
            caminoAct = 0;
        }
        return { numPares, max({caminoAct, Iz.second, Dr.second}) };
    }
}

// Lee los datos y escribe el resultado
void resuelveCaso() {
    bintree<int> a = leerArbol(-1);
    pair<int, int> camino = caminoPares(a);
    std::cout << camino.second << '\n';
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
