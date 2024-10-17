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
    using Nodo = typename double_linked_list_ed <T >:: Nodo ;

public :

    void duplicar() {
        Nodo* aux = this -> fantasma -> sig;
        if (aux != nullptr) { 
			Nodo* otro = aux;
			while (aux != this -> fantasma) {
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
        Nodo* aux = this -> fantasma -> sig;
        if ( aux != this -> fantasma ) {
            std::cout << aux -> elem;
            aux = aux -> sig ;
        }
        while ( aux != this -> fantasma ) {
            std::cout << ' ' << aux -> elem;
            aux = aux -> sig;
        }
        std::cout << '\n';
    }

    void mostrar2() const {
        Nodo* aux = this -> fantasma -> ant;
        if ( aux != this -> fantasma ) {
            std::cout << aux -> elem;
            aux = aux -> ant ;
        }
        while ( aux != this -> fantasma ) {
            std::cout << ' ' << aux -> elem ;
            aux = aux -> ant ;
        }
        std::cout << '\n';
    }
};
#endif