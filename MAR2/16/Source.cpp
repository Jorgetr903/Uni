// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <limits>
using namespace std;

/*
Cota pesimista: que cada producto se compre en su tienda más cara
Cota optimista: que cada producto se compre en su tienda más barata
La cota pesimista y optimista se calcula al principio para que luego llamarlo sea en tiempo constante

En cada tienda solo se pueden comprar 3 productos como máximo
La solución es la suma de los costes 

*/

struct Nodo {
    vector<int> sol;
    int nivel = 0;
    int precio = 0;
    int precio_opt = 0;
    vector<int> marcas_tiendas;    
    bool operator<(Nodo const& otro) const {
        return precio_opt > otro.precio_opt;
    }
    /*
    bool operator<(nodo const& otro) const {
        return calidadOpt > otro.calidadOpt;
    }
    */
};


// función que resuelve el problema
int resolver(vector<vector<int>> const& info, vector<int> const& maxt, vector<int> const& mint) {
    int optimista;
    int pesimista;

    int precio_mejor = 0;
    int sol_mejor = 0;
    optimista = mint[0];
    pesimista = maxt[0];

    int N = info.size();

    Nodo _y; // NODO RAIZ

    _y.sol = vector<int>(N, -1);
    _y.nivel = -1;
    _y.precio = 0;
    _y.precio_opt = optimista;
    _y.marcas_tiendas = vector<int>(N, 0);

    priority_queue<Nodo> cola;
    cola.push(_y);

    precio_mejor = pesimista;

    while (!cola.empty() && cola.top().precio_opt <= precio_mejor) {
        _y = cola.top();
        cola.pop();

        Nodo _x(_y); // CREAMOS UN HIJO

        _x.nivel++;

        // RECORRER LAS POSIBLES RAMAS

        for (int i = 0; i < N; i++) {
            if (_x.marcas_tiendas[i] < 3) { // SI LA TAREA NO ESTÁ ASIGNADA SE ASIGNA
                _x.sol[_x.nivel] = i;
                _x.marcas_tiendas[i]++;
                _x.precio = _y.precio + info[i][_x.nivel]; // SUMAMOS TIEMPO ANTERIOR + TIEMPO MINISTRO EN HACER TAREA I
                _x.precio_opt = _y.precio + mint[_x.nivel];

                if (_x.precio_opt <= precio_mejor) {
                    if (_x.nivel == N - 1) {
                        sol_mejor = _x.precio;
                        precio_mejor = _x.precio;
                    }
                    else {
                        cola.push(_x);
                        precio_mejor = min(precio_mejor, _x.precio + maxt[_x.nivel]);
                    }
                }

                _x.marcas_tiendas[i]--;
            }
        }
    }
    return sol_mejor;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    int tiendas, productos;
    cin >> tiendas >> productos;

    vector<vector<int>> info(tiendas, vector<int>(productos));
    int min = numeric_limits<int>::min();
    int max = std::numeric_limits<int>::max();

    vector<int> MaxProductos(productos, 0);
    vector<int> MinProductos(productos, max);

    for (int i = 0; i < tiendas; i++) {
        for (int j = 0; j < productos; j++) {
            int precio;
            cin >> precio;
            if (precio > MaxProductos[j]) {
                MaxProductos[j] = precio;
            }
            if (precio < MinProductos[j]) {
                MinProductos[j] = precio;
            }
            info[i][j] = precio;
        }
    }
    int sol = resolver(info, MaxProductos, MinProductos);

    cout << sol << '\n';
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