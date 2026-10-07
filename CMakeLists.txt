cmake_minimum_required(VERSION 3.20)
project(PracticaCPP CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(PracticaCPP
        main.cpp
        io/LectorCSV.cpp
        model/Especie.cpp
        eedd/ListaDEnlazada.h
        model/Parque.cpp
        model/Parque.h
)