#include "Grafo.h"
#include <queue>
using namespace std;

class calculadora {
private:
	const int MAX = 10000;
	const int INF = 1000000000; //infinito

	int adyacente(int v, int i) {
		switch (i) {
		case 0: return (v + 1) % MAX; 
		case 1: return (v * 2) % MAX;
		case 2: return v / 3;
		}
	}

public:
	int bfs(int origen, int destino) {
		if (origen == destino) return 0;
		vector<int> distancia(MAX, INF);
		distancia[origen] = 0;

		queue<int> cola; 
		cola.push(origen); //meto a la cola el origen

		while (!cola.empty()) {
			int v = cola.front(); 
			cola.pop();

			for (int i = 0; i < 3; ++i) {
				int w = adyacente(v, i);
				if (distancia[w] == INF) {
					distancia[w] = distancia[v] + 1; //le sumamos 1 a la distancia anterior
					if (w == destino) return distancia[w]; //si el valor es el destino devolvemos la distancia
					else cola.push(w);//si no es el destino metemos el valor en la cola
				}
			}
		}
	}
};