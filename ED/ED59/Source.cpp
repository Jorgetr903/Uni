// Problema: Autoescuela
//Jorge Torres
//A66


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include<set>
using namespace std;

class autoescuela {

private:
    unordered_map<string, pair<string, int>> alumno;
    unordered_map < string, set<string>> profesores;
public:

    autoescuela() {}

    void alta(string const& a, string const& p) {
        if (!alumno.count(a)) {
            alumno[a] = { p, 0 };
            profesores[p].insert(a);
        }
        else {
            profesores[alumno[a].first].erase(a);
            alumno[a].first = p;
            profesores[p].insert(a);
        }
    }

    bool es_alumno(string a, string p) {
        return alumno[a].first == p;
    }

    int puntuacion(string const& a) const {
        if (alumno.count(a)) {
            return alumno.at(a).second;
        }
        else {
            throw domain_error("El alumno " + a + " no esta matriculado");
        }
    }

    void actualizar(string const& a, int n) {
        if (alumno.count(a)) {
            alumno.at(a).second += n;
        }
        else {
            throw domain_error("El alumno " + a + " no esta matriculado");
        }
    }

    vector<string> examen(string const& p, int n) {
        vector<string> res;
        if (profesores.count(p)) {
            auto alumnosExamen = profesores.find(p)->second;
            for (string alum : alumnosExamen) {
                if (alumno.at(alum).second >= n) {
                    res.push_back(alum);
                }
            }
        }
        return res;
    }

    void aprobar(string a) {
        if (alumno.count(a)) {
            profesores[alumno[a].first].erase(a);
            alumno.erase(a);
        }
        else
        {
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
                std::cin >> A;
                punt = atesc.puntuacion(A);
                std::cout << "Puntuacion de " << A << ": " << punt << '\n';
            }
            else if (orden == "actualizar") {
                std::cin >> A >> punt;
                atesc.actualizar(A, punt);
            }
            else if (orden == "examen") {
                std::cin >> P >> punt;
                vector<string> alum = atesc.examen(P, punt);
                cout << "Alumnos de " << P << " a examen:" << '\n';
                for (string a : alum) {
                    cout << a << '\n';
                }
            }
            else if (orden == "aprobar") {
                std::cin >> A;
                atesc.aprobar(A);
            }
            else
                std::cout << "OPERACION DESCONOCIDA\n";
        }
        catch (std::domain_error e) {
            std::cout << "ERROR" << '\n';
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