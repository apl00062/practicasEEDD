//
// Created by Ángel Padilla Luzón on 25/10/2026.
//

#ifndef PRACTICACPP_NODOAVL_H
#define PRACTICACPP_NODOAVL_H


template<typename U>
class NodoAVL {
    NodoAVL *izquierda, *derecha;
    U dato;
    char balanceado;
    int altura;


    NodoAVL(): izquierda(nullptr), derecha(nullptr), balanceado(0) {}
    NodoAVL(U &dato): izquierda(nullptr), derecha(nullptr), balanceado(0), dato(dato){}
};

#endif //PRACTICACPP_NODOAVL_H
