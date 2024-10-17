//Jorge Torres 
//A66

#ifndef LINKED_LIST_ED_PLUS
#define	LINKED_LIST_ED_PLUS

#include <iostream>
#include <string>
#include <stdexcept>

template <typename T>
class linked_list_ed_plus : public linked_list_ed <T > {
	using Nodo = typename linked_list_ed <T >::Nodo;
public:
	void print(std::ostream& salida) const {
		Nodo* aux = this -> prim;
		if (aux != nullptr) {
			salida << aux -> elem;
			aux = aux -> sig;
		}
		while (aux != nullptr) {
			salida << ' ' << aux -> elem;
			aux = aux -> sig;
		}
		salida << '\n';
	}
	void agruparIgualesA(T const& ch) {
		if (this -> prim == nullptr) return; // lista vacia
		// Busca la primera aparicion del elemento
		Nodo* pos = this->prim;
		while (pos != nullptr && pos -> elem != ch)
			pos = pos -> sig;
		if (pos != nullptr) { // encontro primer elemento
			// saltamos todos los elementos iguales para anadir los elementos
			// detras de la posicion de pos
			while (pos -> sig != nullptr && pos -> sig -> elem == ch)
				pos = pos -> sig;
			// Busca elementos posteriores para agruparlos
			Nodo* otro = pos; // pos situado al final del primero bloque de elementos
			while (otro -> sig != nullptr) {
				if (otro -> sig -> elem == ch) {
					moverNodo(pos, otro);
					pos = pos -> sig; // para que quede detras del ultimo elemento
				}
				else otro = otro -> sig;
			}
			if (this -> ult == pos) // se ha movido el ultimo elemento
				this -> ult = otro;
		}
	}
private:
	void moverNodo(Nodo* pos, Nodo* antMover) {
		Nodo* mover = antMover -> sig;
		antMover -> sig = mover -> sig;
		mover -> sig = pos -> sig;
		pos -> sig = mover;
	}
};

template <typename T>
inline std::ostream& operator << (std::ostream& salida, linked_list_ed_plus <T > const& l) {
	l.print(salida);
	return salida;
}

#endif LINKED_LIST_ED_PLUS