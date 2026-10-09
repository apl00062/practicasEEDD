
#ifndef PRACTICACPP_NODO_H
#define PRACTICACPP_NODO_H



template<class T>
class Nodo {
public:
    T dato;
    Nodo *anterior, *siguiente;

    /// Constructor: Paremetrizado
    Nodo(T &dato, Nodo *anterior, Nodo *siguiente) {
        this->dato = dato;
        this->anterior = anterior;
        this->siguiente = siguiente;
    }
};

#endif //PRACTICACPP_NODO_H