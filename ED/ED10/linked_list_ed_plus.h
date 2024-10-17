//Jorge Torres
//A66

#ifndef LINKED_LIST_ED_PLUS
#define LINKED_LIST_ED_PLUS

#include <iostream>
#include <string>
#include <stdexcept>
#include "linked_list_ed.h"

template <typename T>
class linked_list_ed_plus : public linked_list_ed <T> {
	using Nodo = typename linked_list_ed <T>::Nodo;
public:

	void mezclar(linked_list_ed_plus<int>& other) {
		Nodo* aux = this->prim;
		
		if (aux != nullptr) {
			while (aux->sig != nullptr && other.prim != nullptr) {
				if (aux->sig->elem <= other.prim->elem) {
					aux = aux->sig;
				}
				else {
					Nodo* otro = other.prim->sig;
					moverNodo(aux, other.prim);
					aux = aux->sig;
					other.prim = otro;
				}
			}
		}	
		while (other.prim != nullptr) {
			Nodo* otro = other.prim;
			other.prim = other.prim->sig;
			if (aux == nullptr) {
				aux = otro;
				other.prim = nullptr;
				this->prim = aux;
			}
			else {
				aux->sig = otro;
				otro->sig = nullptr;
				aux = aux->sig;
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
		Nodo* siguiente = aux->sig;
		Nodo* otrosig = antMover->sig;
		aux->sig = antMover;
		aux = aux->sig;
		aux->sig = siguiente;
		antMover = otrosig;
	}
};
#endif




