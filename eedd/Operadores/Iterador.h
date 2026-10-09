#ifndef PRACTICACPP_ITERADOR_H
#define PRACTICACPP_ITERADOR_H

#include "Nodo.h"
#include "../ListaDEnlazada.h"

template<class T>
class Iterador {
    Nodo<T> *nodo;
    friend class ListaDEnlazada<T>;

public:
    /// Constructores: Parametrizado
    Iterador(Nodo<T> *nodo) {this->nodo = nodo;}

    bool hayAnterior() { return nodo->anterior != 0; }
    bool haySiguiente() { return nodo->siguiente != 0; }
    void nodoIgualAnterior() { nodo = nodo->anterior; }
    void nodoIgualSiguiente() { nodo = nodo->siguiente; }
    T &dato() { return nodo->dato; }
};


#endif //PRACTICACPP_ITERADOR_H