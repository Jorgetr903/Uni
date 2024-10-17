#include "GrafoValorado.h"
#include <vector>
using namespace std;

class camiones {
private:
	vector<bool> visitados;
	int intersecciones, origen, destino;

public:
	camiones(GrafoValorado<int> const& g, int const& origen, int const& destino, int const& anchura) : visitados(g.V(), false), intersecciones(g.V()), origen(origen), destino(destino) {
		if (!visitados[origen]) {
			dfs(g, origen, anchura);
		}
	}

	void dfs(GrafoValorado<int> const& g, int v, int anchura) {
		visitados[v] = true;
		for (auto a : g.ady(v)) {
			if (a.valor() >= anchura) {
				int w = a.otro(v);
				if (!visitados[w]) {
					dfs(g, w, anchura);
				}
			}
		}
	}

	bool camino() {
		return visitados[origen] && visitados[destino];
	}
};
