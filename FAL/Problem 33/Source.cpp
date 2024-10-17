// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83

#include <iostream>
#include <iomanip>
#include <fstream>
/*
funcion recursiva

no final
resolver1(dato1, dato2) =    (dato1 + dato2) %10 si dato1 + dato2 < 10
                             resolver1(dato1 / 10, dato2 / 10) * 10 + (dato1 + dato2) %10 si dato1 + dato2 >= 10

final
resolver2(digito1, digito2, sol, pot) =    ((dato1 + dato2) %10)*pot + sol si dato1 + dato2 < 10
										resolver2(dato1 / 10, dato2 / 10, ((dato1 + dato2) %10)*pot + sol, 10*pot) si dato1 + dato2 >= 10
*/
// funcion que resuelve el problema
long resolver1(int dato1, int dato2) {
	long suma = dato1 + dato2;
	if (suma < 10) {
		return suma % 10;
	}
	else {
		return resolver1(dato1 / 10, dato2 / 10) * 10 + suma % 10;
	}
}
long resolver2(int dato1, int dato2, int sol, int pot) {
	long suma = dato1 + dato2;
	int digito = suma % 10;
	if (suma < 10) {
		return digito * pot + sol;
	}
	else {
		return resolver2(dato1 / 10, dato2 / 10, digito * pot + sol, 10 * pot);
	}
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuracion, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	int digito1, digito2;
	std::cin >> digito1 >> digito2;
	long sol = resolver1(digito1, digito2);
	long sol2 = resolver2(digito1, digito2, 0, 1);
	// escribir sol
	std::cout << sol << " " << sol2 << '\n';

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