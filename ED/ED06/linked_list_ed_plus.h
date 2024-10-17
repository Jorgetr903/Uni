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

	void duplicar() {
		Nodo* aux = this->prim;
		Nodo* aux2 = nullptr;
		while (aux != nullptr) {
			aux2 = new Nodo(aux->elem, aux->sig);
			aux->sig = aux2;
			aux = aux2->sig;
		}
		this->ult = aux2;
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

