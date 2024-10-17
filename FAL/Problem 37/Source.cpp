// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

// función que resuelve el problema
int buscarIz(std::vector <int> const& v, int altura, int ini, int fin) {
    if (ini >= fin) return ini;
    else if (ini + 1 == fin) return ini; 
    else { 
        int mitad = (ini + fin - 1) / 2;
        if (v[mitad] < altura) return buscarIz(v, altura, mitad + 1, fin);
        else return buscarIz(v, altura, ini, mitad + 1);
    }
}

int buscarDr(std::vector <int> const& v, int altura, int ini, int fin) {
    if (ini >= fin) return ini; 
    else if (ini + 1 == fin) return ini; 
    else { 
        int mitad = (ini + fin) / 2;
        if (altura < v[mitad]) return buscarDr(v, altura, ini, mitad);
        else return buscarDr(v, altura, mitad, fin);
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int elementos, altura;
    std::cin >> elementos >> altura;
    if (!std::cin)
        return false;

    std::vector<int> v(elementos);
    for (int i = 0; i < v.size(); i++) {
        std::cin >> v[i];
    }

    int solIz = buscarIz(v,altura, 0, v.size());

    if (solIz == v.size() || v[solIz] != altura)
        std::cout << "NO EXISTE \n";
    else {
        int solDr = buscarDr(v, altura, 0, v.size());
        if (solIz == solDr) {
            std::cout << solIz << '\n';
        }
        else {
            std::cout << solIz << " " << solDr << '\n';
        }
    }
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}