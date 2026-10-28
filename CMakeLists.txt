cmake_minimum_required(VERSION 3.20)
project(PracticaCPP CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PracticaCPP
        main.cpp
        io/LectorCSV.cpp
        model/Especie.cpp
        eedd/ListaDEnlazada.h
        model/Parque.cpp
        model/Parque.h
        eedd/Operadores/NodoListaDEnlazada.h
        eedd/Operadores/Iterador.h
        model/ControlParques.cpp
        model/ControlParques.h
        model/Arbol.cpp
        model/Arbol.h
        eedd/AVL.h
        eedd/Operadores/NodoAVL.h
)