// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

/*
ÁRBOL EXPLORACIÓN
Número de ramas = Número de colores
Cada nivel del árbol de exploración es una altura de la torre

El vector solución es:
Cada posición es una altura de la torre y la celda contiene el color de la pieza que se coloca en esa altura de la torre

El número del vector es la cantidad de fichas que hay que colocar en la torre, es decir, la altura de la torre que nos piden
*/

// funcion que resuelve el problema
bool verdesSeguidos(int k, std::vector<int>const & sol) {
	if (sol[k] == 2 && sol[k - 1] == 2) return true;
	return false;
}
void resolver(int m, int n, int k, std::vector<int>& sol) {

	for (int x = 0; x < m; x++) {
		sol[k] = x;
		if (!verdesSeguidos(k, sol)) {

			if (k == n - 1) {
				
				for (int i = 0; i < n; i++) {
					if (sol[i] == 0) {
						std::cout << "azul ";
					}
					else if (sol[i] == 1) {
						std::cout << "rojo ";
					}
					else {
						std::cout << "verde ";
					}
				}
					std::cout << '\n';
			}
			else resolver(m, n, k + 1, sol);
		}
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracion, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int m = 3, n;
	std::cin >> n;
	if (n == 0)
		return false;
	std::vector<int> v(n);
	v[0] = 1;
	if (n == 1) {
		std::cout << "rojo";
		std::cout << '\n';
	}
	else {
		resolver(m, n, 1, v);
	}
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