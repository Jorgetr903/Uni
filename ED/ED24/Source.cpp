// Programa para probar la implementación de una cola
// Jorge Torres
// A66

#include <iostream> 
#include <fstream> 
#include "queue_eda.h"
#include <string>

bool resuelveCaso() {
    std::string str;
    getline(std::cin, str);
    if (str == ".") return false;
    // lee los datos de entrada en la cola
    queue<char> cola;
    for (int i = 0; i < str.length(); ++i) {
        cola.push(str[i]);
    }
    // Rota los datos de la cola
    for (int i = 0; i < cola.size(); ++i) {
        cola.push(cola.front());
        cola.pop();
    }
    // Duplica los elementos de la cola
    int numElem = (int)cola.size();
    for (int i = 0; i < numElem; ++i) {
        cola.push(cola.front());
        cola.push(cola.front());
        cola.pop();
    }
    // Muestra los elementos de la cola y la deshace
    numElem = (int)cola.size();
    for (int i = 0; i < numElem; i += 2) {
        std::cout << cola.front();
        cola.pop(); cola.pop();
    }
    if (!cola.empty()) std::cout << "ERROR\n";
    std::cout << '\n';
    return true;
}


int main() {

#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
