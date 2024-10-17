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
    int ejercicios;
    cin >> ejercicios;
    if (ejercicios == 0)
        return false;
    cin.ignore();       //para quitar el salto de línea detrás de casos

    map<string, int> alumnos;

    std::string nombre, calificaion;
    for (int i = 0; i < ejercicios; i++) { // i es el número de línea por la que vamos
        getline(cin, nombre);
        int &nota = alumnos[nombre];
        getline(cin, calificaion);
        if (calificaion == "CORRECTO") {
            nota++;
        }
        else nota--;
    }

    // escribir sol
    for (auto cv : alumnos) {
        if (cv.second != 0) {
            cout << cv.first << ", " << cv.second << '\n';
        }
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
