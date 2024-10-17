// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>


// función que resuelve el problema

int resolver(std::vector<int> const& v, int k) {
    int longMax = 0; int longAct = 0; int numPares = 0;

    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] % 2 == 0) {
            numPares++;
            longAct++;
        }
        else {
            numPares = 0;
            longAct++;
        }

        if (numPares > k) {
            longAct -= (longAct - numPares + 1);
            numPares--;
        }

        if (longAct > longMax) {
            longMax = longAct;
        }
    }
    return longMax;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int elemento, numero;
    std::cin >> elemento >> numero;
    std::vector<int> v(elemento);
    for (int i = 0; i < v.size(); i++) {
        std::cin >> v[i];
    }
    int sol1 = resolver(v, numero);
    // escribir sol

    std::cout << sol1 << '\n';
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
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