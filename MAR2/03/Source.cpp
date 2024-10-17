#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
using namespace std;

pair<int, int> relllenar_matriz(Matriz<int> m, int n) {
    int max_total = 0, casilla;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < n; j++) {
            int max = m[i][j];
            if (j - 1 >= 0 && (max < m[i][j] + m[i - 1][j - 1])) {
                max = m[i][j] + m[i - 1][j - 1];
            }
            if (max < m[i][j] + m[i - 1][j]) {
                max = m[i][j] + m[i - 1][j];
            }
            if (j + 1 < n && (max < m[i][j] + m[i - 1][j + 1])) {
                max = m[i][j] + m[i - 1][j + 1];
            }
            m[i][j] = max;
            if (max_total < max) {
                max_total = max;
                casilla = j + 1;
            }
        }
    }
    return { max_total, casilla };
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, valor, casilla, max = 0;
    cin >> n;

    if (!std::cin)
        return false;
    Matriz<int> tablero(n, n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> valor;
            tablero[i][j] = valor;
        }
    }

    //llamada para completar matriz
    pair<int, int> sol = relllenar_matriz(tablero, n);

    cout << sol.first << " " << sol.second << '\n';

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