#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
using namespace std;

struct tesoros {
    int profundidad;
    int valor;
};

int cazatesoros_rec(vector<tesoros> const& tesr, int i, int j, Matriz<int>& m) {
    if (m[i][j] != -1) // subproblema ya resuelto
        return m[i][j];
    if (i == 0 || j == 0)
        m[i][j] = 0;
    else if (tesr[i - 1].profundidad * 3 > j)
        m[i][j] = cazatesoros_rec(tesr, i - 1, j, m);
    else
        m[i][j] = max(cazatesoros_rec(tesr, i - 1, j, m), cazatesoros_rec(tesr, i - 1, j - tesr[i - 1].profundidad * 3, m) + tesr[i - 1].valor);

    return m[i][j];
}

int cazatesoros(vector<tesoros> const& tesr, int M, vector<bool>& sol) {
    int n = tesr.size();
    Matriz<int> m(n + 1, M + 1, -1);
    int valor = cazatesoros_rec(tesr, n, M, m);
    // cálculo de los objetos
    int i = n, j = M;
    sol = vector<bool>(n, false);
    while (i > 0 && j > 0) {
        if (m[i][j] != m[i - 1][j]) {
            sol[i - 1] = true;
            j = j - 3 * tesr[i - 1].profundidad;
        }
        i--;
    }
    return valor;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int oxigeno, cofres, prof, valor;
    cin >> oxigeno >> cofres;

    if (!std::cin)
        return false;

    vector<tesoros> tesr;
    vector<bool> sol;
    vector<int> sol2;

    for (int i = 0; i < cofres; i++) {
        cin >> prof >> valor;
        tesr.push_back({ prof, valor });
    }

    int oro = cazatesoros(tesr, oxigeno, sol);
    cout << oro << '\n';
    
    for (int i = 0; i < sol.size(); i++) {
        if (sol[i] == true)
            sol2.push_back(i);
    }

    cout << sol2.size() << '\n';

    for (int i = 0; i < sol2.size(); i++) {
        cout << tesr[sol2[i]].profundidad << " " << tesr[sol2[i]].valor << '\n';
    }

    cout << "---" << '\n';

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