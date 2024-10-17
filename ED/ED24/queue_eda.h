
//
//  queue_eda.h
//
//  Implementación del TAD cola con dos pilas
//
//  Estructuras de Datos y Algoritmos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2016-2018 Isabel
//

#ifndef queue_eda_h
#define queue_eda_h

#include <stdexcept>  // std::domain_error
#include <stack> 

template <class T>
class queue {
protected:
    std::stack<T> pila1;
    std::stack<T> pila2;


public:

    // constructor: cola vacía
    queue() {}


    // añadir un elemento al final de la cola
    void push(T const& elem) {
        pila1.push(elem);
    }

    // consultar el primero de la cola
    T const& front() {
        if (pila2.empty()) {
            while (!pila1.empty()) {
                pila2.push(pila1.top());
                pila1.pop();
            }
        }

        return pila2.top();
    }

    // eliminar el primero de la cola
    void pop() {
        if (pila2.empty()) {
            while (!pila1.empty()) {
                pila2.push(pila1.top());
                pila1.pop();
            }
        }
        pila2.pop();
    }

    // consultar si la cola está vacía
    bool empty() const {
        
        return (pila1.empty() && pila2.empty());
    }

    // consultar el tamaño de la cola
    size_t size() const {
        return pila1.size() + pila2.size();
    }


};

#endif // queue_eda_h

