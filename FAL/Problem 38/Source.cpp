// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

/*
Coste   siendo n el número de elementos del vector

T(n) =		Co caso base
			T(n/2) + C1 caso recursivo

Desplegado

T(n) = T(n/2) + C1 = T(n/2^2) + C1 + C1 = T(n/2^3) + C1 + C1 + C1 = ... = T(n/2^k) + KC1 = ... = T(1) + log n + C1

O(log n)
*/

// funcion que resuelve el problema
int resolver(std::vector<bool> const& v, int ini, int fin) {
	if (ini >= fin) return ini; // vector vacio
	else if (ini + 1 == fin) return ini; // vector 1 elemento
	else { // Vector de dos o mas elementos
		int mitad = (ini + fin - 1) / 2;
		if (!v[mitad]) return resolver(v, mitad + 1, fin);
		else return resolver(v, ini, mitad + 1); // incluye la mitad
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracion, y escribiendo la respuesta

bool resuelveCaso() {
	// leer los datos de la entrada
	int elementos;
	bool caso = true;
	std::cin >> elementos;
	if (!std::cin)
		return false;
	std::vector<bool> v(elementos);
	for (int i = 0; i < v.size(); i++) {
		std::cin >> caso;
		v[i] = caso;
	}
	int sol = resolver(v, 0, (int)v.size() + 1);
	// escribir sol
	std::cout << v.size() - sol << '\n';
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