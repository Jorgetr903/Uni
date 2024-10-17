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

    void particion(int pivote) {
        Nodo* act = this->fantasma->sig;
        Nodo* j = this->fantasma->ant;
        while (act != j) {
            if (act->elem <= pivote) act = act->sig;
            else {
                //desengancho
                act->sig->ant = act->ant;
                act->ant->sig = act->sig;
                Nodo* a_mover = act;
                act = act->sig;
                //enganchar
                a_mover->sig = this->fantasma;
                a_mover->ant = this->fantasma->ant;
                this->fantasma->ant->sig = a_mover;
                this->fantasma->ant = a_mover;
            }
        }
        //mover el ultimo
        if (act->elem <= pivote) act = act->sig;
        else {
            //desengancho
            act->sig->ant = act->ant;
            act->ant->sig = act->sig;
            Nodo* a_mover = act;
            act = act->sig;
            //enganchar
            a_mover->sig = this->fantasma;
            a_mover->ant = this->fantasma->ant;
            this->fantasma->ant->sig = a_mover;
            this->fantasma->ant = a_mover;
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

