// Nombre del alumno .....
// Usuario del Juez ......

#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

// función que resuelve el problema
vector<int> resolver(priority_queue<int>& pilas1v, priority_queue<int>& pilas9v, int const& numDrones)
{

    vector<int> sol;
    int drones = numDrones;

    if (pilas1v.empty() || pilas9v.empty()) sol.push_back(0);

    while (!pilas1v.empty() && !pilas9v.empty())
    {
        vector<int> pilas1, pilas9;
        int total = 0;
        for (int i = 0; i < numDrones; i++)
        {
            if (!pilas1v.empty() && !pilas9v.empty()) {
                int pila9 = pilas9v.top();
                int pila1 = pilas1v.top();

                int minimo = min(pila1, pila9);

                pilas1v.pop();
                pilas9v.pop();

                if (pila1 < pila9)
                {
                    pilas9.push_back(pila9 - pila1);
                    total += pila1;
                }
                else if (pila1 == pila9)
                {
                    total += pila1;
                }
                else
                {
                    pilas1.push_back(pila1 - pila9);
                    total += pila9;
                }
            }
            
        }
        for (int i = 0; i < pilas1.size(); i++) {
            pilas1v.push(pilas1[i]);
        }
        for (int i = 0; i < pilas9.size(); i++) {
            pilas9v.push(pilas9[i]);
        }
        pilas1.clear();
        pilas9.clear();
        sol.push_back(total);
    }
    return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
    // leer los datos de la entrada
    int numDrones, numPilas9V, numPilas1V;
    cin >> numDrones >> numPilas9V >> numPilas1V;
    if (!std::cin)
        return false;
    priority_queue<int> pilas9v;
    priority_queue<int> pilas1v;
    int elem;
    for (int i = 0; i < numPilas9V; i++)
    {
        cin >> elem;
        pilas9v.push(elem);
    }

    for (int i = 0; i < numPilas1V; i++)
    {
        cin >> elem;
        pilas1v.push(elem);
    }

    vector<int> sol = resolver(pilas1v, pilas9v, numDrones);

    for (int a : sol) {
        cout << a << " ";
    }
    cout << endl;
    return true;
}

int main()
{
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save old buf and redirect std::cin to casos.txt
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