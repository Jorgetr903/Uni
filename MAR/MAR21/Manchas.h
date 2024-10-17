#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using Mapa = vector<vector<char>>;

class Manchas {
private:
	int F, C;
	vector<vector<bool>> visitados;
	vector<vector<bool>> visitados2;
	int num; //numero de manchas
	int maximo; //tama�o de la mancha mas grande

	bool correcta(int i, int j) const {
		return 0 <= i && i < F && 0 <= j && j < C;
	}

public:
	Manchas(Mapa const& M) : F(M.size()), C(M[0].size()),
		visitados(F, vector<bool>(C, false)), visitados2(F, vector<bool>(C, false)), num(0), maximo(0){
		for (int i = 0; i < F; ++i) {
			for (int j = 0; j < C; ++j) {
				if (!visitados[i][j] && M[i][j] == '#') { // se recorre una nueva mancha
					++num;
					int nuevotam = dfs(M, i, j);
					maximo = max(maximo, nuevotam);
				}
			}
		}
	}

	const vector<pair<int, int>> dirs = { {1,0},{0,1},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1} };

	int dfs(Mapa const& M, int i, int j) {
		visitados[i][j] = true;
		int tam = 1;
		for (auto d : dirs) {
			int ni = i + d.first, nj = j + d.second;
			if (correcta(ni, nj) && M[ni][nj] == '#' && !visitados[ni][nj]) {
				tam += dfs(M, ni, nj);
			}
		}
		return tam;
	}

	int nuevasManchas(Mapa const& M, int i, int j) {
		visitados2[i][j] = true;
		int tam = 1;
		for (auto d : dirs) {
			int ni = i + d.first, nj = j + d.second;
			if (correcta(ni, nj) && M[ni][nj] == '#' && !visitados[ni][nj]) {
				tam += dfs(M, ni, nj);
			}
		}
		return max(tam, maximo);
	}

	int numero() const {
		return num;
	}

	int maxim() const {
		return maximo;
	}

};
