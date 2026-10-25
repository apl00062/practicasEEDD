
#ifndef PRACTICACPP_NODO_H
#define PRACTICACPP_NODO_H


template<class T>
class NodoListaDEnlazada {
public:
    T dato;
    NodoListaDEnlazada *anterior, *siguiente;

    /// Constructor: Paremetrizado
    NodoListaDEnlazada(T &dato, NodoListaDEnlazada *anterior, NodoListaDEnlazada *siguiente) {
        this->dato = dato;
        this->anterior = anterior;
        this->siguiente = siguiente;
    }
};

#endif //PRACTICACPP_NODO_H