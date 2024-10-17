# ifndef Polinomio
# define Polinomio

#include <iostream>
#include <array>
#include <stdexcept>
#include <vector>

class polinomio {
private:
	std::vector<std::pair<int, int>>v;
	const int tamVec = 8;

	int busquedaBinaria(std::vector<std::pair<int, int>>vec, int ini, int fin, int const& coef, int const& grado) {
		if (ini + 1 == fin) {
			if (v[ini].second > grado) {
				return ini + 1;
			}
			else return ini;
		}
		else {
			int m = (ini + fin) / 2;
			if (v[m].second > grado) {
				return busquedaBinaria(vec, m, fin, coef, grado);
			}
			else return busquedaBinaria(vec, ini, m, coef, grado);
		}
	}

public:
	polinomio() {}

	void monomio(int coef, int grado)	{
		std::pair<int, int> nuevo;
		nuevo.first = coef;
		nuevo.second = grado;
		if (v.size() == 0) {
			v.push_back(nuevo);
		}
		else {
			int aux = busquedaBinaria(this->v, 0, v.size(), coef, grado);

			if (aux >= v.size()) {
				v.push_back(nuevo);
			}
			else {
				if (v[aux].second == grado) {
					v[aux].first += coef;
				}
				else if (aux == 0 && aux == v.size() - 1) {
				v.push_back(nuevo);
				swap(v[aux], v[aux + 1]);
				}
				else {
				v.resize(v.size() + 1);
				for (int i = v.size() - 1; i > aux; i--) {
					v[i + 1] = v[i];
				}
				v[aux] = nuevo;
				}
			}
		}
	}

	long long int resolver(int const& variable) {
		long long int sol = 0, aux2, grado;
		std::vector<long long int>aux(v.size()); // guarda potencias de monomios

		for (int i = v.size() - 1; i >= 0; i--) {
			if (i == v.size() - 1) {
				aux2 = 1;

				for (int j = 0; j < v[i].second; j++) {
					aux2 *= variable;
				}
				aux[i] = aux2;
				sol = aux2 * v[i].first;
			}
			else {
				grado = v[i].second - v[i + 1].second;
				aux2 = 1;
				if (v[i].second != 1) {
					if (grado >= 2) {
						for (int i = 0; i < grado; i++) {
							aux2 *= variable;
						}
					}
					else {
						aux2 = variable;
					}
					aux2 *= aux[i + 1];
					aux[i] = aux2;
				}
				else {
					aux2 = variable;
					aux[i] = variable;
				}
				sol += aux2 * v[i].first; // multiplica por el coeficiente
			}
		}
		return sol;
	}
};

#endif
