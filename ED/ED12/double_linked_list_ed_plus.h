//Jorge Torres
//A66

#ifndef double_linked_list_ed_plus_h
#define double_linked_list_ed_plus_h

#include <iostream>
#include <string>
#include <stdexcept>
#include "double_linked_list_ed.h"

template <typename T >
class double_linked_list_ed_plus : public double_linked_list_ed <T > {
    using Nodo = typename double_linked_list_ed <T >::Nodo;

public:

    void intercambiar() {
        Nodo* aux = this->fantasma->sig;
        if (aux != nullptr) {
            while (aux != this->fantasma && aux -> sig != this->fantasma) {
                aux -> sig -> ant = aux -> ant;
                aux -> ant -> sig = aux -> sig;
                aux -> sig = aux->sig -> sig;
                aux -> ant = aux->ant->sig;
                aux->ant->sig = aux;
                aux->sig->ant = aux;
                aux = aux->sig;
            }
        }
    }

    void mostrar() const {
        Nodo* aux = this->fantasma->sig;
        if (aux != this->fantasma) {
            std::cout << aux->elem;
            aux = aux->sig;
        }
        while (aux != this->fantasma) {
            std::cout << ' ' << aux->elem;
            aux = aux->sig;
        }
        std::cout << '\n';
    }
};
#endif
