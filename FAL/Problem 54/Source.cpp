// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using tMatriz = std::vector<std::vector<int>>;

// función que resuelve el problema
int resolver(int a, int b, tMatriz& matriz) {
    if (a == 0 || a == b) return matriz[a][b] = 1;
    else if (b == 1 || b == a - 1) return matriz[a][b] = a;
    else {
        if (matriz[a - 1][b] == -1) {
            matriz[a - 1][b] = resolver(a - 1, b, matriz);
        }
        if (matriz[a - 1][b - 1] == -1) {
            matriz[a - 1][b - 1] = resolver(a - 1, b - 1, matriz);
        }
    }
    matriz[a][b] = matriz[a - 1][b] + matriz[a - 1][b - 1];
    return matriz[a][b];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int a, b;
    std::cin >> a >> b;
    if (!std::cin)
        return false;

    tMatriz matriz(a + 1, std::vector<int>(b + 1, -1));
    int sol = resolver(a, b, matriz);

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