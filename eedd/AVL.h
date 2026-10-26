//
// Created by Ángel Padilla Luzón on 25/10/2026.
//

#ifndef PRACTICACPP_AVL_H
#define PRACTICACPP_AVL_H

#include "Operadores/NodoAVL.h"
#include "VDinamico.h"

template<typename T>
class AVL {
    NodoAVL<T> *raiz;
    unsigned int nElementos;

    bool inserta(NodoAVL<T>* &nodo, T& dato);
    void rotacionDerecha(NodoAVL<T>* &nodo);
    void rotacionIzquierda(NodoAVL<T>* &nodo);

    void inordenAux(NodoAVL<T>* nodo, VDinamico<T*> &vector);
    VDinamico<T*> inorden(NodoAVL<T>* nodo);
    void preordenAux(NodoAVL<T>* nodo, VDinamico<NodoAVL<T>*> &vector);
    VDinamico<NodoAVL<T> *> preorden(NodoAVL<T>* nodo);
    void postordenAux(NodoAVL<T>* nodo, VDinamico<NodoAVL<T>*> &vector);
    VDinamico<NodoAVL<T> *> postorden(NodoAVL<T>* nodo);

    T* busquedaRecursiva(T &dato, const NodoAVL<T> *nodo);
    T* busquedaIterativa(T &dato, NodoAVL<T> *nodo);


public:
    /// Constructores: Por defecto y por copia
    AVL() : raiz(nullptr), nElementos(0) {}
    AVL(const AVL<T> &original);

    /// Destructor
    ~AVL();

    /// Getters
    unsigned int getNumElementos() const { return this->nElementos; }
    unsigned int getAltura() const { return this->raiz->altura; }

    /// Operadores
    AVL &operator=(const AVL &original);

    /// Recorridos: Inorden, preorden y postorden.
    VDinamico<T*> inorden() { return inorden(raiz); }
    VDinamico<NodoAVL<T> *> preorden() { return preorden(raiz); }
    VDinamico<NodoAVL<T> *> postorden() { return postorden(raiz); }

    bool inserta(T& dato) {return inserta(raiz, dato); }

    T* busquedaRecursiva(T &dato) { return busquedaRecursiva(dato,raiz); }
    T* busquedaIterativa(T &dato) { return busquedaIterativa(dato,raiz); };

};


template <typename T>
AVL<T>::~AVL()
{
    VDinamico<NodoAVL<T> *> vector;
    vector = postorden();
    for (int i = 0; i < vector.getTamanioLogico(); ++i)
    {
        delete vector[i];
    }
}

template <typename T>
AVL<T>::AVL(const AVL& original)
{
    VDinamico<NodoAVL<T> *> vector;
    vector = original.preorden();

    for (int i = 0; i < vector.getTamanioLogico(); ++i)
        bool aux = this->inserta(vector[i]->dato);

    this->nElementos = original.nElementos;
}

template <typename T>
AVL<T>& AVL<T>::operator=(const AVL<T>& original)
{
    if (this == &original)
        return *this;

    VDinamico<NodoAVL<T> *> vectorOriginal;
    vectorOriginal = original.preorden();
    VDinamico<NodoAVL<T> *> vector;
    vector = this->preorden();

    for (int i = 0; i < vector.getTamanioLogico(); ++i)
        delete vector[i];

    for (int i = 0; i < vectorOriginal.getTamanioLogico(); ++i)
        bool aux = this->inserta(vectorOriginal[i]->dato);

    this->nElementos = original.nElementos;

    return *this;
}

template<typename T>
void AVL<T>::inordenAux(NodoAVL<T> *nodo, VDinamico<T*> &vector){
    if (nodo)
    {
        inordenAux(nodo->izquierda, vector);
        vector.insertar(&nodo->dato);
        inordenAux(nodo->derecha, vector);
    }
}

template <typename T>
VDinamico<T*> AVL<T>::inorden(NodoAVL<T>* nodo)
{
    VDinamico<T*> vector;
    inordenAux(nodo, vector);
    return vector;
}

template <typename T>
void AVL<T>::preordenAux(NodoAVL<T>* nodo, VDinamico<NodoAVL<T>*> &vector)
{
    if (nodo)
    {
        vector.insertar(nodo);
        preordenAux(nodo->izquierda, vector);
        preordenAux(nodo->derecha, vector);
    }
}

template <typename T>
VDinamico<NodoAVL<T>*> AVL<T>::preorden(NodoAVL<T>* nodo)
{
    VDinamico<NodoAVL<T>*> vector;
    preorden(nodo, vector);
    return vector;
}

template <typename T>
void AVL<T>::postordenAux(NodoAVL<T>* nodo, VDinamico<NodoAVL<T>*> &vector)
{
    if (nodo) {
        postordenAux(nodo->izquierda, vector);
        postordenAux(nodo->derecha, vector);
        vector.insertar(nodo);
    }
}

template <typename T>
VDinamico<NodoAVL<T>*> AVL<T>::postorden(NodoAVL<T>* nodo)
{
    VDinamico<NodoAVL<T>*> vector;
    postordenAux(nodo, vector);
    return vector;
}

template<typename T>
bool AVL<T>::inserta(NodoAVL<T> *&nodo, T &dato) {
    bool insertado = false;
    if (!nodo) {
        NodoAVL<T> *nuevoNodo = new NodoAVL<T>(dato);
        nodo = nuevoNodo;
        return true;
    }

    if (nodo->dato == dato)
        return false;

    if (dato < nodo->dato) {
        insertado = inserta(nodo->izquierda, dato);
    }
    if (dato > nodo->dato) {
        insertado = inserta(nodo->derecha, dato);
    }

    if (!insertado)
        return insertado;

    if (insertado) {
        const int izq = nodo->izquierda == nullptr ? -1 : nodo->izquierda->altura;
        const int dcha = nodo->derecha == nullptr ? -1 : nodo->derecha->altura;
        nodo->altura = 1 + std::max(izq,dcha);

        nodo->balanceado = izq - dcha;

        if (nodo->balanceado == 2) {
            if (nodo->izquierda->balanceado >= 0) {
                rotacionDerecha(nodo);
            } else {
                rotacionIzquierda(nodo->izquierda);
                rotacionDerecha(nodo);
            }
        } else if (nodo->balanceado == -2) {
            if (nodo->derecha->balanceado <= 0) {
                rotacionIzquierda(nodo);
            } else {
                rotacionDerecha(nodo->derecha);
                rotacionIzquierda(nodo);
            }
        }
        ++nElementos;
    }
    return insertado;
}

template<typename T>
void AVL<T>::rotacionIzquierda(NodoAVL<T> *&nodo) {
    NodoAVL<T> *auxiliar = nodo;
    NodoAVL<T> *auxiliar2 = auxiliar->derecha;
    nodo = auxiliar2;

    auxiliar->derecha = auxiliar2->izquierda;
    auxiliar2->izquierda = auxiliar;

    ++auxiliar->balanceado;

    if (auxiliar2->balanceado < 0)
        auxiliar->balanceado += -auxiliar2->balanceado;

    ++auxiliar2->balanceado;

    if (auxiliar->balanceado > 0)
        auxiliar2->balanceado += auxiliar->balanceado;

    const int izq = nodo->izquierda == nullptr ? -1 : nodo->izquierda->altura;
    const int dcha = nodo->derecha == nullptr ? -1 : nodo->derecha->altura;
    nodo->altura = 1 + std::max(izq,dcha);
}

template<typename T>
void AVL<T>::rotacionDerecha(NodoAVL<T> *&nodo) {
    NodoAVL<T> *auxiliar = nodo;
    NodoAVL<T> *auxiliar2 = auxiliar->izquierda;
    nodo = auxiliar2;

    auxiliar->izquierda = auxiliar2->derecha;
    auxiliar2->derecha = auxiliar;

    --auxiliar->balanceado;

    if (auxiliar2->balanceado > 0)
        auxiliar->balanceado -= auxiliar2->balanceado;

    --auxiliar2->balanceado;

    if (auxiliar->balanceado < 0)
        auxiliar2->balanceado += auxiliar->balanceado;

    const int izq = nodo->izquierda == nullptr ? -1 : nodo->izquierda->altura;
    const int dcha = nodo->derecha == nullptr ? -1 : nodo->derecha->altura;
    nodo->altura = 1 + std::max(izq,dcha);
}

template <typename T>
T* AVL<T>::busquedaIterativa(T& dato, NodoAVL<T> *nodo)
{
    while (nodo)
    {
        if (nodo->dato == dato)
            return &nodo->dato;
        if (dato < nodo->dato)
            nodo = nodo->izquierda;
        else
            nodo = nodo->derecha;
    }
    return nullptr;
}

template <typename T>
T* AVL<T>::busquedaRecursiva(T& dato, const NodoAVL<T> *nodo)
{
    if (dato == nodo->dato)
        return &nodo->dato;
    if (dato < nodo->dato)
        return busquedaIterativa(dato, nodo->izquierda);
    if (nodo->dato < dato)
        return busquedaIterativa(dato, nodo->derecha);

    return nullptr;

}

#endif //PRACTICACPP_AVL_H
