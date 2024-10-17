//Jorge Torres

#include <iostream>
#include <iomanip>
#include <fstream>

#include <queue>
using namespace std;

bool operator<(pair<int, string> const& a, pair<int, string> const& b) {
    return a.first < b.first || (a.first == b.first);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int eventos, gravedad;
    char caso;
    string nombre;

    cin >> eventos;
    if (eventos == 0)
        return false;

    //priority_queue<pair<int, string>, vector<pair<int, string>>, less<pair<int, string>>> enfermos;
    priority_queue<pair<int, string>> enfermos;

    for (int i = 0; i < eventos; i++) {
        cin >> caso;
        if (caso == 'I') {
            cin >> nombre >> gravedad;
            enfermos.push({ gravedad, nombre });
        }
        else { // caso == 'A'
            cout << enfermos.top().second << '\n';
            enfermos.pop();
        }
    }

    cout << "---\n";

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
