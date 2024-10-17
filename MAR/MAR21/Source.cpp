#include <iostream>
#include <iomanip>
#include <fstream>
#include "Manchas.h"
using namespace std;

struct Solucion {
    int numManchas;
    int tamManchaGrande;
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int filas, columnas;
    char c;
    cin >> filas >> columnas;

    if (!std::cin)
        return false;

    Mapa mapa(filas);

    // leemos la imagen
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cin.get(c);
            if (c == '#') {
                mapa[i][j] = '#';
            }
        }
    }

    // la analizamos
    Manchas manchas(mapa);

    int nuevasManchas, i, j;
    cin >> nuevasManchas;
    for (int a = 0; a < nuevasManchas; a++) {
        cin >> i >> j;
        int sol = manchas.nuevasManchas(mapa, i, j);
        cout << sol << " ";
    }
    cout << '\n';

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