//Jorge Torres 
//A66
# ifndef HORAS
# define HORAS

# include <iostream>
# include <array>
# include <stdexcept>
class Horas {

private:
	int horas, minutos, segundos;

public:
	Horas(int h, int m, int s) :
		horas(h), minutos(m), segundos(s) {
		if (h < 0 || h > 23 || m < 0 || s < 0 || m > 59 || s > 59) throw std::invalid_argument(" Hora invalida ");
	};

	Horas() : horas(0), minutos(0), segundos(0) {};

	//sobrecargar del operador <
	bool operator<(Horas const& h) const {
		if (horas < h.horas) return true;
		else if (horas > h.horas) return false;
		else if (minutos < h.minutos) return true;
		else if (minutos > h.minutos) return false;
		else if (segundos < h.segundos) return true;
		else return false;
	}

	bool operator == (Horas const& h) const {
		if (this->horas == h.horas && this->minutos == h.minutos && this->segundos == h.segundos) return true;
		return false;
	}

	bool operator <= (Horas const& h) const {
		return *this < h || *this == h;
	}

	Horas& operator=(Horas const& other) {
		if (this != &other) {
			horas = other.horas; minutos = other.minutos; segundos = other.segundos;
		}
		return *this;
	}

	Horas& operator + (Horas const& other) {
		horas += other.horas; minutos += other.minutos; segundos += other.segundos;
		if (segundos >= 60) {
			segundos -= 60;
			minutos++;
		}
		if (minutos >= 60) {
			minutos -= 60;
			horas++;
		}
		if (horas >= 24) throw std::invalid_argument(" Hora invalida ");
		return *this;
	}

	int get_hora() const { return horas; }
	int get_minuto() const { return minutos; }
	int get_segundo() const { return segundos; }
};

inline std::istream& operator >> (std::istream& entrada, Horas& h) {
	int x, y, z;
	char aux;
	entrada >> x >> aux >> y >> aux >> z;
	h = Horas(x, y, z);
	return entrada;
}

inline std::ostream& operator << (std::ostream& salida, Horas const& f) {
	if (f.get_hora() < 10) {
		salida << "0" << f.get_hora() << ':';
	}
	else salida << f.get_hora() << ':';
	if (f.get_minuto() < 10) {
		salida << "0" << f.get_minuto() << ':';
	}
	else salida << f.get_minuto() << ':';
	if (f.get_segundo() < 10) {
		salida << "0" << f.get_segundo();
	}
	else salida << f.get_segundo();

	return salida;
}

#endif