// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


int contarParadas(int peso, std::vector<int> const& v) {
    int cont = 1;
    int suma = 0;
    int i = 0;
    while (i < v.size()) {
        if (suma + v[i] <= peso) {
            suma += v[i];
        }
        else {
            cont++;
            suma = v[i];
        }
        i++;
    }
    return cont;
}
// función que resuelve el problema
int resolver(std::vector<int>const& v, int ini, int fin, int viajes) {
    if (ini == fin) {
        return ini;
    }
    else {
        int mitad = (ini + fin) / 2;
        int p = contarParadas(mitad, v);
        if (p <= viajes) // salen menos paradas de las que deberíamos o igual
        {
            return resolver(v, ini, mitad, viajes);
        }
        else {
            return resolver(v, mitad + 1, fin, viajes);
        }
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int cuadros, maxviajes, inter_min = -1, interMax = 0;

    std::cin >> cuadros >> maxviajes;
    if (cuadros == 0 && maxviajes == 0)
        return false;
    std::vector<int>v(cuadros);

    for (int i = 0; i < v.size(); i++) {
        std::cin >> v[i];
        if (v[i] > inter_min) {
            inter_min = v[i];
        }
        interMax += v[i];
    }

    int sol = resolver(v, inter_min, interMax, maxviajes);

    // escribir sol
    std::cout << sol << '\n';
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