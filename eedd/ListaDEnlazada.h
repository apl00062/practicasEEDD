
#ifndef PRACTICACPP_LISTADENLAZADA_H
#define PRACTICACPP_LISTADENLAZADA_H


#include <stdexcept>
#include "Operadores/Iterador.h"

template<typename T>
class ListaDEnlazada {
    Nodo<T> *cabecera, *cola;
    int nElementos;

public:
    /// Constructores: Por defecto y por copia.
    ListaDEnlazada() { cabecera = nullptr; cola = nullptr; nElementos = 0; }
    ListaDEnlazada(const ListaDEnlazada &original);

    /// Destructor
    ~ListaDEnlazada();

    /// Operadores
    ListaDEnlazada &operator=(const ListaDEnlazada &original);
    ListaDEnlazada &operator+(const ListaDEnlazada &original);

    /// Getters y Setters
    Iterador<T> getIterador();
    T& getDatoCabecera();
    T& getDatoCola();
    int getTamLista() const { return this->nElementos; }

    bool comprabarIterador(Iterador<T> &iterador);

    void insertaInicio(T& dato);
    void insertaFinal(T& dato);
    void insertar(Iterador<T> &iterador, T& dato);

    void borraInicio();
    void borraFinal();
    void borrar(Iterador<T> &iterador);

    void concatena(const ListaDEnlazada &original) { this+original; }
    T* buscarDato(T& dato);

};

template<typename T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada &original) {
    if (original.cabecera == nullptr || original.cola == nullptr )
        throw std::invalid_argument("La lista está vacía.");
    if (original.cabecera == original.cola) {
        Nodo<T> *nuevo = new Nodo<T>(original.cabecera->dato, nullptr, nullptr);
        this->cabecera = nuevo;
        this->cola = nuevo;
    }
    else {
        this->cabecera = new Nodo<T>(original.cabecera->dato, nullptr, nullptr);
        Iterador<T> iteradorOriginal = Iterador<T>(original.cabecera);
        Iterador<T> iteradorThis = Iterador<T>(this->cabecera);
        while (iteradorOriginal.haySiguiente()) {
            Nodo<T> *nuevo = new Nodo<T>(iteradorOriginal.nodo->dato, iteradorOriginal.nodo->anterior,
                iteradorOriginal.nodo->siguiente);
            iteradorOriginal.nodo->siguiente = nuevo;
            iteradorOriginal.aSiguiente();
            iteradorThis.aSiguiente();
        }
        this->cola = new Nodo<T>(original.cola->dato, original.cola->anterior, nullptr);
        this->nElementos = original.nElementos;
    }
}

template<typename T>
ListaDEnlazada<T>::~ListaDEnlazada() {
    Nodo<T> *auxiliar = cabecera->siguiente;
    cabecera = nullptr;
    cola = nullptr;
    nElementos = 0;
    while (auxiliar != nullptr) {
        delete auxiliar->anterior;
        auxiliar = auxiliar->siguiente;
    }
    delete auxiliar->anterior;
}

template<typename T>
ListaDEnlazada<T> &ListaDEnlazada<T>::operator=(const ListaDEnlazada &original) {
    if (this == &original)
        return *this;

    // Primero borramos todos los datos del vector actual.
    int elementosTotales = nElementos;
    for (int i = 0; i < elementosTotales; ++i)
        borraInicio();

    if (original.cabecera == nullptr)
        return *this;

    // Luego insertamos todos los elementos
    Iterador<T> iterador = Iterador<T>(original.cola);
    for (int i = 0; i < original.nElementos; ++i) {
        insertaInicio(iterador.dato());
        iterador.aAnterior();
    }
    return *this;
}

template<typename T>
ListaDEnlazada<T> &ListaDEnlazada<T>::operator+(const ListaDEnlazada &original) {
    if (cabecera == nullptr)
        *this = original;

    Iterador<T> iteradorOriginal = Iterador<T>(original.cabecera->siguiente);
    Iterador<T> iteradorThis = Iterador<T>(this->cola);
    while (iteradorOriginal.haySiguiente()) {
        Nodo<T> *nuevo = new Nodo<T>(iteradorOriginal.dato(), iteradorOriginal.nodo->anterior,
            iteradorOriginal.nodo->siguiente);
        iteradorThis.nodo->siguiente = nuevo;
        iteradorOriginal.aSiguiente();
        iteradorThis.aSiguiente();
    }
    Nodo<T> *nuevo = new Nodo<T>(iteradorOriginal.dato(), iteradorOriginal.nodo->anterior, nullptr);
    iteradorThis.nodo->siguiente = nuevo;
    cola = nuevo;
}

template<typename T>
T &ListaDEnlazada<T>::getDatoCabecera() {
    if (cabecera == nullptr)
        throw std::out_of_range("La lista esta vacia.");
    return cabecera->dato;
}

template<typename T>
T &ListaDEnlazada<T>::getDatoCola() {
    if (cola == nullptr)
        throw std::out_of_range("La lista esta vacia");
    return cola->dato;
}

template<typename T>
Iterador<T> ListaDEnlazada<T>::getIterador() {
    if (cabecera == nullptr)
        throw std::out_of_range("La lista esta vacia.");
    return Iterador<T>(cabecera);
}

template<typename T>
bool ListaDEnlazada<T>::comprabarIterador(Iterador<T> &iterador) {
    Nodo<T> *aux = this->cabecera;

    while (aux != nullptr && iterador.nodo != aux) {
        aux = aux->siguiente;
    }
    return aux != nullptr;
}

template<typename T>
void ListaDEnlazada<T>::insertaInicio(T &dato) {
    if (cabecera == nullptr) {
        Nodo<T> *nuevo = new Nodo<T>(dato,nullptr,nullptr);
        cabecera = nuevo;
        cola = nuevo;
    }
    else {
        Nodo<T> *nuevo = new Nodo<T>(dato, nullptr, cabecera);
        cabecera->anterior = nuevo;
        cabecera = nuevo;
    }
    ++nElementos;
}

template<typename T>
void ListaDEnlazada<T>::insertar(Iterador<T> &iterador, T &dato) {
    if (iterador == nullptr)
        throw std::invalid_argument("El iterador no apunta a nada.");
    if (!comprabarIterador(iterador))
        throw std::invalid_argument("El iterador no apunta a ningun elemento de esta lista.");
    if (cabecera == iterador.nodo)
        this->insertaInicio(dato);
    if (cola == iterador.nodo)
        this->insertaFinal(dato);
    else {
        Nodo<T>* nuevo = new Nodo<T>(dato, iterador.nodo->anterior, iterador.nodo);
        iterador.nodo->anterior->siguiente = nuevo;
        iterador.nodo->anterior = nuevo;
    }
    ++nElementos;
}

template<typename T>
void ListaDEnlazada<T>::insertaFinal(T &dato) {
    if (cabecera == nullptr) {
        Nodo<T> *nuevo = new Nodo<T>(dato, nullptr, nullptr);
        cabecera = nuevo;
        cola = nuevo;
    }
    else {
        Nodo<T> *nuevo = new Nodo<T>(dato, cola->anterior, nullptr);
        cola->siguiente = nuevo;
        cola = nuevo;
    }
    ++nElementos;
}

template<typename T>
void ListaDEnlazada<T>::borraInicio() {
    if (cabecera == nullptr)
        throw std::out_of_range("La lista esta vacia.");
    if (cabecera == cola) {
        cola->anterior = nullptr;
        cabecera->siguiente = nullptr;
        delete cola;
        delete cabecera;
    }
    else {
        Nodo<T> *auxiliar = cabecera->siguiente;
        auxiliar->anterior = nullptr;
        delete cabecera;
        cabecera = auxiliar;
    }
    --nElementos;
}

template<typename T>
void ListaDEnlazada<T>::borrar(Iterador<T> &iterador) {
    if (cabecera == nullptr)
        throw std::out_of_range("La lista esta vacia.");
    if (!comprabarIterador(iterador))
        throw std::invalid_argument("El iterador no apunta a ningun elemento de esta lista.");
    if (cabecera == cola)
        borraInicio();
    else {
        iterador.nodo->anterior->siguiente = iterador.nodo->siguiente;
        iterador.nodo->siguiente->anterior = iterador.nodo->anterior;
        delete iterador.nodo;
    }
    --nElementos;
}

template<typename T>
void ListaDEnlazada<T>::borraFinal() {
    if (cabecera == nullptr)
        throw std::out_of_range("La lista esta vacia.");
    if (cabecera == cola) {
        cola->anterior = nullptr;
        cabecera->siguiente = nullptr;
        delete cola;
        delete cabecera;
    }
    else {
        Iterador<T> iterador = new Iterador<T>(cabecera);
        while (iterador.nodo != cola->anterior) {
            iterador.aSiguiente();
        }
        iterador.nodo->siguiente = nullptr;
        delete cola;
        cola = iterador.nodo;
    }
    --nElementos;
}

template<typename T>
T* ListaDEnlazada<T>::buscarDato( T &dato) {
    Iterador<T> iterador(this->cabecera);
    while (iterador.haySiguiente()) {
        if (iterador.dato() == dato)
            return &iterador.dato();
        iterador.aSiguiente();
    }
    return nullptr;
}

#endif //PRACTICACPP_LISTADENLAZADA_H
