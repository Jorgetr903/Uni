#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <limits>
using namespace std;

struct nodo {
    vector<int> sol;
    vector<bool> marcas;
    int calidad, calidadOpt, nivel;

    bool operator<(nodo const& otro) const {
        return calidadOpt > otro.calidadOpt;
    }
};

int estimacion(vector<int> const& calidadMaxCarro, nodo const& y) {
    int est = y.calidad;

    for (int i = y.nivel + 1; i < calidadMaxCarro.size(); i++) {
        est += calidadMaxCarro[i];
    }
    return est;
}

int resolver(vector<vector<int>> const& calidades, vector<int> const& anchuraCarre, vector<int>const& anchuraCarro, vector<int> const& calidadMaxCarro) {

    int numCarros = anchuraCarro.size();
    int numCaminos = anchuraCarre.size();
    int calidadMejor = 0;
    nodo _y;

    _y.calidad = 0;
    _y.nivel = -1;
    _y.calidadOpt = estimacion(calidadMaxCarro, _y);
    _y.marcas = vector<bool>(numCaminos, false);
    _y.sol = vector<int>(numCarros);

    priority_queue<nodo> cola;

    cola.push(_y);

    while (!cola.empty() && cola.top().calidadOpt >= calidadMejor) {
        _y = cola.top();
        cola.pop();

        nodo _x(_y);
        _x.nivel++;
        for (int i = 0; i < numCaminos; i++) {
            if (!_x.marcas[i] && anchuraCarre[i] >= anchuraCarro[_x.nivel]) {
                _x.sol[_x.nivel] = i;
                _x.marcas[i] = true;
                _x.calidad = _y.calidad + calidades[_x.nivel][i];
                _x.calidadOpt = estimacion(calidadMaxCarro, _x);

                if (_x.nivel == numCarros - 1) {
                    if (_x.calidad > calidadMejor) {
                        calidadMejor = _x.calidad;
                    }
                }
                else {
                    if (_x.calidadOpt > calidadMejor) {
                        cola.push(_x);
                        calidadMejor = max(calidadMejor, _x.calidad);
                    }
                }
                _x.marcas[i] = false;
            }
        }
        //El carro no sale a la calle
        _x.calidad = _y.calidad;
        _x.calidadOpt = estimacion(calidadMaxCarro, _x);
        _x.sol[_x.nivel] = -1;

        if (_x.nivel == numCarros - 1) {
            if (_x.calidad > calidadMejor) {
                calidadMejor = _x.calidad;
            }
        }
        else {
            if (_x.calidadOpt > calidadMejor) {
                cola.push(_x);
                calidadMejor = max(calidadMejor, _x.calidad);
            }
        }
    }
    return calidadMejor;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada

    int n, m;
    cin >> n >> m;

    vector<int> anchurascarros;

    for (int i = 0; i < n; i++) {
        int aux;
        cin >> aux;
        anchurascarros.push_back(aux);
    }
    vector<int> anchurasCaminos;

    for (int i = 0; i < m; i++) {
        int aux;
        cin >> aux;
        anchurasCaminos.push_back(aux);
    }

    vector<vector<int>> calidades(n);
    vector <int> calidadMaxCarro(m, -1);
    for (int i = 0; i < n; i++) {
        for (int h = 0; h < m; h++) {
            int aux;
            cin >> aux;
            calidades[i].push_back(aux);

            calidadMaxCarro[h] = max(calidadMaxCarro[h], aux);
        }
    }

    int sol = resolver(calidades, anchurasCaminos, anchurascarros, calidadMaxCarro);

    cout << sol << "\n";
    // escribir sol
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}