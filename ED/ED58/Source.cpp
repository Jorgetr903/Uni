// Problema: Carnet por puntos
//Jorge Torres
//A66
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
using namespace std;

class carnet_puntos {
private:
    unordered_map<string, int> conductores; //DNI, puntos
    unordered_map<int, int> puntos; //puntos, cantidad de conductores que tienen esos puntos

public:
    void nuevo(string dni) {
        if (!conductores.count(dni)) {
            conductores.insert({ dni, 15 });
            puntos[15]++;
        }
        else {
            throw domain_error("Conductor duplicado");
        }
    }

    void quitar(string dni, int punt) {
        if (conductores.count(dni)) {
            puntos[conductores[dni]]--;
            if (conductores[dni] - punt < 0) {
                conductores[dni] = 0;
            }
            else {
                conductores[dni] -= punt;
            }
            puntos[conductores[dni]]++;
        }
        else {
            throw domain_error("Conductor inexistente");
        }
    }

    int consultar(string dni) {
        if (conductores.count(dni)) {
            return conductores[dni];
        }
        else {
            throw domain_error("Conductor inexistente");
        }
    }

    int cuantos_con_puntos(int punt) {
        if (punt >= 0 && punt <= 15) {
            return puntos[punt];
        }
        else {
            throw domain_error("Puntos no validos");
        }
    }
};

bool resuelveCaso() {
    std::string orden, dni;
    int punt;
    std::cin >> orden;
    if (!std::cin)
        return false;

    carnet_puntos dgt;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo") {
                std::cin >> dni;
                dgt.nuevo(dni);
            }
            else if (orden == "quitar") {
                std::cin >> dni >> punt;
                dgt.quitar(dni, punt);
            }
            else if (orden == "consultar") {
                std::cin >> dni;
                punt = dgt.consultar(dni);
                std::cout << "Puntos de " << dni << ": " << punt << '\n';
            }
            else if (orden == "cuantos_con_puntos") {
                std::cin >> punt;
                int cuantos = dgt.cuantos_con_puntos(punt);
                std::cout << "Con " << punt << " puntos hay " << cuantos << '\n';
            }
            else
                std::cout << "OPERACION DESCONOCIDA\n";
        }
        catch (std::domain_error e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}


int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());


    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}