#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

struct myclass {
    bool operator()(std::pair<int, int> i, std::pair<int, int> j) {
        return i.second < j.second || (i.second == j.second && i.first < j.first);
    }
} mioperando;

// función que resuelve el problema
int resolver(vector<pair<int, int>>& casas)
{
    int numTunel = 1;
    sort(casas.begin(), casas.end(), mioperando);
    int lim = casas[0].second;

    for (int i = 1; i < casas.size(); i++) {
        if (casas[i].first >= lim) { // no entra en el tunel
            numTunel++;
            lim = casas[i].second;
        }
    }
    return numTunel;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int numEdif;
    cin >> numEdif;
    if (numEdif == 0)
        return false;

    vector<pair<int, int>> casas;
    while (numEdif--) {
        pair<int, int> edif;
        int m1, m2;
        cin >> m1 >> m2;
        casas.push_back({ m1, m2 });
    }
    int sol = resolver(casas);

    // escribir sol
    cout << sol << "\n";
    return true;
}

int main()
{
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save old buf and redirect std::cin to casos.txt
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
