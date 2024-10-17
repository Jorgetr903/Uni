//Jorge Torres 
//A66
# ifndef PELICULA
# define PELICULA

#include <iostream>
#include <array>
#include <string>
#include <stdexcept>
#include "Horas.h"
using namespace std;

class Pelicula {
private:
	Horas hora, duracion, salida;  string nombre;

public:
	Pelicula(Horas h, Horas d, string n) :
		hora(h), duracion(d), nombre(n), salida(h + d) {
	};

	Pelicula() : hora(Horas()), duracion(Horas()), nombre(), salida(Horas()) {};

	Pelicula& operator=(Pelicula const& other) {
		if (this != &other) {
			hora = other.hora; duracion = other.duracion; nombre = other.nombre; salida = other.salida;
		}
		return *this;
	}

	bool operator<(Pelicula const& h) const {
		if (salida < h.salida) return true;
		else if (salida == h.salida) {
			if (nombre < h.nombre) return true;
			else return false;
		}
		else return false;
	}

	Horas get_hora() const { return hora; }
	Horas get_duracion() const { return duracion; }
	string get_nombre() const { return nombre; }
	Horas get_salida() const { return salida; }
};

inline std::istream& operator >> (std::istream& entrada, Pelicula& p) {
	Horas h, d, s; string n;
	entrada >> h >> d;
	getline(cin, n);
	p = Pelicula(h, d, n);
	return entrada;
}

inline std::ostream& operator << (std::ostream& salida, Pelicula const& f) {
	salida << f.get_salida() << " " << f.get_nombre() << '\n';
	return salida;
}

#endif
