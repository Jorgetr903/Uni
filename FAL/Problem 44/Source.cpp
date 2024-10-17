// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

struct tSol {
    bool cumple;
    int suma;
};

// función que resuelve el problema
tSol resolver(std::vector<int> const& v, int ini, int fin) {
    if (ini + 1 == fin) return {true, v[ini]};
    else {
        int mitad = (ini + fin) / 2;
        tSol Iz = resolver(v, ini, mitad );
        tSol Dr = resolver(v, mitad, fin);
        
        tSol solucion;

        solucion.suma = Iz.suma + Dr.suma;
        solucion.cumple = Iz.cumple && Dr.cumple && Iz.suma < Dr.suma;

        return solucion;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int filas, columnas, numero;
    bool degradado = true;
    std::cin >> filas >> columnas;
    if (!std::cin)
        return false;
    
    for (int i = 0; i < filas; i++) {
        std::vector<int> v(columnas);
        for (int j = 0; j < v.size(); j++) {
            std::cin >> v[j];
        }
        if (!resolver(v, 0, v.size()).cumple) {
            degradado = false;
            for (int h = i + 1; h < filas; h++) {
                for (int k = 0; k < columnas; k++) {
                    std::cin >> numero;
                }
            }
            i = filas;
        }
    }
    if (degradado) std::cout << "SI\n";
    else std::cout << "NO\n";

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