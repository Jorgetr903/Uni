// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <set>
#include <vector>
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int jugadores, numero;
    string nombre;
    cin >> jugadores;
    if (jugadores == 0)
        return false;

    unordered_map<int, set<string>> bingo; //clave numero y valor los jugadores
    unordered_map<string, int> cartonJugador; //calve jugador y valor la cantidad de numeros
    for (int i = 0; i < jugadores; i++) {
        cin >> nombre >> numero;
        while (numero != 0) {
            bingo[numero].insert(nombre);
            ++cartonJugador[nombre];
            cin >> numero;
        }
    }

    bool terminado = false;
    vector<string> ganadores;
    while (!terminado) {
        cin >> numero;
        auto a = bingo[numero];
        for (auto b : a) {
            cartonJugador[b]--;
            if (cartonJugador[b] == 0) {
                terminado = true;
                ganadores.push_back(b);
            }
        }
        a.clear();
    }

    // escribir sol
    for (auto a : ganadores) {
        cout << a << " ";
    }
    cout << '\n';

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
