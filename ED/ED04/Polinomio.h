# ifndef Polinomio
# define Polinomio

# include <iostream>
# include <array>
# include <stdexcept>
#include <vector>
using namespace std;

class Polinomio {
private:
	vector<pair<int, int>>v;
public:

	void Monomio(int& grado, int& coef, vector<bool>& existeGr) {
		pair<int, int> nuevo;

		nuevo.first = grado;
		nuevo.second = coef;
		if (v.size() == 0) {
			v.push_back(nuevo);
		}
		else {
			for (int i = 0; i < v.size(); i++) {
				if (grado == v[i].first) {
					v[i].second += nuevo.second;
				}
				else {
					for (int i = 0; i < v.size(); i++) {
						if (nuevo.first > v[i].first && nuevo.first < v[i + 1].first) {
							for (int h = i + 1; h < v.size(); h++) {
								v[h + 1] = v[h];
							}
							v[i] = nuevo;
						}
					}
				}
			}
		}
	}
};



#endif