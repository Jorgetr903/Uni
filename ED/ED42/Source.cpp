// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

template <class T>
class bintree_eda_plus : public bintree <T> {

    using Link = typename bintree<T>::Link;
public:
    bintree_eda_plus() : bintree<T>() {}
    bintree_eda_plus(bintree_eda_plus<T> const& l, T const& e, bintree_eda_plus<T> const& r) : bintree<T>(l, e, r) {}


    void perfildr(vector<int>& sol) {
        int nivel = 0;
        if (!this->empty()) {
            queue<pair<Link, int>> pendientes;
            pendientes.push({ this->raiz, 0 });
            while (!pendientes.empty()) {
                Link sig = pendientes.front().first;
                int nivelSig = pendientes.front().second;
                pendientes.pop();
                if (nivelSig == nivel) {
                    sol.push_back(sig->elem);
                    nivel++;
                }
                if (sig->right != nullptr)
                    pendientes.push({ sig->right, nivelSig + 1 });
                if (sig->left != nullptr)
                    pendientes.push({ sig->left, nivelSig + 1 });
            }
        }
    }
};


template <typename T>
inline bintree_eda_plus<T> leerArbol_plus(T vacio) {
    T raiz;
    std::cin >> raiz;
    if (raiz == vacio) { // es un árbol vacío
        return {};
    }
    else { // leer recursivamente los hijos
        auto iz = leerArbol_plus(vacio);
        auto dr = leerArbol_plus(vacio);
        return { iz, raiz, dr };
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada

    auto arbol = leerArbol_plus(-1);
    vector <int> sol;
    arbol.perfildr(sol);
    cout << sol[0];
    for (int i = 1; i < sol.size(); i++) {
        cout << " " << sol[i];
    }
    cout << '\n';
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