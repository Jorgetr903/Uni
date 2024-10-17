// Problema: Las torres del desierto

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <map>
#include <set>
#include <stdexcept>
using namespace std;

enum class Direccion { Norte, Sur, Este, Oeste };

istream& operator>>(istream& is, Direccion& dir) {
    string palabra; is >> palabra;
    if (palabra == "Norte") dir = Direccion::Norte;
    else if (palabra == "Sur") dir = Direccion::Sur;
    else if (palabra == "Este") dir = Direccion::Este;
    else if (palabra == "Oeste") dir = Direccion::Oeste;
    else throw std::domain_error("Lectura de direccion incorrecta");
    return is;
}

class Desierto {
private:
    unordered_map<string, std::pair<int, int>> torres;
    map<pair<int, int>, string> posX; //x, y, nombre
    map<pair<int, int>, string> posY; //y, x, nombre

public:
    void anyadir_torre(const string& nombre, int x, int y) {
        if (!torres.count(nombre)) {
            if (posX.find({x, y}) != posX.end()) {
                throw domain_error("Posicion ocupada");
            }
            else {
                torres.insert({ nombre, {x, y} });
                posX[{x, y}] = nombre;
                posY[{y, x}] = nombre;
            }
        }
        else {
            throw domain_error("Torre ya existente");
        }
    }

    void eliminar_torre(const string& nombre) {
        auto at = torres.find(nombre);
        if (at == torres.end()) {
            throw domain_error("Torre no existente");
        }
        else {
            posX.erase({ at->second.first, at->second.second });
            posY.erase({ at->second.second, at->second.first });
            torres.erase(at);
        }
    }

    pair<int, int> posicion(const string& nombre) const {
        auto it = torres.find(nombre);
        if (it != torres.end()) {
            return it->second;
        }
        else {
            throw domain_error("Torre no existente");
        }
    }

    pair<bool, string> torre_en_posicion(int x, int y) const {
        if (posX.find({ x,y }) != posX.cend()) {
            return { true, posX.at({ x,y }) };
        }
        else {
            return { false ,"NO" };
        }
    }

    string torre_mas_cercana(const string& nombre, const Direccion& dir) const {
        auto it = torres.find(nombre);

        if (it != torres.cend()) {

            if (dir == Direccion::Oeste || dir == Direccion::Este) {
                auto it2 = posY.find({ (*it).second.second,(*it).second.first });
                int y = (*it2).first.first;
                if (dir == Direccion::Oeste) {
                    if (it2 != posY.cbegin()) {
                        --it2;
                        if ((*it2).first.first != y) {
                            throw domain_error("No hay torres en esa direccion");
                        }
                    }
                    else {
                        throw domain_error("No hay torres en esa direccion");
                    }
                }
                else {
                    if (it2 != posY.cend()) {
                        ++it2;
                        if (it2 == posY.cend() || (*it2).first.first != y) {
                            throw domain_error("No hay torres en esa direccion");
                        }
                    }
                    else {
                        throw domain_error("No hay torres en esa direccion");
                    }
                }
                return (*it2).second;
            }
            else {
                auto it2 = posX.find((*it).second);
                int x = (*it2).first.first;
                if (dir == Direccion::Sur) {
                    if (it2 != posX.cbegin()) {
                        --it2;
                        if ((*it2).first.first != x) {
                            throw domain_error("No hay torres en esa direccion");
                        }
                    }
                    else {
                        throw domain_error("No hay torres en esa direccion");
                    }
                }
                else {
                    if (it2 != posX.cend()) {
                        ++it2;
                        if (it2 == posX.cend() || (*it2).first.first != x) {
                            throw domain_error("No hay torres en esa direccion");
                        }
                    }
                    else {
                        throw domain_error("No hay torres en esa direccion");
                        return (*it2).second;
                    }
                }
                return (*it2).second;
            }
        }
        else {
            throw domain_error("Torre no existente");
        }
    }
};

bool tratar_caso() {

    std::string orden, torre;
    int posX, posY;
    std::cin >> orden;
    if (!std::cin)
        return false;

    Desierto desierto;
    Direccion dir;
    while (orden != "FIN") {
        try {
            if (orden == "anyadir_torre") {
                std::cin >> torre >> posX >> posY;
                desierto.anyadir_torre(torre, posX, posY);
            }
            else if (orden == "torre_en_posicion") {
                std::cin >> posX >> posY;
                pair<bool, string> posicionOcupada = desierto.torre_en_posicion(posX, posY);
                if (!posicionOcupada.first) {
                    cout << "NO\n";
                }
                else {
                    cout << "SI " << posicionOcupada.second << '\n';
                }
            }
            else if (orden == "posicion") {
                std::cin >> torre;
                pair<int, int> posicion = desierto.posicion(torre);
                cout << posicion.first << " " << posicion.second << '\n';
            }
            else if (orden == "torre_mas_cercana") {
                std::cin >> torre >> dir;
                string torreMasCercana = desierto.torre_mas_cercana(torre, dir);
                cout << torreMasCercana << '\n';
            }
            else if (orden == "eliminar_torre") {
                std::cin >> torre;
                desierto.eliminar_torre(torre);
            }
            else
                std::cout << "OPERACION DESCONOCIDA\n";
        }
        catch (std::domain_error e) {
            std::cout << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}


int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    ifstream in("datos.in");
    auto cinbuf = cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 



    while (tratar_caso());


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}