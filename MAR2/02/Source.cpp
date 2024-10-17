#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"
using namespace std;


vector<int> devolver_dardos(vector<int> const& M, int C) {
    int n = M.size();
    Matriz<EntInf> dardos(n + 1, C + 1, Infinito);
    dardos[0][0] = 0;

    //rellenamos la matriz
    for (int i = 1; i <= n; ++i) {
        dardos[i][0] = 0;
        for (int j = 1; j <= C; ++j)
            if (M[i - 1] > j)
                dardos[i][j] = dardos[i - 1][j];
            else
                dardos[i][j] = min(dardos[i - 1][j], dardos[i][j - M[i - 1]] + 1);
    }

    vector<int> sol;
    if (dardos[n][C] != Infinito) {
        int i = n, j = C;
        while (j > 0 && i > 0) { // no se ha pagado todo
            if (M[i - 1] <= j && dardos[i][j] != dardos[i - 1][j]) {
                // tomamos una moneda de tipo i
                sol.push_back(M[i - 1]); j = j - M[i - 1];
            }
            else { // no tomamos más dardos de tipo
                i--;
            } 
        }
    }
    return sol;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int valor, sectores, p;
    cin >> valor >> sectores;
    if (!std::cin)
        return false;
    vector<int> puntos(sectores);

    for (int i = 0; i < sectores; i++) {
        cin >> p;
        puntos.push_back(p);
    }

    vector<int> sol = devolver_dardos(puntos, valor);

    if (sol.empty()) {
        cout << "Imposible\n";
    }
    else {
        cout << sol.size() << ":";
        for (int i = 0; i < sol.size(); i++) {
            cout << " " << sol[i];
        }
        cout << '\n';
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