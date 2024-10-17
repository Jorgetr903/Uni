// Problema interseccion de dos listas ordenadas

// IMPORTANTE

// Nombre y apellidos del alumno
// Usuario del juez de clase
// Usuario que has utilizado en esta prueba


#include <iostream>               
#include <fstream>               

#include "deque_eda.h"
using namespace std;
// Explicación del algoritmo empleado






class InterseccionListas : public deque<int> {
    using Nodo = deque<int>::Nodo;
public:
    void print(std::ostream& o = std::cout) const {
        // rellenar
        Nodo* l1 = this->fantasma->sig;
        if (l1 != this->fantasma) {
            cout << l1->elem;
            l1 = l1->sig;
        }
        while (l1 != this->fantasma) {
            cout << " " << l1->elem;
            l1 = l1->sig;
        }
        cout << '\n';
    }

    void interseccion(InterseccionListas const& other) {
        // rellenar
        Nodo* l1 = this->fantasma->sig;
        Nodo* l2 = other.fantasma->sig;
        Nodo* aux = nullptr;

        while (l1 != this->fantasma && l2 != other.fantasma) {
            if (l1->elem == l2->elem) {
                l1 = l1->sig;
                l2 = l2->sig;
            }
            else if (l1->elem > l2->elem) {
                l2 = l2->sig;
            }
            else { // l1->elem < l2->elem
                aux = l1;
                l1 = l1->sig;
                this->borra_elem(aux);
            }
        }
        while (l1 != this->fantasma) {
            aux = l1;
            l1 = l1->sig;
            this->borra_elem(aux);
        }
    }
};



/////////////////////////////////////////////////////////
// desde aquí NO se puede modificar nada

inline std::ostream& operator<<(std::ostream& o, InterseccionListas const& a) {
    a.print(o);
    return o;
}

InterseccionListas leerLista() {
    InterseccionListas lista;
    int n;
    std::cin >> n;
    while (n != 0) {
        lista.push_back(n);
        std::cin >> n;
    }
    return lista;
}

bool resuelveCaso() {
    InterseccionListas lista1 = leerLista();
    InterseccionListas lista2 = leerLista();
    lista1.interseccion(lista2);

    std::cout << lista1 << '\n';

    return true;
}


int main() {

#ifndef DOMJUDGE
    std::ifstream in("sample1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos; std::cin >> numCasos; std::cin.ignore();
    for (int i = 0; i < numCasos; ++i) { resuelveCaso(); }

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
