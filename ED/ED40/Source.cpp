// Nombre del alumno: Jorge Torres
// Usuario del Juez: A66

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

bintree<int> reconstruir(vector<int>& preorder, vector<int>& inorder, int preStart, int preEnd, int inStart, int inEnd) {
    if (preStart > preEnd || inStart > inEnd) {
        return bintree<int>();
    }

    int rootVal = preorder[preStart];

    int k = 0;
    for (int i = inStart; i <= inEnd; i++) {
        if (inorder[i] == rootVal) {
            k = i;
            break;
        }
    }
    bintree <int> arbIz = reconstruir(preorder, inorder, preStart + 1, preStart + k - inStart, inStart, k - 1);
    bintree <int> arbDr = reconstruir(preorder, inorder, preStart + k - inStart + 1, preEnd, k + 1, inEnd);

    bintree <int> root = bintree<int>(arbIz, rootVal, arbDr);

    return root;
   

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    std::string line;
    int num;

    vector<int> preorden;
    vector<int> inorden;
    if (!std::cin)
        return false;
    std::getline(cin, line);

    std::istringstream linea1(line);
    while (linea1 >> num) {
        preorden.push_back(num);
    }
    std::getline(cin, line);
    std::istringstream linea2(line);
    while (linea2 >> num) {
        inorden.push_back(num);
    }

    bintree<int> arbol = reconstruir(preorden, inorden, 0, preorden.size() - 1, 0, inorden.size() - 1);
    // escribir sol
    vector <int> post = arbol.postorder();

    for (int i = 0; i < post.size(); i++) {
        cout << post[i] << " ";
    }
    cout << '\n';

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
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