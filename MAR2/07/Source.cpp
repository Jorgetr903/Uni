#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
using namespace std;

int subsecuencia_rec(string const& c1, string const& c2, int i, int j, Matriz<int> & m) {
    int& res = m[i][j]; // para no tener que escribir todo el rato
    if (res == -1) {
        
        if (i == c1.length() || j == c2.length())
            res = 0;
        else if (c1[i] == c2[j])
            res = subsecuencia_rec(c1, c2, i + 1, j + 1, m) + 1;
        else
            res = max(subsecuencia_rec(c1, c2, i + 1, j, m), subsecuencia_rec(c1, c2, i, j + 1, m));
    }
    return res;
}

void reconstruir(string const& c1, string const& c2, Matriz<int> const& m, int i, int j, string& sol) {
    if (i == c1.length() || j == c2.length()) return;
    else if (c1[i] == c2[j]) {
        sol.push_back(c1[i]);
        reconstruir(c1, c2, m, i + 1, j + 1, sol);
    }
    else if (m[i][j] == m[i + 1][j])
        reconstruir(c1, c2, m, i + 1, j, sol);
    else
        reconstruir(c1, c2, m, i, j + 1, sol);
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    string cadena1, cadena2;
    cin >> cadena1 >> cadena2;
    if (!std::cin)
        return false;

    int n = cadena1.length();
    int m = cadena2.length();

    Matriz<int> matriz(n + 1, m + 1, -1);

    // escribir sol

    subsecuencia_rec(cadena1, cadena2, 0, 0, matriz);
    string sol;
    reconstruir(cadena1, cadena2, matriz, 0, 0, sol);
    cout << sol << '\n';
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