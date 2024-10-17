// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>


// función que resuelve el problema
std::pair<bool, int> resolver1(int n, int suma) {
    int digito = n % 10;
    int sumIz = 0;
    if (n < 10 && suma % n == 0) {
        sumIz = digito;
        return { true, sumIz };
    }
    else if (n < 10 && suma % n == 1) {
        return { false, 0 };
    }
    else if (n >= 10 && suma % digito == 0) {
        std::pair<bool, int> sol = resolver1(n / 10, suma + digito);
        if (sol.first && sol.second % digito == 0) {
            sumIz = sol.second + digito;
            return { true, sumIz };
        }
        else {
            return { false, 0 };
        }
    }
    else if (n >= 10 && suma % digito == 1) {
        return { false, 0 };
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int numero;
    std::cin >> numero;

    std::pair<bool, int> sol = resolver1(numero, 0);
    // escribir sol
    if (sol.first) {
        std::cout << "SI" << '\n';
    }
    else {
        std::cout << "NO" << '\n';
    }
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