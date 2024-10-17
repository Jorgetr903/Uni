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

    void eliminarMenor() {
        Nodo* aux = this->fantasma->sig;
        if (aux != nullptr) {
            while (aux->sig != this->fantasma) {
                if (aux->sig->elem < aux->elem) {
                    aux->sig = aux->sig->sig;
                    aux->sig->ant->ant = nullptr;
                    aux->sig->ant->sig = nullptr;
                    aux->sig->ant = aux;
                }
                else 
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

