
#include "VDinamico.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

template<typename T>
VDinamico<T>::VDinamico() {
    this->tamFisico = 1;
    this->tamLogico = 0;
    this->vector = new T[tamFisico];
}

template<typename T>
VDinamico<T>::VDinamico(unsigned int tamLogico, T &dato) {
    if (tamLogico < 1) {
        throw std::invalid_argument("El tamanio logico tiene que ser mayor que 0.");
    }
    aumentarTamVector(tamLogico);
    for (int i = 0; i < tamLogico; ++i) {
        this->vector[i] = dato;
    }
}

template<typename T>
VDinamico<T>::VDinamico(const VDinamico &original) {
    this->tamLogico = original.tamLogico;
    this->tamFisico = original.tamFisico;
    this->vector = new T[this->tamFisico];
    for (int i = 0; i < this->tamLogico; ++i) {
        this->vector[i] = original.vector[i];
    }
}

template<typename T>
VDinamico<T>::VDinamico(const VDinamico &original, unsigned int posicionInicial, unsigned int numeroElementos) {
    if (posicionInicial < 0 || numeroElementos <= 0) {
        throw std::invalid_argument("La posicion inicial no puede ser negativa y el número de elementos tiene que ser mayor a 0.");
    }
    if (posicionInicial+numeroElementos > original.tamLogico) {
        throw std::out_of_range("PosicionInicial + Numero de elementos no pueden superar el Tamanio Logico");
    }

    this->tamLogico = original.tamLogico;
    this->tamFisico = original.tamFisico;
    this->vector = new T[tamFisico];
    for (int i = 0; i < numeroElementos; ++i) {
        this->vector[i] = original[posicionInicial+i];
    }
}

template<typename T>
VDinamico<T> &VDinamico<T>::operator=(const VDinamico &original) {
    if (this == &original)
        return *this;

    T* nuevoVector = new T[original.tamFisico];

    for (int i = 0; i < original.tamLogico; ++i) {
        nuevoVector[i] = original.vector[i];
    }

    delete [] this->vector;

    this->vector = nuevoVector;
    this->tamLogico = original.tamLogico;
    this->tamFisico = original.tamFisico;

    return *this;
}

template<typename T>
VDinamico<T>::~VDinamico() {
    this->tamLogico = 0;
    this->tamFisico = 0;
    delete [] this->vector;
}


template<typename T>
T& VDinamico<T>::operator[](unsigned int posicion) {
    if (posicion >= tamLogico) {
        throw std::out_of_range("La posicion indicada se encuentra vacía.");
    }
    return this->vector[posicion];
}


template<typename T>
bool VDinamico<T>::operator==(const VDinamico &original) {
    if (original.tamLogico != this->tamLogico || original.tamFisico != this->tamFisico) {
        return false;
    }

    for (int i = 0; i < this->tamLogico; ++i) {
        if (original.vector[i] != this->vector[i])
            return false;
    }
    return true;
}


template<typename T>
unsigned int VDinamico<T>::potenciaDeDos(unsigned int tamLogico) {
    unsigned int tamanio = tamLogico * 2;
    while (tamLogico > tamanio) {
        tamanio *= 2;
    }

    unsigned int potencia = 1;
    while (potencia < tamanio) {
        potencia *= 2;
    }
    return potencia;
}


template<typename T>
void VDinamico<T>::aumentarTamVector(unsigned int tamLogico) {
    if (tamLogico >= this->tamFisico) {
    unsigned int nuevoTamanio = potenciaDeDos(tamLogico);
    T* nuevoVector = new T[nuevoTamanio];
    for (int i = 0; i < this->tamLogico; ++i) {
        nuevoVector[i] = this->vector[i];
    }
    delete [] this->vector;
    this->vector = nuevoVector;
    this->tamLogico = tamLogico;
    this->tamFisico = nuevoTamanio;
    }
}


template<typename T>
void VDinamico<T>::insertar(const T &dato, unsigned int posicion) {
    if (posicion > this->tamLogico && posicion != UINT_MAX) {
        throw std::out_of_range("La posicion tiene que encontrarse dentro del tamanio logico");
    }
    if (this->tamLogico == this->tamFisico)
        aumentarTamVector(this->tamLogico);
    if (posicion == UINT_MAX) {
        this->vector[this->tamLogico] = dato;
        ++this->tamLogico;
    }
    else {
        for (int i = this->tamLogico; i > posicion; --i) {
            this->vector[i] = this->vector[i-1];
        }
        this->vector[posicion] = dato;
        ++this->tamLogico;
    }
}


template<typename T>
T& VDinamico<T>::eliminar(unsigned int posicion) {
    if (tamLogico == 0)
        throw std::out_of_range("El vector esta vacio.");

    if (posicion == UINT_MAX)
        posicion = tamLogico-1;

    if (posicion >= tamLogico)
        throw std::out_of_range("La posicion está vacía.");

    T& dato = this->vector[posicion];

    for (unsigned int i = posicion; i < this->tamLogico - 1; ++i)
        this->vector[i] = this->vector[i+1];

    --this->tamLogico;

    return dato;
}



template<typename T>
void VDinamico<T>::ordenar() {
    std::sort(this->vector, this->vector + this->tamLogico);
}


template<typename T>
int VDinamico<T>::busquedaDicotomica(const T &dato) {
    ordenar();
    int inferior = 0;
    int superior = this->tamLogico-1;
    int medio;

    while (inferior <= superior) {
        medio = (inferior + superior) / 2;
        if (this->vector[medio] == dato) {
            return medio;
        }
        else if (this->vector[medio] < dato) {
            inferior = medio + 1;
        }
        else {
            superior = medio -1;
        }
    }
    return -1;
}
