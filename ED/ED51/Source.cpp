// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <sstream>
#include <set>
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    string linea;
    map<string, int> diccionario;
    pair<string, int> dato;

    // guardo los datos en los dos diccionarios
    getline(cin, linea);
    std::stringstream frase(linea);
    while (frase >> dato.first >> dato.second) {
        diccionario.insert(dato);
    }

    getline(cin, linea);
    map<string, int> diccionario2;
    std::stringstream frase2(linea);
    while (frase2 >> dato.first >> dato.second) {
        diccionario2.insert(dato);        
    }

    //compruebo los datos
    set<string> modificados;
    set<string> nuevos;
    set<string> eliminados;

    auto it1 = diccionario.begin();
    auto it2 = diccionario2.begin();

    while (it1 != diccionario.end() && it2 != diccionario2.end()) {
        if ((*it1).first == (*it2).first) {
            if ((*it1).second != (*it2).second) modificados.insert((*it1).first);
            it1++;
            it2++;
        }
        else if ((*it1).first < (*it2).first) {
            eliminados.insert((*it1).first);
            it1++;
        }
        else if ((*it1).first > (*it2).first) {
            nuevos.insert((*it2).first);
            it2++;
        }
    }

    while (it1 != diccionario.end()) {
        eliminados.insert((*it1).first);
        it1++;
    }

    while (it2 != diccionario2.end()) {
        nuevos.insert((*it2).first);
        it2++;
    }

    //escribir salida
    if (modificados.empty() && nuevos.empty() && eliminados.empty()) cout << "Sin cambios \n";
    else {
        if (!nuevos.empty()) {
            cout << "+ ";
            for (string n : nuevos) cout << n << " ";
            cout << '\n';
        }
        if (!eliminados.empty()) {
            cout << "- ";
            for (string e : eliminados) cout << e << " ";
            cout << '\n';
        }
        if (!modificados.empty()) {
            cout << "* ";
            for (string m : modificados) cout << m << " ";
            cout << '\n';
        }
    }
    cout << "--- \n";
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
    cin.ignore();
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}