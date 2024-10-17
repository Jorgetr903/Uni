// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int alumnos, saltar;
    std::cin >> alumnos >> saltar;
    if (alumnos == 0 && saltar == 0)
        return false;

    std::queue<int> cola;
    for (int i = 1; i < alumnos + 1; i++) {
        cola.push(i);
    }
    int j = 1;
    while (cola.size() != 1) {

        int elegido = cola.front();
        cola.pop();
        if (j != saltar + 1) {
            cola.push(elegido);
        }
        else {
            j = 0;
        }
        j++;
    }
    int sol = cola.front();
    std::cout << cola.front() << '\n';
    // escribir sol

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
