// Nombre del alumno
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int eventos, valor;
    
    cin >> eventos;
    if (!std::cin)
        return false;

    priority_queue<int> medianaYmenores;
    priority_queue<int, vector<int>, greater<int>> mayores;

    for (int i = 0; i < eventos; i++) {
        cin >> valor;
        if (valor == 0) {
            if (!medianaYmenores.empty()) {
                cout << medianaYmenores.top() << " ";
                medianaYmenores.pop();
                if (medianaYmenores.size() < mayores.size()) {
                    medianaYmenores.push(mayores.top());
                    mayores.pop();
                }
            }
            else {
                cout << "ECSA ";
            }
        }
        else if (medianaYmenores.empty()) {
            medianaYmenores.push(valor);
        }
        else {
            if (mayores.empty()) {
                if (valor > medianaYmenores.top()) {
                    mayores.push(valor);
                }
                else {
                    mayores.push(medianaYmenores.top());
                    medianaYmenores.pop();
                    medianaYmenores.push(valor);
                }
            }
            else if (medianaYmenores.size() == mayores.size()) {
                if (medianaYmenores.top() < valor && valor < mayores.top() || valor < medianaYmenores.top()) {
                    medianaYmenores.push(valor);
                }
                else {
                    mayores.push(valor);
                    medianaYmenores.push(mayores.top());
                    mayores.pop();
                }
            }
            else {
                if (medianaYmenores.top() < valor && valor < mayores.top() || mayores.top() < valor) {
                    mayores.push(valor);
                }
                else {
                    medianaYmenores.push(valor);
                    mayores.push(medianaYmenores.top());
                    medianaYmenores.pop();
                }
            }
        }
    }
    // escribir sol
    cout << '\n';

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