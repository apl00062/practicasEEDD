
#ifndef PRACTICACPP_LISTADENLAZADA_H
#define PRACTICACPP_LISTADENLAZADA_H


#include <stdexcept>
#include <type_traits>
#include "Operadores/Iterador.h"

template<typename T>
class ListaDEnlazada {
    NodoListaDEnlazada<T> *cabecera, *cola;
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
    unsigned int getTamLista() const { return this->nElementos; }

    /**
     * Metodo que comprueba que el iterador apunta a un elemento de esta lista.
     *
     * \param iterador
     *      Iterador que queremos comprobar.
    */
    bool comprabarIterador(Iterador<T> &iterador);

    /**
     * Metodo que crea e inserta un nuevo nodo en el incio de la lista, maneja todas las posibles casuisticas.
     * Aumenta el tamaño de la lista +1.
     *
     * \param dato
     *      Dato con el que crearemos el nodo.
    */
    T* insertaInicio(T& dato);

    /**
     * Metodo que crea e inserta un nuevo nodo en el final de la lista, maneja todas las posibles casuisticas.
     * Aumenta el tamaño de la lista +1.
     *
     * \param dato
     *      Dato con el que crearemos el nodo.
    */
    T* insertaFinal(T &dato);

    /**
     * Metodo que crea e inserta un nuevo nodo en el lugar donde el iterador apunte. Este metodo, primero llama a
     * comprobarIterador(). Si el iterador apunta a la cabecera llama a insertarInicio() y si apunta a la cola
     * llama a insertarFinal(). Aumenta el tamaño de la lista +1.
     *
     * \param iterador
     *      Iterador que apunta a la posicion en la que queremos insertar el nodo.
     * \param dato
     *      Dato con el que crearemos el nodo.
     *
     * \exception
     *      Salta una excepcion, si el metodo comprabarIterador() devuelve null.
    */
    T* insertar(Iterador<T> &iterador, T& dato);

    /**
     * Metodo que borra el nodo al que apunta la cabecera, asignando la cabecera al nodo siguiente a la cabecera.
     * Disminuye el tamaño de la lista en -1.
     *
     * \exception
     *      Salta una excepcion si la lista esta vacia.
    */
    void borraInicio();

    /**
     * Metodo que borra el nodo al que apunta la cola, asignando la cola al nodo anterior a la cola.
     * Disminuye el tamño de la lista en -1.
     *
     * \exception
     *      Salta una excepcion si la lista esta vacia.
    */
    void borraFinal();

    /**
     * Metodo que borra el nodo al que apunta al iterador. Primero llama a comprabarIterador(). Si el iterador apunta a
     * la cabecera, llama a borrarInicio(), si apunta a la cola llama a borraFinal(). Disminuye el tamaño en -1.
     *
     * \param iterador
     *      Iterador que apunta a la posicion que queremos borrar.
     *
     * \exception
     *      Salta una excepcion si comprobarIterador() devuelve null.
    */
    void borrar(Iterador<T> &iterador);

    void concatena(const ListaDEnlazada &original) { return this+original; }
    T* buscarDato(T& dato);

};

template<typename T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada &original) {
    if (original.cabecera == nullptr || original.cola == nullptr )
        throw std::invalid_argument("La lista está vacía.");
    if (original.cabecera == original.cola) {
        NodoListaDEnlazada<T> *nuevo = new NodoListaDEnlazada<T>(original.cabecera->dato, nullptr, nullptr);
        this->cabecera = nuevo;
        this->cola = nuevo;
    }
    else {
        this->cabecera = new NodoListaDEnlazada<T>(original.cabecera->dato, nullptr, nullptr);
        Iterador<T> iteradorOriginal = Iterador<T>(original.cabecera);
        Iterador<T> iteradorThis = Iterador<T>(this->cabecera);
        while (iteradorOriginal.haySiguiente()) {
            NodoListaDEnlazada<T> *nuevo = new NodoListaDEnlazada<T>(iteradorOriginal.nodo->dato, iteradorOriginal.nodo->anterior,
                iteradorOriginal.nodo->siguiente);
            iteradorThis.nodo->siguiente = nuevo;
            iteradorOriginal.aSiguiente();
            iteradorThis.aSiguiente();
        }
        this->cola = new NodoListaDEnlazada<T>(original.cola->dato, original.cola->anterior, nullptr);
        this->nElementos = original.nElementos;
    }
}

template<typename T>
ListaDEnlazada<T>::~ListaDEnlazada() {
    while (cabecera != nullptr)
        borraInicio();
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
        NodoListaDEnlazada<T> *nuevo = new NodoListaDEnlazada<T>(iteradorOriginal.dato(), iteradorOriginal.nodo->anterior,
            iteradorOriginal.nodo->siguiente);
        iteradorThis.nodo->siguiente = nuevo;
        iteradorOriginal.aSiguiente();
        iteradorThis.aSiguiente();
    }
    NodoListaDEnlazada<T> *nuevo = new NodoListaDEnlazada<T>(iteradorOriginal.dato(), iteradorOriginal.nodo->anterior, nullptr);
    iteradorThis.nodo->siguiente = nuevo;
    cola = nuevo;

    return this;
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
    NodoListaDEnlazada<T> *aux = this->cabecera;

    while (aux != nullptr && iterador.nodo != aux) {
        aux = aux->siguiente;
    }
    return aux != nullptr;
}

template<typename T>
T* ListaDEnlazada<T>::insertaInicio(T &dato) {
    if (cabecera == nullptr) {
        NodoListaDEnlazada<T> *nuevo = new NodoListaDEnlazada<T>(dato,nullptr,nullptr);
        cabecera = nuevo;
        cola = nuevo;
    }
    else if (cabecera == cola) {
        NodoListaDEnlazada<T> *nuevo = new NodoListaDEnlazada<T>(dato, nullptr, cola);
        cola->anterior = nuevo;
        cabecera = nuevo;
    }
    else {
        NodoListaDEnlazada<T> *nuevo = new NodoListaDEnlazada<T>(dato, nullptr, cabecera);
        cabecera->anterior = nuevo;
        cabecera = nuevo;
    }
    ++nElementos;
    return &dato;
}

template<typename T>
T* ListaDEnlazada<T>::insertar(Iterador<T> &iterador, T &dato) {
    if (!comprabarIterador(iterador))
        throw std::invalid_argument("El iterador no apunta a ningun elemento de esta lista.");
    if (cabecera == iterador.nodo)
        this->insertaInicio(dato);
    else if (cola == iterador.nodo)
        this->insertaFinal(dato);
    else if (cola == cabecera)
        this->insertaInicio(dato);
    else {
        NodoListaDEnlazada<T>* nuevo = new NodoListaDEnlazada<T>(dato, iterador.nodo->anterior, iterador.nodo);
        iterador.nodo->anterior->siguiente = nuevo;
        iterador.nodo->anterior = nuevo;
        ++nElementos;
        return &dato;
    }
}

template<typename T>
T* ListaDEnlazada<T>::insertaFinal(T &dato) {
    if (cabecera == nullptr) {
        NodoListaDEnlazada<T> *nuevo = new NodoListaDEnlazada<T>(dato, nullptr, nullptr);
        cabecera = nuevo;
        cola = nuevo;
    }
    else if (cabecera == cola) {
        NodoListaDEnlazada<T> *nuevo = new NodoListaDEnlazada<T>(dato, cabecera, nullptr);
        cabecera->siguiente = nuevo;
        cola = nuevo;
    }
    else {
        NodoListaDEnlazada<T> *nuevo = new NodoListaDEnlazada<T>(dato, cola, nullptr);
        cola->siguiente = nuevo;
        cola = nuevo;
    }
    ++nElementos;
    return &dato;
}

template<typename T>
void ListaDEnlazada<T>::borraInicio() {
    if (cabecera == nullptr)
        throw std::out_of_range("La lista esta vacia.");
    if (cabecera == cola) {

        delete cabecera;
        cabecera = nullptr;
        cola = nullptr;
    }
    else {
        NodoListaDEnlazada<T> *auxiliar = cabecera->siguiente;
        auxiliar->anterior = nullptr;

        delete cabecera;
        cabecera = auxiliar;
        auxiliar = nullptr;
    }
    --nElementos;
}

template<typename T>
void ListaDEnlazada<T>::borrar(Iterador<T> &iterador) {
    if (cabecera == nullptr)
        throw std::out_of_range("La lista esta vacia.");
    if (!comprabarIterador(iterador))
        throw std::invalid_argument("El iterador no apunta a ningun elemento de esta lista.");

    NodoListaDEnlazada<T> *siguienteIterador = iterador.nodo->siguiente;
    if (cabecera == cola)
        borraInicio();
    else if (iterador.nodo == cabecera)
        borraInicio();
    else if (iterador.nodo == cola)
        borraFinal();
    else {
        NodoListaDEnlazada<T> *aBorrar = iterador.nodo;
        aBorrar->anterior->siguiente = aBorrar->siguiente;
        aBorrar->siguiente->anterior = aBorrar->anterior;

        delete aBorrar;

        --nElementos;
    }
    iterador.nodo = siguienteIterador;
}

template<typename T>
void ListaDEnlazada<T>::borraFinal() {
    if (cabecera == nullptr)
        throw std::out_of_range("La lista esta vacia.");
    if (cabecera == cola) {

        delete cola;
        cabecera = nullptr;
        cola = nullptr;
    }
    else {
        NodoListaDEnlazada<T> *auxiliar = cola->anterior;
        auxiliar->siguiente = nullptr;

        delete cola;
        cola = auxiliar;
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
