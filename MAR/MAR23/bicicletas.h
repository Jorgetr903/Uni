#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"
#include <vector>
using namespace std;

class bicicletas {
private:
	int coste, puentesPresup, islas;
	vector<Arista<int>> arm;

public:
    bicicletas(GrafoValorado<int> const& gr, int a) : coste(0), puentesPresup(a), islas(gr.V()) {
        arm_kruskal(gr);
    }

    void arm_kruskal(GrafoValorado<int> const& g) {
        PriorityQueue<Arista<int>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top();
            pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                arm.push_back(a);
                coste += a.valor();
                if (arm.size() == g.V() - 1)
                    break;
            }
        }
    }
    pair<int, bool> solucion() {
        return { coste, (arm.size() <= puentesPresup && arm.size() == islas - 1) };
    }
};
