// Nombre del alumno: Jorge Torres

#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
using namespace std;

struct Tarea{
    int ini, fin, min = 0;

    bool operator>(const Tarea& other) const {
        return ini > other.ini;
    }
};

bool multitarea(priority_queue<Tarea, vector<Tarea>, greater<Tarea>> &tareas, int minutos) {
    bool conflicto = false;
    int tiempo = 0;

    while (!tareas.empty() && tiempo < minutos) {
        Tarea tarea = tareas.top();
        tareas.pop();

        if (tarea.ini <= tiempo) {
            conflicto = true;
            break;
        }

        tiempo = tarea.fin - 1;
        if (tarea.min > 0 && tarea.ini + tarea.min <= minutos) {
            tareas.push({ tarea.ini + tarea.min, tarea.fin + tarea.min, tarea.min });
        }
    }
    return conflicto;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int unicas, periodicas, minutos;
    Tarea tarea;

    cin >> unicas >> periodicas >> minutos;
    if (!std::cin)
        return false;

    priority_queue<Tarea, vector<Tarea>, greater<Tarea>> tareas;

    for (int i = 0; i < unicas; i++) {
        cin >> tarea.ini >> tarea.fin;
        tareas.push(tarea);
    }
    for (int i = 0; i < periodicas; i++) {
        cin >> tarea.ini >> tarea.fin >> tarea.min;
        tareas.push(tarea);
    }

    // escribir sol

    bool sol = multitarea(tareas, minutos);
    if (sol) cout << "SI\n";
    else cout << "NO\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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