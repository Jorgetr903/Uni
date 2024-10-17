//Jorge Torres

#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"
using namespace std;

struct Caja {
    int num;
    int espera;

    bool operator<(const Caja& other) const {
        if (espera == other.espera) {
            return num < other.num;
        }
        return espera < other.espera;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int cajas, clientes, tiempo;
    cin >> cajas >> clientes;
    if (cajas == 0 && clientes == 0)
        return false;

    PriorityQueue<Caja> cola;
    for (int i = 0; i < clientes; i++) {
        cin >> tiempo;

        if (cola.size() < cajas) {
            cola.push({ cola.size() + 1, tiempo });
        }
        else {
            Caja caja = cola.top();
            cola.pop();
            caja.espera += tiempo;
            cola.push(caja);
        }
    }

    if (cola.size() < cajas) {
        cout << cola.size() + 1 << '\n';
    }
    else {
        cout << cola.top().num << '\n';
    }
    
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
