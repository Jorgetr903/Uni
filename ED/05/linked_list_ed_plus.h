//Jorge Torres 
//A66

#ifndef LINKED_LIST_ED_PLUS
#define	LINKED_LIST_ED_PLUS

#include <iostream>
#include <string>
#include <stdexcept>
#include "linked_list_ed.h"

template <typename T>
class linked_list_ed_plus : public linked_list_ed <T > {
	using Nodo = typename linked_list_ed <T >::Nodo;
public:

	/*void print(std::ostream& salida) const {
		Nodo* aux = this->prim;
		if (aux != nullptr) {
			salida << aux->elem;
			aux = aux->sig;
		}
		while (aux != nullptr) {
			salida << ' ' << aux->elem;
			aux = aux->sig;
		}
		salida << '\n';
	}*/

	template <typename Predicate>
	void mostrarPropiedad(Predicate pred, std::ostream& o = std::cout) const {
		Nodo* aux = this -> prim;
		while (aux != nullptr && !pred(aux -> elem)) 
			aux = aux -> sig;
		if (aux != nullptr) {
			o << aux -> elem;
			aux = aux -> sig;
			while (aux != nullptr) {
				if (pred(aux -> elem))
					o << ' ' << aux -> elem;
				aux = aux -> sig;
			}
		}
		o << '\n';
	}
};

class empiezaPor {
public:
	empiezaPor(std::string ch) : c(ch) {}
	bool operator ()(std::string palabra) {
		if (palabra.substr(0, 1) == c) return true;
		else return false;
	}
private:
	std::string c;
};

template <typename T>
inline std::ostream& operator << (std::ostream& salida, linked_list_ed_plus <T > const& l) {
	return salida;
}

#endif LINKED_LIST_ED_PLUS
