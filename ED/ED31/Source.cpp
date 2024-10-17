// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66


#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include"bintree_eda.h"

template <class T >

std::vector<int> descripcion(bintree <T > const& arbol) { 

	if (arbol.empty()) {
		return { 0, 0, 0 };
	}
	else {
		std::vector<int> iz = descripcion(arbol.left());
		std::vector<int> dr = descripcion(arbol.right());

		int altura = std::max(iz[2], dr[2]) + 1;
		int hojas;
		if (arbol.left().empty() && arbol.right().empty()) {
			hojas = iz[1] + dr[1] + 1;
		}
		else {
			hojas = iz[1] + dr[1];
		}
		int nodos = iz[0] + dr[0] + 1;
		return { nodos, hojas, altura };
	}
}
void resuelveCaso() {
	char a = '.';
	bintree <char> arbol = leerArbol(a);
	std::vector<int> sol = descripcion(arbol);
	for (int i : sol)
	{
		std::cout << i << " ";
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