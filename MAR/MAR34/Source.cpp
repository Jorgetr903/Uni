#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

struct myclass
{
    bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) const
    {
        if (p1.first != p2.first)
        {
            return p1.first < p2.first;
        }
        return p1.second > p2.second;
    }
} mioperando;


int resolver(vector<pair<int, int>>& tareas, int ini, int fin) {
    sort(tareas.begin(), tareas.end(), mioperando);

    int tareasmin = 0;
    int tiempo_actual = ini;
    int i = 0;

    while (tiempo_actual < fin && i < tareas.size()) {
        if (tareas[i].first <= tiempo_actual) {
            int max_fin = -1;
            while (i < tareas.size() && tareas[i].first <= tiempo_actual) { //de los que no se pasan del instante actual cual dura más
                max_fin = max(max_fin, tareas[i].second);
                ++i;
            }
            tiempo_actual = max_fin;
            ++tareasmin;
        }
        else {
            // No hay tarea disponible para cubrir el tiempo actual
            return -1; // Indicar que no se puede cubrir todo el tiempo
        }
    }

    if (tiempo_actual >= fin) {
        return tareasmin;
    }
    else {
        return -1; // Indicar que no se puede cubrir todo el tiempo
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
    // leer los datos de la entrada
    int A, B, C;
    cin >> A >> B >> C;
    if (A == 0 && B == 0 && C == 0)
        return false;

    vector<pair<int, int>> tareas;
    while (C--)
    {
        int m1, m2;
        cin >> m1 >> m2;
        tareas.push_back({ m1, m2 });
    }
    auto sol = resolver(tareas, A, B);

    // escribir sol
    sol == -1 ? cout << "Imposible\n" : cout << sol << "\n";
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
