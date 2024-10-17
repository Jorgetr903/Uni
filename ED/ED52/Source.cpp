// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int capitulos, num;
    cin >> capitulos;

    unordered_map<int, int> emision; //ultima vez que se ha emitido, si se ha emitido

    int maximo = 0, pos = 1;
    for (int i = 1; i <= capitulos; i++) {
        cin >> num;
        int& donde = emision[num];
        if (donde >= pos) {
            pos = donde + 1;
        }
        maximo = max(maximo, i - pos + 1);
        donde = i;
    }
    cout << maximo << '\n';
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