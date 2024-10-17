//Jorge Torres

#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"
using namespace std;

struct enfermo {
    int gravedad;
    string nombre;
    int llegada;
};

bool operator<(enfermo const& a, enfermo const& b) {
    return a.gravedad > b.gravedad || (a.gravedad == b.gravedad && a.llegada < b.llegada);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int eventos, gravedad;
    char caso;
    string nombre;

    cin >> eventos;
    if (eventos == 0)
        return false;

    PriorityQueue<enfermo> enfermos;

    for (int i = 0; i < eventos; i++) {
        cin >> caso;
        if (caso == 'I') {
            cin >> nombre >> gravedad;
            enfermos.push({ gravedad, nombre, i});
        }
        else { // caso == 'A'
            cout << enfermos.top().nombre << '\n';
            enfermos.pop();
        }
    }

    cout << "---\n";

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
