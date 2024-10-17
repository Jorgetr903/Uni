// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
using namespace std;


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int numeros, preguntas, num, pos;
    cin >> numeros >> preguntas;
    if (!std::cin)
        return false;
    map<int, vector<int>> ocurrencias;

    for (int i = 1; i <= numeros; i++) {
        cin >> num;
        vector<int>& apariciones = ocurrencias[num];
        apariciones.push_back(i);
    }
    // escribir sol
    for (int i = 0; i < preguntas; i++) {
        cin >> pos >> num;
        vector<int>& apariciones = ocurrencias[num];
        if (apariciones.size() >= pos) cout << apariciones[pos - 1] << '\n';
        else cout << "NO HAY \n";
    }
    cout << "--- \n";

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