// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>



// función que resuelve el problema
std::pair<int, int> resolver(std::vector<int> const& v, int& suma) {
    int sumaAct = 0; int inicio = 0; int final = 0; int posicion = 0;
    for (int i = 0; i < v.size(); i++) {
        if (sumaAct + v[i] > suma) {
            sumaAct += v[i];
            final++;
            suma = sumaAct;
            inicio = i - final + 1;
            posicion = final;
        }
        else if (sumaAct + v[i] > 0) {
            sumaAct += v[i];
            final++;
        }
        else {
            sumaAct = 0;
            final = 0;
        }
    }
    return { inicio, posicion };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int elementos;
    int suma = 0;
    std::cin >> elementos;
    if (!std::cin)
        return false;

    std::vector<int> v(elementos);
    for (int i = 0; i < v.size(); i++) {
        std::cin >> v[i];
    }

    std::pair<int, int> sol = resolver(v, suma);

    // escribir sol
    std::cout << suma << " " << sol.first << " " << sol.second << '\n';

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