#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
using namespace std;

int aibofobia_rec(string const& c, int i, int j, Matriz<int>& m) {
    int& res = m[i][j];
    if (res == -1) {
        if (i == j) res = 0;
        else if (i > j) res = 0;
        else {
            if (c[i] == c[j]) {
                res = aibofobia_rec(c, i + 1, j - 1, m);
            }
            else {
                res = min(aibofobia_rec(c, i + 1, j, m), aibofobia_rec(c, i, j - 1, m)) + 1;
            }
        }
    }
    return res;
}

void reconstruir(string const& c, Matriz<int> const& m, int i, int j, string& sol) {
    if (i <= j) {
        if (i == j) {
            sol.push_back(c[i]);
        }
        else if (c[i] == c[j]) {
            sol.push_back(c[i]);
            reconstruir(c, m, i + 1, j - 1, sol);
            sol.push_back(c[j]);
        }
        else if (m[i][j] == m[i + 1][j] + 1) {
            sol.push_back(c[i]);
            reconstruir(c, m, i + 1, j, sol);
            sol.push_back(c[i]);
        }
        else {
            sol.push_back(c[j]);
            reconstruir(c, m, i, j - 1, sol);
            sol.push_back(c[j]);
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    string cadena;
    cin >> cadena;
    if (!std::cin)
        return false;

    int n = cadena.length();

    Matriz<int> matriz(n + 1, n + 1, -1);

    // escribir sol

    int anadir = aibofobia_rec(cadena, 0, n - 1, matriz);
    string sol;
    reconstruir(cadena, matriz, 0, n - 1, sol);
    cout << anadir << " " << sol << '\n';
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