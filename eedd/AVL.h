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
    unsigned int altura;
    unsigned int nElementos;

    bool inserta(NodoAVL<T>* &nodo, T& dato);
    void rotacionDerecha(NodoAVL<T>* &nodo);
    void rotacionIzquierda(NodoAVL<T>* &nodo);

    VDinamico<NodoAVL<T>*> inorden(NodoAVL<T>* &nodo);
    VDinamico<NodoAVL<T>*> preorden(NodoAVL<T>* &nodo);
    VDinamico<NodoAVL<T>*> postorden(NodoAVL<T>* &nodo);

public:
    AVL() : raiz(nullptr), altura(0), nElementos(0) {}
    bool inserta(T& dato) {return inserta(raiz, dato); }



};

template<typename T>
bool AVL<T>::inserta(NodoAVL<T> *&nodo, T &dato) {
    if (!nodo) {
        nodo = new NodoAVL<T>(dato);
        return true;
    }
    if (dato < nodo->dato)
        return inserta(nodo->izquierda, dato);
    if (dato > nodo->dato)
        return inserta(nodo->derecha, dato);

    return false;
}

template<typename T>
void AVL<T>::inorden(NodoAVL<T> *&nodo, VDinamico<NodoAVL<T> *> vector){
    
}

#endif //PRACTICACPP_AVL_H
