// Nombre del alumno: Jorge Torres
// Usuario del juez: A66

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <cctype>
#include <cassert>
#include <stdexcept>
#include <iomanip>

//
//  linked_list_ed.h
//
//  Implementación del TAD linked_list con nodos enlazados
//  y punteros al primer y  último nodo
//
//  Estructuras de Datos. Grupos A y C. Curso 2021/22
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2021 Isabel Pita 
//  Adaptada de la implementación del queue realizada por Alberto Verdejo

#ifndef linked_list_ed_h
#define linked_list_ed_h

#include <stdexcept>  // std::domain_error

template <typename T>
class linked_list_ed {
protected:

    /*
     Nodo que almacena internamente el elemento (de tipo T),
     y un puntero al nodo siguiente, que puede ser nullptr si
     el nodo es el último de la lista enlazada.
     */
    struct Nodo {
        Nodo() : sig(nullptr) {}
        Nodo(T const& elem, Nodo* si = nullptr) : elem(elem), sig(si) {}
        T elem;
        Nodo* sig;
    };

    // punteros al primer y último elemento
    Nodo* prim;
    Nodo* ult;

public:

    // constructor: lista enlazada vacia 
    linked_list_ed() : prim(nullptr), ult(nullptr) {}

    // destructor
    ~linked_list_ed() {
        libera();
    }

    // constructor por copia
    linked_list_ed(linked_list_ed<T> const& other) {
        copia(other);
    }

    // operador de asignación
    linked_list_ed<T>& operator=(linked_list_ed<T> const& other) {
        if (this != &other) {
            libera();
            copia(other);
        }
        return *this;
    }

    // añadir un elemento al final de la lista enlazada
    void push_back(T const& elem) {
        Nodo* nuevo = new Nodo(elem);

        if (ult != nullptr)
            ult->sig = nuevo;
        ult = nuevo;
        if (prim == nullptr) // la lista estaba vacía
            prim = nuevo;
    }

    // añadir un elemento al principio de la lista enlazada
    void push_front(T const& elem) {
        Nodo* nuevo = new Nodo(elem, prim);
        prim = nuevo;
        if (ult == nullptr) // la lista estaba vacía
            ult = nuevo;
    }


    // eliminar el primero de la lista enlazada
    void pop_front() {
        if (empty())
            throw std::domain_error("eliminando de una lista enlazada vacia");
        Nodo* a_borrar = prim;
        prim = prim->sig;
        if (prim == nullptr) // la lista enlazada se ha quedado vacía
            ult = nullptr;
        delete a_borrar;
    }

    // consultar si la lista enlazada está vacía
    bool empty() const {
        return this->prim == nullptr;
    }


protected:

    void libera() {
        while (prim != nullptr) {
            Nodo* a_borrar = prim;
            prim = prim->sig;
            delete a_borrar;
        }
        ult = nullptr;
    }

    // this está sin inicializar
    void copia(linked_list_ed const& other) {
        if (other.empty()) {
            prim = ult = nullptr;
        }
        else {
            Nodo* act = other.prim; // recorre la cola original
            ult = new Nodo(act->elem); // último nodo copiado
            prim = ult;
            while (act->sig != nullptr) {
                act = act->sig;
                ult->sig = new Nodo(act->elem);
                ult = ult->sig;
            }
        }
    }
};

#endif // linked_list_ed_h



template <class T>
class linked_list_ed_plus : public linked_list_ed<T> {
    using Nodo = typename linked_list_ed<T>::Nodo;
public:
    void print(std::ostream& o = std::cout) const {
        if (!this->empty()) {// la lista no está vacía
            Nodo* aux = this->prim;
            o << aux->elem;
            aux = aux->sig;
            while (aux != nullptr) {
                o << ' ' << aux->elem;
                aux = aux->sig;
            }
        }
        o << '\n';
    }

    void rotar() {
        if (!this->empty() && this->prim->sig != nullptr) {
            // Dos o mas elementos
            Nodo* a_mover = this->prim;
            // Desengancha el primer nodo
            this->prim = a_mover->sig;
            a_mover->sig = nullptr;
            // Lo engancha al final de la lista
            this->ult->sig = a_mover;
            // repite el proceso para todos los demás nodos de la lista
            Nodo* act = a_mover;
            while (this->ult->sig != nullptr) {
                // Desengancha el primer nodo
                a_mover = this->prim;
                this->prim = a_mover->sig;
                // Lo engancha al final de la lista
                a_mover->sig = nullptr;
                act->sig = a_mover;
                act = act->sig;
            }
            this->ult = act;
        }
    }

    // Separar los elementos positivos y negativos y eliminar los ceros
    // 
    void separar(linked_list_ed_plus& l) {

        Nodo* aux = this->prim;
        Nodo* otro = l.prim;
        Nodo* a_mover;
        while (aux != nullptr && aux->elem <= 0) {
            if (aux->elem < 0) {
                a_mover = aux;
                aux = aux->sig;
                if (l.prim == nullptr) {
                    l.prim = a_mover;
                    otro = l.prim;
                }
                else {
                    otro->sig = a_mover;
                    otro = otro->sig;
                }
                a_mover->sig = nullptr;
                this->prim = aux;
            }
            else {
                a_mover = aux;
                aux = aux->sig;
                this->prim = aux;
                delete a_mover;
            }
        }

        if (aux != nullptr) {

            while (aux->sig != nullptr) {
                if (aux->sig->elem > 0) {
                    aux = aux->sig;
                }
                else {
                    if (aux->sig->elem < 0) {
                        a_mover = aux->sig;
                        aux->sig = aux->sig->sig;
                        if (l.prim == nullptr) {
                            l.prim = a_mover;
                            otro = l.prim;
                        }
                        else {
                            otro->sig = a_mover;
                            otro = otro->sig;
                        }
                        a_mover->sig = nullptr;
                    }
                    else {
                        a_mover = aux->sig;
                        aux->sig = aux->sig->sig;
                        delete a_mover;
                    }
                }
            }
        }
        this->ult = aux;
        l.ult = otro;
    }
};