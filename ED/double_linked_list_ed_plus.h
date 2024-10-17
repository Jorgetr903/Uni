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

    void interseccion(double_linked_list_ed_plus<int> const& other) {
        Nodo* aux = this->fantasma->sig;
        Nodo* otro = other.fantasma->sig;
        Nodo* n = nullptr;
        while (aux != this->fantasma && otro != other.fantasma) {
            if (aux->elem < otro->elem) {
                n = aux;
                aux = aux->sig;
                this->borra_elem(n);
            }
            else if (aux->elem == otro->elem) {
                otro = otro->sig;
                aux = aux->sig;
            }
            else {
                otro = otro->sig;
            }
        }
        while (aux != this->fantasma) {
            n = aux;
            aux = aux->sig;
            this->borra_elem(n);
        }
    }

    void intercambiar() {
        Nodo* aux = this->fantasma->sig;
        if (aux != nullptr) {
            while (aux != this->fantasma && aux->sig != this->fantasma) {
                aux->sig->ant = aux->ant;
                aux->ant->sig = aux->sig;
                aux->sig = aux->sig->sig;
                aux->ant = aux->ant->sig;
                aux->ant->sig = aux;
                aux->sig->ant = aux;
                aux = aux->sig;
            }
        }
    }

    void duplicar() {
        Nodo* aux = this->fantasma->sig;
        if (aux != nullptr) {
            Nodo* otro = aux;
            while (aux != this->fantasma) {
                otro = new Nodo(aux->elem, aux->ant, aux->sig);
                aux->sig = otro;
                aux = otro->sig;
            }
            aux = this->fantasma->ant;
            while (aux != this->fantasma) {
                otro = new Nodo(aux->elem, aux->ant, aux->sig);
                aux->ant = otro;
                aux = otro->ant;
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

