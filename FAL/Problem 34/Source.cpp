// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>



// función que resuelve el problema
long long int recurNoFinal(long long int n) {
    if (n < 10 && n % 2 == 1) {
        return n;
    }
    else if (n < 10 && n % 2 == 0) {
        return 0;
    }
    else if (n >= 10 && n % 2 == 1) {
        return recurNoFinal(n / 10) * 10 + n%10;
    }
    else if (n >= 10 && n % 2 == 0) {
        return recurNoFinal(n / 10);
    }
}

long long int recurFinal(long long int n, long long int pot, long long int sol) {
    long long int digito = n % 10;
    if (n < 10 && n % 2 == 1) {
        return digito*pot + sol;
    }
    else if (n < 10 && n % 2 == 0) {
        return sol;
    }
    else if (n >= 10 && n % 2 == 1) {
        return recurFinal(n / 10, 10*pot, digito*pot + sol);
    }
    else if (n >= 10 && n % 2 == 0) {
        return recurFinal(n / 10, pot, sol);
    }
}

std::pair<long long int, long long int> resolver(long long int numero)
{
    long long int a = recurNoFinal(numero);
    long long int b = recurFinal(numero, 1, 0);
    return{ a, b };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    long long int numero;
    std::cin >> numero;
    if (!std::cin)
        return false;

    std::pair<long long int, long long int> sol = resolver(numero);

    // escribir sol
    std::cout << sol.first << " " << sol.second << '\n';

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