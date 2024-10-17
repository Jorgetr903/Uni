#include<iostream>
#include <fstream>
#include"Matriz.h"
using namespace std;


//Alumnos: Jorge Torres Ruiz (Mar295), Ignacio García Fernández (Mar235)

//Plantea y explica la recurrencia
//
//Definicion
// Definimos n como el número de filas del tablero y m como el número de columnas.
// Nuestra recurrencia se llamrá FormasSaltar(i,j) que obtiene el número de formas diferentes que hay para llegar a la celda (n,m) desde la casilla (i,j)
//
//Llamada inicial
// FormasSaltar(1,1) siendo la casilla inicial del tablero
//
//Caso/s base
// Si i o j son 0 entonces FormasSaltar(i, j) = 0 (no pertenecen a nuetsro tablero)
// FormasSaltar(n, m) = 1 se ha llegado a la celda objetivo, necesitamos sumar 1 a nuestra llamada.
// Si i+aij > n y j + aij > m FormasSaltar(i,j) = 0 esto significa que si el numero solo nos permite saltar a posiciones fuera del tablero entonces el resultado es 0.
//
//Casos recursivos
// Si i+aij > n FormasSaltar(i,j)  = FormasSaltar(i, j+aij) Nuestra casilla solo puede saltar hacia la derecha
// Si j +aij > m FormasSaltar(i,j) = FormasSaltar(i + aij, j) Nuesta casilla solo puede saltar hacia abajo
// Si no ocurre ninguna de las anteriores FormasSaltar(i, j) = FormasSaltar(i, j+aij) + FormasSaltar(i + aij, j) Desde nuestra casilla se puede saltar hacia abajo y hacia la derecha. Por tanto sumamos el resultado de ambas posiciones de la matriz.


long long int numCaminos(Matriz<int> const& tablero, int N, int M) {

	//Resuelve el problema utilizando programacion dinamica ITERATIVA

	// Cada posicion i, j depende como mucho de una posicion más a la derecha y una posición por debajo, es por eso que realizamos el llenado de la matriz de abajo hacia arriba y de derecha a izquerda.
	//Como la matriz tiene fila y columna 0 estas posiciones se rellenan con ceros, ya que no forman parte de nuestro tabero.
	//
	//Analiza justificadamente el coste en tiempo y espacio
	//El coste en espacio es O(N*M) siendo N el numero de filas y M el de columnas
	//El coste en tiempo es idéntico O(N*M) ya que calcular cada posicioón de la matriz nos cuesta constante al ser sumas. El coste es le de recorrer la matriz.
	//

	Matriz<int> matriz(N + 1, M + 1); //Creamos la matriz que vamos a rellenar

	for (int i = N; i > 0; i--) {
		matriz[i][0] = 0; //Caso base (no pertenece a nuestro tablero)
		for (int j = M; j > 0; j--) {
			matriz[0][j] = 0; //Caso base (no pertenece a nuestro tablero)

			if (i == N && j == M) { // Estamos en la casilla final
				matriz[i][j] = 1;
			}
			else if (i + tablero[i - 1][j - 1] > N && j + tablero[i - 1][j - 1] > M) { //se sale del tablero de ambas formas
				matriz[i][j] = 0;
			}
			else {
				if (i + tablero[i - 1][j - 1] > N) //no puedes saltar hacia abajo
				{
					matriz[i][j] = matriz[i][j + tablero[i - 1][j - 1]];
				}
				else if (j + tablero[i - 1][j - 1] > M) //no puedes saltar hacia derecha
				{
					matriz[i][j] = matriz[i + tablero[i - 1][j - 1]][j];
				}
				else { //Puedes saltar en ambas direcciones
					matriz[i][j] = matriz[i + tablero[i - 1][j - 1]][j] + matriz[i][j + tablero[i - 1][j - 1]];
				}
			}

		}
	}

	return matriz[1][1]; //Devolvemos la casilla (1,1)


}


bool resuelveCaso() {
	int N, M;
	cin >> N >> M;
	if (!cin) {
		return false;
	}
	else {
		Matriz<int> tablero(N, M);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
				cin >> tablero[i][j];
		}

		cout << numCaminos(tablero, N, M) << '\n';
		return true;
	}
}


int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}