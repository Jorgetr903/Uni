#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
using namespace std;

pair<int, int> bombillas_rec(vector<int> const& pot, vector<int> const& cost, int i, int j, Matriz<int>& m) {
    if (m[i][j] != -1) // subproblema ya resuelto
        return { m[i][j], j};
    if (i == 0 || j == 0)
        m[i][j] = 0;
    else if (pot[i - 1] > j)
        m[i][j] = bombillas_rec(pot, cost, i - 1, j, m).first;
    else
        m[i][j] = min(bombillas_rec(pot, cost, i - 1, j, m).first, bombillas_rec(pot, cost, i, j - pot[i - 1], m).first + cost[i - 1]);

    return {m[i][j], j};
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, Pmax, Pmin, pot, cost;
    cin >> n >> Pmax >> Pmin;

    if (!std::cin)
        return false;

    vector<int> potencias;
    vector<int> costes;

    for (int i = 0; i < n; i++) {
        cin >> pot;
        potencias.push_back(pot);
    }

    for (int i = 0; i < n; i++) {
        cin >> cost;
        costes.push_back(cost);
    }

    Matriz<int> m(n + 1, Pmax + 1, -1);

    pair<int, int> sol = bombillas_rec(potencias, costes, n, Pmax, m);

    if (sol.first == -1) {
        cout << "IMPOSIBLE\n";
    }
    else {
        cout << sol.first << " " << sol.second << '\n';
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