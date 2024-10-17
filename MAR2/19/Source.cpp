// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
#include <vector>
#include <queue>
using namespace std;

struct nodo {
    vector<int> sol;
    int nivel, limpiadas, recogido, recogido_opt;
    vector<int> basuraPlaya;

    bool operator<(nodo const& otro) const {
        return otro.recogido_opt <= recogido_opt;
    }
};

// función que resuelve el problema
pair<int, int> resolver(Matriz<int> recogePersPlaya, vector<int> basuraPlaya, vector<int> maxRecogerPers, int minLimpias) {
    int numPers = recogePersPlaya.numfils();
    int numPLayas = recogePersPlaya.numcols();
    nodo _y;
    _y.sol = vector<int>(numPers, -1);
    _y.nivel = -1;
    _y.recogido = 0;
    _y.limpiadas = 0;
    _y.recogido_opt = maxRecogerPers[0];
    _y.basuraPlaya = basuraPlaya;

    priority_queue<nodo> cola;

    cola.push(_y);
    int recogidoMejor = 0;
    pair<int, int> solMejor;

    while (!cola.empty() && cola.top().recogido_opt > recogidoMejor) {
        _y = cola.top();
        cola.pop();

        nodo _x = (_y);
        _x.nivel++;

        for (int i = 0; i < numPLayas; i++) {

            if (_x.basuraPlaya[i] > 0) {
                _x.sol[_x.nivel] = i; //se le asigna a pa persona _x.nivel la playa i

                int recogeEnPlaya = recogePersPlaya[_x.nivel][i]; // lo que peude recoger en la playa

                if (recogeEnPlaya <= _x.basuraPlaya[i]) {  //él solo no la acaba de limpiar
                    _x.basuraPlaya[i] -= recogeEnPlaya;
                    _x.recogido += recogeEnPlaya;
                }
                else {
                    _x.recogido += _x.basuraPlaya[i]; //recogemos lo que queda hasta vaciarla
                    _x.basuraPlaya[i] = 0; // queda limpia 
                    _x.limpiadas++;
                }
                //el oprimista es lo ya recogido mas todas las personas que quedan si recogen su maximo independientemente de la playa
                if (_x.nivel + 1 >= numPers) {
                    _x.recogido_opt = _x.recogido;
                }
                else {
                    _x.recogido_opt = _x.recogido + maxRecogerPers[_x.nivel + 1];
                }


                if (_x.recogido_opt >= recogidoMejor) {
                    if (_x.nivel == numPers - 1) {
                        if (_x.limpiadas >= minLimpias && _x.recogido > recogidoMejor) {
                            solMejor = { _x.recogido, _x.limpiadas };
                            recogidoMejor = _x.recogido;
                        }
                    }
                    else {
                        cola.push(_x);
                    }
                }
            }
        }
    }

    return solMejor;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int numPers, numPlayas, minLimpias;
    cin >> numPers >> numPlayas >> minLimpias;

    vector<int> basuraPlayas;

    for (int i = 0; i < numPlayas; i++) {
        int basura;
        cin >> basura;
        basuraPlayas.push_back(basura);
    }

    Matriz<int> personaPlaya(numPers, numPlayas);
    vector<int>maxRecogerPers(numPers, -1);
    for (int i = 0; i < numPers; i++) {
        for (int h = 0; h < numPlayas; h++) {
            int n;
            cin >> n;
            if (n > maxRecogerPers[i]) {
                maxRecogerPers[i] = n;
            }
            personaPlaya[i][h] = n;
        }
    }

    for (int i = maxRecogerPers.size() - 2; i >= 0; i--) {
        maxRecogerPers[i] += maxRecogerPers[i + 1];
    }


    pair<int, int> sol = resolver(personaPlaya, basuraPlayas, maxRecogerPers, minLimpias);
    // escribir sol

    if (sol.second < minLimpias) {
        cout << "IMPOSIBLE\n";
    }
    else {
        cout << sol.first << " " << sol.second << "\n";
    }

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