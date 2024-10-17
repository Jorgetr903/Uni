#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct nodo {
    vector<int> sol;
    vector<bool> marcas;
    int nivel, libreA, libreB, puntuacion, puntuacionOpt;
    bool operator<(nodo const& otro) const
    {
        return otro.puntuacionOpt < puntuacionOpt;
    }
};

//Consideramos que todas las canciones que quedan por decidir si se ponen o no, se ponen. Sumamos toda su puntuaicon
int estimacion(vector<pair<int, int>> const& infoCanciones, int i) {
    int acc = 0;
    for (int h = i; h < infoCanciones.size(); h++) {
        acc += infoCanciones[h].second;
    }
    return acc;
}

// función que resuelve el problema
int resolver(vector<pair<int, int>> const& infoCanciones, int const& tamCaras) {

    //Los niveles del árbol son canciones y las ramas: ponerla en la cara A, en la B o no ponerla
    int numCanciones = infoCanciones.size();

    nodo _y;
    _y.libreA = tamCaras;
    _y.libreB = tamCaras;
    _y.marcas = vector<bool>(numCanciones, false);
    _y.nivel = -1;
    _y.puntuacion = 0;
    _y.puntuacionOpt = 0;
    _y.sol = vector<int>(numCanciones); //0 no la pones, 1 la pones can cara 1, 2 la pones en cara 2

    priority_queue<nodo> cola;

    cola.push(_y);

    int mejorPuntuacion = -1;

    while (!cola.empty() && cola.top().puntuacionOpt > mejorPuntuacion) {
        _y = cola.top();
        cola.pop();
        nodo _x(_y);

        _x.nivel++;

        if (_x.libreA > infoCanciones[_x.nivel].first) {  //cabe en la a
            _x.sol[_x.nivel] = 1;
            _x.libreA = _y.libreA - infoCanciones[_x.nivel].first;
            _x.puntuacion = _y.puntuacion + infoCanciones[_x.nivel].second;
            _x.puntuacionOpt = _x.puntuacion + estimacion(infoCanciones, _x.nivel + 1);

            if (_x.nivel == numCanciones - 1) {
                if (_x.puntuacion > mejorPuntuacion) {
                    mejorPuntuacion = _x.puntuacion;
                }
            }
            else if (_x.puntuacionOpt >= mejorPuntuacion) {
                cola.push(_x);
            }
        }

        if (_x.libreB > infoCanciones[_x.nivel].first) {  //cabe en la b
            _x.sol[_x.nivel] = 2;
            _x.libreB = _y.libreB - infoCanciones[_x.nivel].first;
            _x.puntuacion = _y.puntuacion + infoCanciones[_x.nivel].second;
            _x.puntuacionOpt = _x.puntuacion + estimacion(infoCanciones, _x.nivel + 1);

            if (_x.nivel == numCanciones - 1) {
                if (_x.puntuacion > mejorPuntuacion) {
                    mejorPuntuacion = _x.puntuacion;
                }
            }
            else if (_x.puntuacionOpt >= mejorPuntuacion) {
                cola.push(_x);
            }
        }

        //No la ponemos en ninguna cara
        _x.sol[_x.nivel] = 0;
        _x.puntuacion = _y.puntuacion;
        _x.puntuacionOpt = _x.puntuacion + estimacion(infoCanciones, _x.nivel + 1);

        if (_x.nivel == numCanciones - 1) {
            if (_x.puntuacion > mejorPuntuacion) {
                mejorPuntuacion = _x.puntuacion;
            }
        }
        else if (_x.puntuacionOpt >= mejorPuntuacion) {
            cola.push(_x);
        }
    }
    return mejorPuntuacion;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n == 0)
        return false;

    int tamCara;
    cin >> tamCara;

    vector<pair<int, int>> infoCanciones;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        infoCanciones.push_back({ a, b }); //duracion y puntuación 
    }

    int sol = resolver(infoCanciones, tamCara);
    cout << sol << "\n";
    // escribir sol

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