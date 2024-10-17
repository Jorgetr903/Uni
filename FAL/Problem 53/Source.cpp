// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>



// función que resuelve el problema
long long int resolver(int valor, int& a, int& b) {
    if (valor == 0) return 0;
    else if (valor == 1) return 1;
    else if (valor == 2) {
        a = 1;
        b = 1;

        return a;
    }
    else {
        resolver(valor - 1, a, b);
        long long int aux = a;
        a = a + b;
        b = aux;
        return a;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int valor, valor2, valor3;
    std::cin >> valor;
    if (!std::cin)
        return false;

    long long int sol = resolver(valor, valor2, valor3);

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