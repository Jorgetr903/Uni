#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

class cole {

private:
    const int INF = numeric_limits<int>::max();
    vector<int> dist;
    IndexPQ<int> pq;
    int destino;
    vector<int> contadorCaminos;

    void relajar(AristaDirigida<int> a) {
        int n1, n2;
        n1 = a.desde();
        n2 = a.hasta();

        if (dist[n2] > dist[n1] + a.valor()) {
            dist[n2] = dist[n1] + a.valor();
            pq.update(n2, dist[n2]);
            contadorCaminos[n2] = contadorCaminos[n1];
        }
        else if (dist[n2] == dist[n1] + a.valor()) {
            contadorCaminos[n2] += contadorCaminos[n1];
        }
    }

public:
    cole(DigrafoValorado<int> const& g) : dist(g.V(), INF), pq(g.V()), destino(g.V() - 1), contadorCaminos(g.V(), 0) {
        dist[0] = 0;
        pq.push(0, 0);
        contadorCaminos[0] = 1;
        while (!pq.empty()) {
            int nodo = pq.top().elem;
            pq.pop();

            for (auto a : g.ady(nodo)) {
                relajar(a);
            }
        }
    }

    int sol() {
        return contadorCaminos[destino];
    }
};