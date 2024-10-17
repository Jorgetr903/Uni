// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
using namespace std;


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int casos;
    cin >> casos;
    if (casos == 0)
        return false;
    cin.ignore();       //para quitar el salto de línea detrás de casos

    map<string, vector<int>> lugar;

    std::string linea, palabra;
    for (int i = 1; i <= casos; i++) { // i es el número de línea por la que vamos
        getline(cin, linea);
        std::stringstream frase(linea);
        while (frase >> palabra) { // recorre las palabras de la línea
            if (palabra.length() > 2) {
                // pasamos a minúscula
                for (char& c : palabra) c = tolower(c);
                std::vector<int>& apariciones = lugar[palabra];

                if (apariciones.empty() || apariciones.back() != i) {
                    apariciones.push_back(i);
                }
            }
        }
    }

    // escribir sol
    for (auto cv : lugar) {
        cout << cv.first;
        for (auto numlinea : cv.second) {
            cout << ' ' << numlinea;
        }
        cout << '\n';
    }
    cout << "---\n";

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
