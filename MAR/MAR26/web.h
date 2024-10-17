#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class web {

private:
    int origen = 0, destino;

    const int INF = numeric_limits<int>::max();
    vector<int> dist;
    IndexPQ<int> pq;

    void relajar(AristaDirigida<int> a) {
        int n1, n2;

        n1 = a.desde();
        n2 = a.hasta();

        if (dist[n2] > dist[n1] + a.valor()) {
            dist[n2] = dist[n1] + a.valor();
            pq.update(n2, dist[n2]);
        }
    }

public:

    web(DigrafoValorado<int> const& g) : dist(g.V(), INF), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);

        while (!pq.empty()) {
            int nodo = pq.top().elem;
            pq.pop();

            for (auto a : g.ady(nodo)) {
                relajar(a);
            }
        }
    }

    int sol(int const& dst) {
        if (dist[dst] == INF) {
            return -1;
        }
        return dist[dst];
    }
};
