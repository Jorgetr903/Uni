// Problema Smart farming

// IMPORTANTE

// Nombre y apellidos del alumno
// Usuario del juez de clase
// Usuario que has utilizado en esta prueba


#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <utility>
#include <vector>
using namespace std;


// Explicación de la representación elegida para resolver el problema.






// No olvides poner comentarios en el codigo para que se puedan entender bien 
// las funciones.
// No olvides poner el coste de cada una de las funciones y explicarlo.
class smartFarming {
private:
    using tsector = std::string;
    using tplaga = std::string;




public:
    smartFarming() {}
    // Coste de la función y justificación
    void alta(tsector const& id, int n) {



    }

    // Coste de la función y justificación
    void datos(tsector const& id, tplaga const& p, int n) {




    }

    // Coste de la función y justificación
    std::vector<std::pair<tsector, tplaga>> fumigar() {




    }


    // Coste de la función y justificación
    std::vector<std::pair<tplaga, int>> plagas(tsector const& id) {



    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    std::string op;
    smartFarming sf;
    std::cin >> op;  // operacion a realizar
    if (!std::cin)
        return false;
    std::string id; std::string plaga; int n;
    while (op != "FIN") {
        try {
            if (op == "alta") {
                std::cin >> id >> n;  // sector - numero de plantas
                sf.alta(id, n);
            }
            else if (op == "datos") {
                std::cin >> id >> plaga >> n; // sector, plaga, numero de plantas afectadas
                sf.datos(id, plaga, n);
            }
            else if (op == "fumigar") {
                std::vector<std::pair<std::string, std::string>> v = sf.fumigar();
                // Escribir el resultado
                for (auto const& s : v) {
                    std::cout << "Fumigar la plaga " << s.second << " del sector";
                    std::cout << ' ' << s.first << '\n';
                }
            }
            else if (op == "plagas") {
                std::cin >> id; // sector
                std::vector<std::pair<std::string, int>> v = sf.plagas(id);
                // Escribir el resultado
                std::cout << "Plagas del sector " << id << " :";
                for (auto const& s : v)
                    std::cout << ' ' << s.first << ' ' << s.second;
                std::cout << '\n';
            }
        }
        catch (std::domain_error& d) {
            std::cout << "ERROR: " << d.what() << '\n';
        }
        std::cin >> op;
    }
    std::cout << "---" << '\n';

    return true;

}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample3.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso())
        ;

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
