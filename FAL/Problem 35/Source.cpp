// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>


// función que resuelve el problema
int resolver1(int n, int digito) {
    if (n < 10 && n >= digito) {
        return n;
    }
    else if (n < 10 && n < digito) {
        return 0;
    }
    else if (n >= 10 && n % 10 >= digito) {
        return resolver1(n / 10, n % 10) * 10 + n % 10;
    }
    else if (n > 10 && n % 10 < digito) {
        return resolver1(n / 10, digito);
    }
}

int resolver2(int n, int digito, int pot, int sol) {
    if (n < 10 && n >= digito) {
        return n*pot + sol;
    }
    else if (n < 10 && n < digito) {
        return sol;
    }
    else if (n >= 10 && n % 10 >= digito) {
        return resolver2(n / 10, n % 10, 10*pot, (n%10)*pot + sol);
    }
    else if (n > 10 && n % 10 < digito) {
        return resolver2(n / 10, digito, pot, sol);
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int numero;
    std::cin >> numero;

    int sol1 = resolver1(numero, 0);
    int sol2 = resolver2(numero, 0, 1, 0);
    // escribir sol

    std::cout << sol1 << " " << sol2 << '\n';
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