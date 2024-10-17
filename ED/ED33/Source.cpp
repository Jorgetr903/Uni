// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include"bintree_eda.h"

template <class T>

T minimo(bintree <T> const& arbol) {
	T iz, dr, min = arbol.root();
	if (arbol.left().empty() && arbol.right().empty()) return min;
	else {
		if (!arbol.left().empty()) {
			iz = minimo(arbol.left());
		}
		else iz = min;

		if (!arbol.right().empty()) {
			dr = minimo(arbol.right());
		}
		else dr = min;

		if (min > iz || min > dr) {
			if (min > iz) min = iz;
			if (min > dr) min = dr;
		}
		return min;
	}
}

bool resuelveCaso() {
	char caso;
	std::cin >> caso;
	if (!std::cin)
		return false;

	if (caso == 'N') {
		int i = -1;
		bintree <int> arbol = leerArbol(i);
		std::cout << minimo(arbol) << '\n';
	}
	else {
		std::string a = "#";
		bintree <std::string> arbol = leerArbol(a);
		std::cout << minimo(arbol) << '\n';
	}

	return true;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	while (resuelveCaso())
		;


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}