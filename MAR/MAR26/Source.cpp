#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "GrafoDirigidoValorado.h"
#include "web.h"
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int paginas, tiempo, enlaces, pag, pag2;
    
    cin >> paginas;
    if (paginas == 0)
        return false;

    vector<int> tiempos(paginas);
    DigrafoValorado<int> grafo(paginas);

    for (int i = 0; i < paginas; i++) {
        cin >> tiempos[i];
    }
    cin >> enlaces;

    for (int i = 0; i < enlaces; i++) {
        cin >> pag >> pag2 >> tiempo;
        tiempo += tiempos[pag2 - 1];
        if (pag == 1) {
            tiempo += tiempos[pag - 1];
        }
        grafo.ponArista({ pag - 1, pag2 - 1, tiempo });
    }

    web web(grafo);
    
    int sol = web.sol(grafo.V() - 1);
    if (sol != -1) {
        cout << sol << '\n';
    }
    else {
        cout << "IMPOSIBLE\n";
    }

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
