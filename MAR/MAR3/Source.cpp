
#include <iostream>
#include <iomanip>
#include <fstream>
#include "TreeSet_AVL.h"
#include <list>
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int claves, num, k1, k2;
    cin >> claves;
    if (claves == 0)
        return false;

    Set<int> arbol;
    for (int i = 0; i < claves; i++) {
        cin >> num;
        arbol.insert(num);
    }

    cin >> k1 >> k2;
    list<int> sol = arbol.elementosEntre(k1, k2);

    for (int elem : sol) {
        cout << elem << " ";
    }
    cout << endl;
    // escribir sol

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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
