// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

// función que resuelve el problema
char resolver(std::vector<char> const& v, char ini, char fin, char primer) {
    if (ini == fin - 1) {
        if (v[ini - primer] == ini) return fin;
        else return ini;
    }
    else { 
        char mitad = (ini + fin) / 2;
        if (v[mitad - primer] > mitad) return resolver(v, ini, mitad, primer);
        else return resolver(v, mitad, fin, primer); // Incluye el elemento mitad
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    char preso1, preso2;
    std::cin >> preso1 >> preso2;
    int cantidad = preso2 - preso1;
    
    std::vector<char> v(cantidad);
    for (int i = 0; i < v.size(); i++) {
        std::cin >> v[i];
    }

    char sol = resolver(v, preso1, preso2, preso1);
    // escribir sol

    std::cout << sol << '\n';
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