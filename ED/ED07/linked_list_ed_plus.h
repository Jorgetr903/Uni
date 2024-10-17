//Jorge Torres
//A66

#ifndef LINKED_LIST_ED_PLUS
#define LINKED_LIST_ED_PLUS

#include <iostream>
#include <string>
#include <stdexcept>
#include "linked_list_ed.h"
#include "Horas.h"

template <typename T>
class linked_list_ed_plus : public linked_list_ed <T > {
	using Nodo = typename linked_list_ed <T >::Nodo;
public:

	void quitarPares() {
		Nodo* aux = this->prim;
		while (aux != nullptr && aux != this->ult) {
			if (aux->sig != this->ult) {
				aux->sig = aux->sig->sig;
			}
			else {
				aux->sig = nullptr;
			}
			aux = aux->sig;
		}
		this->ult = aux;
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


