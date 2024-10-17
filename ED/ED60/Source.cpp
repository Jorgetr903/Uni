// Problema: Carnet por puntos
//Jorge Torres
//A66
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <unordered_map>
using namespace std;

class carnet_puntos {
private:
    unordered_map<string, pair<int, list<string>::iterator>> conductores; //DNI, puntos e iterador
    unordered_map<int, stack<string>> listaPorPuntos; //puntos, lista de conductores con esos puntos

public:
    void nuevo(string dni) {
        if (!conductores.count(dni)) {
            listaPorPuntos[15].push(dni);
            conductores[dni] = { 15, listaPorPuntos[15].top()};
        }
        else {
            throw domain_error("Conductor duplicado");
        }
    }

    void quitar(string dni, int punt) {
        if (conductores.count(dni)) {
            listaPorPuntos[conductores[dni]].erase(dni);
            if (conductores[dni] - punt > 0) {
                conductores[dni] -= punt;
            }
            else {
                conductores[dni] = 0;
            }
            listaPorPuntos[conductores[dni]].insert(dni);
        }
        else {
            throw domain_error("Conductor inexistente");
        }
    }

    void recuperar(string dni, int punt) {
        if (conductores.count(dni)) {
            listaPorPuntos[conductores[dni]].erase(dni);
            if (conductores[dni] + punt < 15) {
                conductores[dni] += punt;
            }
            else {
                conductores[dni] = 15;
            }
            listaPorPuntos[conductores[dni]].insert(dni);
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
            return listaPorPuntos[punt].size();
        }
        else {
            throw domain_error("Puntos no validos");
        }
    }

    unordered_set<string> lista_por_puntos(int punt) {
        if (punt >= 0 && punt <= 15) {
            return listaPorPuntos[punt];
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
            else if (orden == "recuperar") {
                std::cin >> dni >> punt;
                dgt.recuperar(dni, punt);
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
            else if (orden == "lista_por_puntos") {
                std::cin >> punt;
                unordered_set<string> lista = dgt.lista_por_puntos(punt);
                std::cout << "Tienen " << punt << " puntos: ";
                for (auto elem : lista) {
                    cout << elem << " ";
                }
                cout << '\n';
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