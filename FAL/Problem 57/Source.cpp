// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// función que resuelve el problema
void resolver(int m, int n, int k, std::vector<char>& sol) {
    for (char c = 'a'; c < 'a' + m; c++) {
        sol[k] = c;
        if (k == n - 1) {
            for (int i = 0; i < n; i++) {
                std::cout << sol[i];
            }
            std::cout << '\n';
        }
        else resolver(m, n, k + 1, sol);
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int m, n;
    std::cin >> m >> n;
    if (!std::cin)
        return false;

    std::vector<char> v(n);

    resolver(m, n, 0, v);
    std::cout << '\n';
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