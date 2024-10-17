// Nombre del alumno Jorge Torres
// Usuario del Juez MAR295

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <limits>
using namespace std;

struct Nodo {
    vector<int> sol;
    int nivel = 0;
    int tiempo = 0;
    int tiempo_opt = 0;
    vector<bool> asignado;
    bool operator<(Nodo const& otro) const {
        return otro.tiempo_opt <= tiempo_opt;
    }
};

std::pair<std::vector<int>, std::vector<int>> calculo_estimacion(const std::vector<std::vector<int>>& info) {
    vector<int> lento(info.size());
    vector<int> rapido(info.size());

    vector<int> opt(info.size());
    vector<int> pes(info.size());

    for (int i = 0; i < info.size(); i++) {
        auto maximo = std::max_element(info[i].begin(), info[i].end());
        auto minimo = std::min_element(info[i].begin(), info[i].end());

        lento[i] = *maximo;
        rapido[i] = *minimo;
    }

    opt[info.size() - 1] = 0;
    pes[info.size() - 1] = 0;

    for (int h = info.size() - 2; h >= 0; h--) {
        opt[h] = opt[h + 1] + rapido[h + 1];
        pes[h] = pes[h + 1] + lento[h + 1];
    }

    return { opt, pes };
}

// función que resuelve el problema
int resolver(vector<vector<int>> const& info, int const& maxi, int const& mini) {
    vector<int> optimista;
    vector<int> pesimista;

    int tiempo_mejor = 0;
    int sol_mejor = 0;
    auto estim = calculo_estimacion(info);
    optimista = estim.first;
    pesimista = estim.second;

    int N = info.size();

    Nodo _y; // NODO RAIZ

    _y.sol = vector<int>(N, -1);
    _y.nivel = -1;
    _y.tiempo = 0;
    _y.tiempo_opt = optimista[0];
    _y.asignado = vector<bool>(N, false);

    priority_queue<Nodo> cola;
    cola.push(_y);

    tiempo_mejor = pesimista[0];

    while (!cola.empty() && cola.top().tiempo_opt <= tiempo_mejor) {
        _y = cola.top();
        cola.pop();

        Nodo _x(_y); // CREAMOS UN HIJO

        _x.nivel++;

        // RECORRER LAS POSIBLES RAMAS

        for (int i = 0; i < N; i++) {
            if (!_x.asignado[i]) { // SI LA TAREA NO ESTÁ ASIGNADA SE ASIGNA
                _x.sol[_x.nivel] = i;
                _x.asignado[i] = true;
                _x.tiempo = _y.tiempo + info[_x.nivel][i]; // SUMAMOS TIEMPO ANTERIOR + TIEMPO MINISTRO EN HACER TAREA I
                _x.tiempo_opt = _x.tiempo + optimista[_x.nivel];

                if (_x.tiempo_opt <= tiempo_mejor) {
                    if (_x.nivel == N - 1) {
                        sol_mejor = _x.tiempo;
                        tiempo_mejor = _x.tiempo;
                    }
                    else {
                        cola.push(_x);
                        tiempo_mejor = min(tiempo_mejor, _x.tiempo + pesimista[_x.nivel]);
                    }
                }

                _x.asignado[i] = false;
            }
        }
    }
    return sol_mejor;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n == 0)
        return false;
    vector<vector<int>> info(n);
    int max = numeric_limits<int>::min();
    int min = std::numeric_limits<int>::max();
    for (int i = 0; i < n; i++) {
        for (int h = 0; h < n; h++) {
            int d;
            cin >> d;
            if (d < min) {
                min = d;
            }
            else if (d > max) {
                max = d;
            }
            info[i].push_back(d);
        }
    }
    int sol = resolver(info, max, min);

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