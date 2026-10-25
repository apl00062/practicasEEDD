#ifndef PRACTICACPP_ITERADOR_H
#define PRACTICACPP_ITERADOR_H

#include "NodoListaDEnlazada.h"

template<class T>
class ListaDEnlazada;

template<class T>
class Iterador {
    NodoListaDEnlazada<T> *nodo;
    friend class ListaDEnlazada<T>;

public:
    /// Constructores: Parametrizado
    Iterador(NodoListaDEnlazada<T> *nodo) {this->nodo = nodo;}

    bool hayAnterior() { return nodo->anterior != nullptr; }
    bool haySiguiente() { return nodo->siguiente != nullptr; }
    void aAnterior();
    void aSiguiente();
    T &dato() { return nodo->dato; }

};

template<class T>
void Iterador<T>::aAnterior() {
    if (nodo != nullptr)
        nodo = nodo->anterior;
}

template<class T>
void Iterador<T>::aSiguiente() {
    if (nodo != nullptr)
        nodo = nodo->siguiente;
}


#endif //PRACTICACPP_ITERADOR_H