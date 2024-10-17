// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// funcion que resuelve el problema

void resolver(int m, int n, int k, std::vector<int>& sol) {
	for (int i = 0; i < m; i++) {
		sol[k] = 
	}
	
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracion, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int juguetes, ninos;
	std::cin >> juguetes >> ninos;
	if (!std::cin)
		return false;
	std::vector<int> sol(2 * ninos);
	resolver(juguetes, ninos, 0, sol);
	std::cout << '\n';
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