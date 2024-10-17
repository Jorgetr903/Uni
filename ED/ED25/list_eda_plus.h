//Jorge Torres
//A66

#ifndef LIST_EDA_PLUS
#define LIST_EDA_PLUS

#include <iostream>
#include <string>
#include <stdexcept>
#include "list_eda.h"

template <typename T>
class list_eda_plus : public list <T > {
	using Nodo = typename list <T >::Nodo;
public:

	void qitarPosPar() {
		auto it = this->begin();
		it++;
		while (it != this->end()) {
			it = this->erase(it);
			if (it != this->end())
			it++;
		}
	}

	void mostrar() { // O(N)
		for (auto it = this->cbegin(); it != this->cend(); ++it)
			std::cout << *it;
		std::cout << '\n';
	}


private:

	void moverNodo(Nodo* aux, Nodo* antMover) {
		Nodo* mover = antMover->sig;
		aux->sig = mover;
	}
};


#endif LIST_EDA_PLUS