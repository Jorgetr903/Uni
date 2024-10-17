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

	void quitarRepetidos() {
		Nodo* aux = this->prim;
		if (aux != nullptr) { 
			Nodo* otro = aux;
			while (aux != nullptr) {
				while (otro->sig != nullptr && otro->sig->elem == aux->elem)
					otro = otro->sig;

				if (otro != aux)
					moverNodo(aux, otro);

				aux = aux->sig;
				otro = aux;
			}
		}
	}

	void mostrar() {
		Nodo* aux = this->prim;
		while (aux != nullptr) {
			std::cout << aux->elem << " ";
			aux = aux->sig;
		}
		std::cout << '\n';
	}

private:
	
	void moverNodo(Nodo* aux, Nodo* antMover) {
		Nodo* mover = antMover -> sig;
		aux->sig = mover;
	}	
};


#endif LINKED_LIST_ED_PLUS



