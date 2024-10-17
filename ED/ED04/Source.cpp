// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Polinomio.h"

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio?n, y escribiendo la respuesta

int resolver(Polinomio const p, float valor) {
    int resultado = 0;
    for (int i = 0; i < p.size(); i++) {
        resultado += p[i].first * (valor) ^ p[i].second;
    }
    return resultado;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int dato1, dato2, i = 0;
    int valores;
    float valor;
    if (!std::cin)
        return false;

    std::cin >> dato1 >> dato2;
    Polinomio p;

    while (dato1 != 0 && dato2 != 0) {
        p.Monomio(dato1, dato2);
        std::cin >> dato1 >> dato2;
    }

    std::cin >> valores;
    for (int j = 0; j < valores; j++) {
        std::cin >> valor;
        int resolver(p, valor);
    }

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