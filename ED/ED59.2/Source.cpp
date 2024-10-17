// Problema: Autoescuela
//Jorge Torres
//A66

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <set>
using namespace std;

class autoescuela {
private:
    unordered_map<string, set<string>> profesores; // profesores, set de alumnos
    unordered_map<string, pair<int, string>> alumnos; // alumnos, puntuacion y profesor

public:
    void alta(string a, string p) {
        if (!alumnos.count(a)) {
            alumnos.insert({ a, {0, p} });
            profesores.insert(p, a);
        }
        else {
            string prof = alumnos.at(a).second;
            alumnos.at(a).second = p;
            profesores.insert(p, a);
            profesores.at(prof).erase(a);
        }
    }

    bool es_alumno(string a, string p) {
        if (profesores[p].count(a)) {
            return true;
        }
        else return false;
    }

    int puntuacion(string a) {
        if (alumnos.count(a)) {
            return alumnos[a].first;
        }
        else {
            throw domain_error("El alumno " + a + " no esta matriculado");
        }
    }

    void actualizar(string a, int n) {
        if (alumnos.count(a)) {
            alumnos[a].first += n;
        }
        else {
            throw domain_error("El alumno " + a + " no esta matriculado");
        }
    }

    vector<string> examen(string p, int n) {
        vector<string> res;
        auto at = profesores.find(p);
        if (at != profesores.end()) {
            for (string alum : at->second) {
                if (alumnos.at(alum).first >= n) {
                    res.push_back(alum);
                }
            }
        }
    }

    void aprobar(string a) {
        if (alumnos.count(a)) {
            string prof = alumnos.at(a).second;
            alumnos.erase(a);
            profesores.at(prof).erase(a);
        }
        else {
            throw domain_error("El alumno " + a + " no esta matriculado");
        }
    }
};

bool resuelveCaso() {
    std::string orden, P, A;
    int punt;
    std::cin >> orden;
    if (!std::cin)
        return false;

    autoescuela atesc;

    while (orden != "FIN") {
        try {
            if (orden == "alta") {
                std::cin >> A >> P;
                atesc.alta(A, P);
            }
            else if (orden == "es_alumno") {
                std::cin >> A >> P;
                bool esAlumno = atesc.es_alumno(A, P);
                if (esAlumno) {
                    cout << A << " es alumno de " << P << '\n';
                }
                else {
                    cout << A << " no es alumno de " << P << '\n';
                }
            }
            else if (orden == "puntuacion") {
                std::cin >> A >> punt;
                punt = atesc.puntuacion(A);
                std::cout << "Puntos de " << A << ": " << punt << '\n';
            }
            else if (orden == "actualizar") {
                std::cin >> A >> punt;
                atesc.actualizar(A, punt);
            }
            else if (orden == "exmen") {
                std::cin >> P >> punt;
                vector<string> alum = atesc.examen(P, punt);
                cout << "Alumnos de " << P << " a examen:";
                for (string a : alum) {
                    cout << a << " ";
                }
                cout << '\n';
            }
            else if (orden == "aprobar") {
                std::cin >> A;
                atesc.aprobar(A);
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