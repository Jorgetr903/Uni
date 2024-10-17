// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include "set_eda.h"
using namespace std;

pair<int, int> altura(int &jefes, int &precarios) {
    int numhijos, hijos = 0;
    pair<int, int> alt = {0, 0};
    
    cin >> numhijos;
    if (numhijos == 0) return { 1, 1 };
    else {
        for (int i = 0; i < numhijos; i++) {
            alt = altura(jefes, precarios);
            hijos += alt.second;
        }
    }
    if (alt.first >= jefes) {
        precarios += hijos;
        return { 0, 0 };
    }
    else return { alt.first + 1, hijos };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int jefes, precarios = 0;
    cin >> jefes;
    if (!std::cin)
        return false;
    
    altura(jefes, precarios);
    cout << precarios << '\n';
    // escribir sol


    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
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