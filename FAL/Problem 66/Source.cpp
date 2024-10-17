// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using tmatriz = std::vector<std::vector<int>>;

/*
ÁRBOL EXPLORACIÓN
Número de ramas = Número de funcionarios
Cada nivel del árbol de exploración es un trabajo
Se hacen todas las combinaciones posibles de los funcionarios y se queda con la que tenga el menor tiempo

El vector solución es:
Cada posición es un trabajo y la celda contiene el funcionario

El número del vector es la cantidad de funcionarios
*/


// función que resuelve el problema
void resolver(int n, int k, std::vector<bool>& marcas, int& SatisActual, int& SatisMejor, std::vector<int>& sol, std::vector<int>& solMejor, std::vector<std::vector<int>> const& tiempos) {
    for (int i = 0; i < n; i++) {
        sol[i] = i;
        SatisActual += tiempos[k][i];
        if (!marcas[i]) { //funcionario no utilizado
            marcas[i] = true;
            if (k == n - 1) {
                if (SatisActual < SatisMejor) {
                    SatisMejor = SatisActual;
                    solMejor = sol;
                }
            }
            else resolver(n, k + 1, marcas, SatisActual, SatisMejor, sol, solMejor, tiempos);
            marcas[i] = false;
        }
        SatisActual -= tiempos[k][i];
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int funcionarios, SatisActual = 0, SatisMejor = 0;
    std::cin >> funcionarios;
    if (funcionarios == 0)
        return false;

    tmatriz tiempos(funcionarios, std::vector<int>(funcionarios));

    for (int i = 0; i < funcionarios; i++) {
        for (int j = 0; j < funcionarios; j++) {
            std::cin >> tiempos[i][j];
            if (i == j) {
                SatisMejor += tiempos[i][j];
            }
        }
    }

    std::vector<int> sol(funcionarios);
    std::vector<int> solMejor(funcionarios);
    std::vector<bool> marcas(funcionarios, false);
    resolver(funcionarios, 0, marcas, SatisActual, SatisMejor, sol, solMejor, tiempos);

    // escribir sol
    std::cout << SatisMejor << '\n';
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