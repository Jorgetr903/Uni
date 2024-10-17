// Nombre del alumno: Jorge Torres

#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"
using namespace std;

struct registro {
    int momento, id, periodo;
};

bool operator<(registro const& a, registro const& b) {
    return a.momento < b.momento || (a.momento == b.momento && a.id < b.id);
}

bool resuelveCaso() {
    int usuarios;
    cin >> usuarios;

    if (usuarios == 0)
        return false;

    PriorityQueue<registro> cola;
    
    for (int i = 0; i < usuarios; ++i) {
        int id_usu, periodo;
        cin >> id_usu >> periodo;
        cola.push({ periodo, id_usu, periodo });
    }

    int envios;
    cin >> envios;

    while (envios--) {
        registro usuario = cola.top(); cola.pop();
        cout << usuario.id << '\n';
        usuario.momento += usuario.periodo;
        cola.push(usuario);
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
