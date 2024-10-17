// Nombre del alumno: Jorge Torres
// Usuario del Juez: A83


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// función que resuelve el problema


bool esValida(int k, std::vector<int>& sol, std::vector<int>& piezas, std::vector<int>& colocadas, int color) {
    bool valido = true;
    //verdes seguidas
    if (sol[k] == 2 && sol[k - 1] == 2) valido = false;
    //si he puesto verde, tiene que haber mas azules
    if (colocadas[2] > colocadas[0] && color == 2) valido = false;
    //había pieza de ese color para colocar
    if (piezas[color] < 0) valido = false;

    return valido;
}

void resolver(int m, int n, int k, std::vector<int>& sol, std::vector<int>& piezas, std::vector<int>& colocadas, bool &exito) {
   for (int x = 0; x < m; x++) {
       sol[k] = x;
       piezas[x]--;
       colocadas[x]++;
       if (esValida(k, sol, piezas, colocadas, x)) {
           if (k == n - 1 && colocadas[1] > (colocadas[0] + colocadas[2])) {
               for (int i = 0; i < n; i++) {
                   if (sol[i] == 0) {
                       std::cout << "azul ";
                   }
                   else if (sol[i] == 1) {
                       std::cout << "rojo ";
                   }
                   else {
                       std::cout << "verde ";
                   }
                   exito = true;
               }
               std::cout << '\n';
           }
           else {
               if (k < n - 1) resolver(m, n, k + 1, sol, piezas, colocadas, exito);
           }
       }
       piezas[x]++;
       colocadas[x]--;
   }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int m = 3, n;
    bool exito = false;
    std::vector<int> piezas(m);
    std::cin >> n >> piezas[0] >> piezas[1] >> piezas[2];
    if (n == 0)
        return false;
    std::vector<int> colocadas(m, 0);
    std::vector<int> v(n, -1);

    v[0] = 1;
    colocadas[1]++;
    piezas[1]--;

    resolver(m, n, 1, v, piezas, colocadas, exito);
    if (!exito) std::cout << "SIN SOLUCION\n";

    std::cout << '\n';
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
