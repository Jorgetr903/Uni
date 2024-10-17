//https://drive.google.com/drive/u/1/folders/1c1ACtFf70zoqOfGgW-0w_BsF32snCx4y
#include <iostream> 
#include <fstream> 
#include "LinkedListQueue.h"



// Prioridad de los valores enteros
class mult {
private:
	int n;
public:
	mult(int k) : n(k) {}
	bool operator() (int x) {
		return x % n == 0;
	}
};

// Prioridad de los caracteres
class vocal {
public:
	bool operator() (char c) {
		return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
	}
};

bool resuelveCaso() {
	int ops; std::cin >> ops;
	if (ops == 0) return false;
	char tipo; std::cin >> tipo;
	// Cola de enteros
	if (tipo == 'I') {
		mult prioridad(2);
		queue<int, mult> q(prioridad);
		for (int i = 0; i < ops; ++i) {
			try {
				char x; int n;
				std::cin >> x;
				if (x == 'E') { std::cin >> n; q.push(n); }
				else if (x == 'D') q.pop();
				else if (x == 'P') std::cout << q.front() << '\n';
			}
			catch (std::domain_error& e) {
				std::cout <<"ERROR: " <<e.what() << '\n';
			}
		}
	}
	else { // Cola de caracteres
		vocal v;
		queue<char, vocal> q(v);
		for (int i = 0; i < ops; ++i) {
			try {
				char x; char n;
				std::cin >> x;
				if (x == 'E') { std::cin >> n; q.push(n); }
				else if (x == 'D') q.pop();
				else if (x == 'P') std::cout << q.front() << '\n';
			}
			catch (std::domain_error& e) {
				std::cout <<"ERROR: "<< e.what() << '\n';
			}
		}
	}
	std::cout << "---\n";
	return true;
}



int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


	while (resuelveCaso());


#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
