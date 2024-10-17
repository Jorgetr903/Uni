//Jorge Torres
//A66

#ifndef LINKED_LIST_ED_PLUS
#define LINKED_LIST_ED_PLUS

#include <iostream>
#include <string>
#include <stdexcept>
#include "linked_list_ed.h"

template <typename T>
class linked_list_ed_plus : public linked_list_ed <T > {
	using Nodo = typename linked_list_ed <T >::Nodo;
public:

	void invertir() {
		Nodo* aux = this->prim;
		if (aux == nullptr || aux->sig == nullptr) { //vacío o de un elemento

		}
		else {
			Nodo* prim = aux;
			while (aux->sig != nullptr) {
				Nodo* pos = aux->sig;
				aux->sig = pos->sig;
				pos->sig = prim;
				prim = pos;
			}
			this->prim = prim;
		}
	}

	void moverNodo(Nodo* pos, Nodo* antMover) {
		Nodo* mover = antMover -> sig;
		antMover -> sig = mover -> sig;
		mover -> sig = pos -> sig;
		pos -> sig = mover;
	}

	void mostrar() {
		Nodo* aux = this->prim;
		while (aux != nullptr) {
			std::cout << aux->elem << " ";
			aux = aux->sig;
		}
		std::cout << '\n';
	}
};


#endif LINKED_LIST_ED_PLUS