// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

struct tJugador {
    std::string nombre;
    int canicas;
};

// Sobrecarga operador >> para lectura de datos
std::istream& operator >> (std::istream& entrada, tJugador& j) {
    entrada >> j.nombre >> j.canicas;
    return entrada;
}

// función que resuelve el problema
tJugador resolver(std::vector<tJugador> const& v, int ini, int fin) {
    tJugador sol;
    if (ini + 2 == fin) {
        if (v[ini].canicas >= v[fin - 1].canicas) {
            sol.nombre = v[ini].nombre;
            sol.canicas = v[ini].canicas + v[fin - 1].canicas / 2;
        }
        else {
            sol.nombre = v[fin - 1].nombre;
            sol.canicas = v[fin - 1].canicas + v[ini].canicas / 2;
        }
    }
    else {
        int mitad = (ini + fin) / 2;
        tJugador solIz = resolver(v, ini, mitad);
        tJugador solDr = resolver(v, mitad, fin);
        if (solIz.canicas >= solDr.canicas) {
            sol.nombre = solIz.nombre;
            sol.canicas = solIz.canicas + solDr.canicas / 2;
        }
        else {
            sol.nombre = solDr.nombre;
            sol.canicas = solDr.canicas + solIz.canicas / 2;
        }
    }
    return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int jugadores;
    std::cin >> jugadores;
    if (!std::cin)
        return false;
    std::vector<tJugador> v(jugadores);
    for (int i = 0; i < jugadores; i++) {
        std::cin >> v[i];
    }

    tJugador sol = resolver(v, 0, v.size());

    // escribir sol
    std::cout << sol.nombre << " " << sol.canicas << '\n';

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