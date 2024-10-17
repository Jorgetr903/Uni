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

	void suma(linked_list_ed_plus<int> const& other) {
		Nodo* aux = this->prim;
		Nodo* otro = other.prim;
		if (aux != nullptr) {
			if (aux->sig != nullptr) {
				Nodo* pos = aux->sig;
				int valor = aux->elem + otro->elem;
				if (valor == 0) {
					while (valor == 0 && aux->sig != nullptr) {
						this->prim = aux->sig;
						aux = aux->sig;
						otro = otro->sig;
						valor = aux->elem + otro->elem;
					}
				}
				if (aux->sig != nullptr) {
					aux->elem = valor;
					otro = otro->sig;
					pos = aux->sig;
					while (pos != nullptr && pos->sig != nullptr) {
						valor = pos->elem + otro->elem;
						if (valor != 0) {
							pos->elem = valor;
							aux = pos;
							pos = pos->sig;
							otro = otro->sig;
						}
						else {
							pos = pos->sig;
							aux->sig = pos;
							otro = otro->sig;
						}
					}
					if (pos != nullptr) {
						valor = pos->elem + otro->elem;
						if (valor == 0) {
							aux->sig = nullptr;
						}
						else {
							pos->elem = valor;
						}
					}
				}
				else {
					int valor = aux->elem + otro->elem;
					if (valor == 0) {
						this->prim = nullptr;
					}
					else {
						aux->elem = valor;
					}
				}
			}
			else {
				int valor = aux->elem + otro->elem;
				if (valor == 0) {
					this->prim = nullptr;
				}
				else {
					aux->elem = valor;
				}
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
		Nodo* mover = antMover->sig;
		aux->sig = mover;
	}
};


#endif LINKED_LIST_ED_PLUS



