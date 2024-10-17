// Nombre del alumno: Jorge Torres

#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

using namespace std;

long long int costeSumar(priority_queue<long long int, vector<long long int>, greater<long long int>> sumandos) {
    long long int costeTotal = 0;
    long long int num1, num2;
    while (sumandos.size() != 1) {
        num1 = sumandos.top();
        sumandos.pop();
        num2 = sumandos.top();
        sumandos.pop();
        costeTotal += (num1 + num2);
        sumandos.push(num1 + num2);
    }
    return costeTotal;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int cantidad, num;

    cin >> cantidad;

    if (cantidad == 0)
        return false;

    priority_queue<long long int, vector<long long int>, greater<long long int>> sumandos;

    for (int i = 0; i < cantidad; i++) {
        cin >> num;
        sumandos.push(num);
    }

    // escribir sol
    long long int sol = costeSumar(sumandos);
    cout << sol << '\n';

    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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
