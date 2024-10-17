// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta

bool cmp(const pair<string, int>& a, const pair<string, int>& b) {
    return (a.second > b.second) || (a.second == b.second && a.first < b.first);
}

bool resuelveCaso() {
    // leer los datos de la entrada
    string deporte, estudiante;
    cin >> deporte;
    if (!std::cin)
        return false;
    unordered_map<string, unordered_set<string>> deportes; //para cada deporte los alumnos que se han apuntado
    unordered_map<string, string> estudiantes; //para cada estudiante, el deporte al que se han apuntado

    deportes.insert(deporte, {});

    while (cin >> estudiante, estudiante != "_FIN_") {
        if (isupper(estudiante[0])) { //es un deporte
            deporte = estudiante;
            deportes.insert(deporte, {});
        }
        else { //es un estudiante
            auto it = estudiantes.insert({ estudiante, deporte });
            if (it.second) {
                deportes[deporte].insert(estudiante);
            }
            else {
                if (it.first->second != deporte) {
                    deportes[it.first->second].erase(estudiante);
                }
            }
        }
    }

    //ponemos los deportes en un vector para luego ordenarlos
    vector<pair<string, int>> lista;
    for (auto const& it : deportes) {
        lista.push_back({ it.first, it.second.size() });
    }

    //ordenamos
    sort(lista.begin(), lista.end(), cmp);

    // escribir sol
    for (auto& par : lista) {
        cout << par.first << " " << par.second << '\n';
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