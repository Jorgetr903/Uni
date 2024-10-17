// Nombre del alumno: Jorge Torres
// Usuario del Juez:A66


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

struct sol {
	bool zurdo;
	int nodos;
};

template <class T>
sol zurdo(bintree<T> const& arbol) {
	if (arbol.empty()) {
		return { true, 0, };
	}
	else if (arbol.right().empty() && arbol.left().empty()) {
		return { true, 1 };
	}
	else {
		sol iz = zurdo(arbol.left());
		sol dr = zurdo(arbol.right());

		sol final {iz.nodos > dr.nodos && iz.zurdo && dr.zurdo, iz.nodos + dr.nodos + 1};

		return final;
	}
}

void resuelveCaso() {
	bintree <char> arbol = leerArbol('.');
	sol a = zurdo(arbol);
	if (a.zurdo) {
		std::cout << "SI";
	}
	else {
		std::cout << "NO";
	}
	std::cout << '\n';
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}