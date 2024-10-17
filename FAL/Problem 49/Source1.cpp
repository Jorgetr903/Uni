// Jorge Torres
// A83
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
//*******************************
// Explicacion del algoritmo utilizado
// Voy dividiendo por la mitad hasta llegar a solo un elemento y devuelvo si es par o impar
// Luego comparo la cantidad de pares de las mitades y si son caucásicas
// Devuelvo la suma de los pares y que es caucásica si se cumple la condición o que no es caucásica si no se cumple
//
// Coste de la solucion. Recurrencia y orden de complejidad
// T(n) =	C0 caso base
//			2T(n/2) + C1 caso recursivo
// 
// O(n) siendo n el númnero de elementos
//*******************
// Aqui la funcion recursiva que resuelve el problema
std::pair<int, bool> resolver(std::vector<int> const& v, int ini, int fin) {
	if (ini + 1 == fin) { // un elemento
		if (v[ini] % 2 == 0) return { 1, true }; // 1 si es par
		else return { 0, true }; // 0 si es impar
	}
	else {
		int mitad = (ini + fin) / 2;
		std::pair<int, bool> paresIz = resolver(v, ini, mitad);
		std::pair<int, bool> paresDr = resolver(v, mitad, fin);
		if (std::abs(paresIz.first - paresDr.first) > 2 || !paresDr.second || !paresIz.second
			) return { 0, false }; // devuelvo false si una de sus mitades no es caucásica o si la diferencia entre los pares de sus mitades es mayor que 2
		else return { paresIz.first + paresDr.first, true }; // devuelvo la suma de los pares de las mitades y que es caucásico
	}
}
// Tratar cada caso
bool resuelveCaso() {
	// Lectura de los datos
	
	int num;
	std::cin >> num;
	if (num == 0) return false;
	std::vector<int> v(num);
	for (int i = 0; i < num; ++i) {
		std::cin >> v[i];
	}
	// resolver
	std::pair<int, bool> sol = resolver(v, 0, v.size());
	// Escribir los resultados
	if (sol.second) std::cout << "SI" << '\n';
	else std::cout << "NO\n";
	return true;
}
int main() {
	// Para la entrada por fichero.
#ifndef DOMJUDGE
	std::ifstream in("datos.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while (resuelveCaso())
		;
	// Para restablecer entrada.
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	//system("PAUSE");
#endif
	return 0;
}