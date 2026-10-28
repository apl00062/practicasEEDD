//
// Created by Ángel Padilla Luzón on 01/10/2026.
//

#include "Parque.h"

Parque::Parque(int codigoParque, const std::string &nombreParque) {
    this->codigoParque = codigoParque;
    this->nombreParque = nombreParque;
}


Parque::Parque(const Parque &original) {
    this->codigoParque = original.codigoParque;
    this->nombreParque = original.nombreParque;
    this->arboles = original.arboles;
}


int Parque::getCodigoParque() const {
    return this->codigoParque;
}


Arbol* Parque::getArbol(int posicion){
    return this->arboles[posicion];
}

unsigned int Parque::getNArboles() {
    return this->arboles.getTamanioLogico();
}

std::string Parque::getNombreParque() const{
    return this->nombreParque;
}


void Parque::setCodigoParque(int codParque) {
    this->codigoParque = codParque;
}


void Parque::setNombreParque(const std::string& nomParque) {
    this->nombreParque = nomParque;
}


bool Parque::operator==(const Parque &original) const{
    return this->codigoParque == original.codigoParque;
}

void Parque::insertarArbol(Arbol* arbol) {
    arboles.insertar(arbol);
}

bool Parque::existeNombreComun(const std::string& nombreComun)
{
    for (int i = 0; i < this->arboles.getTamanioLogico(); ++i)
    {
        if (arboles[i]->getNombreComun() == nombreComun)
            return true;
    }
    return false;
}

int Parque::contarNumeroEspecies() {
    if (arboles.getTamanioLogico() <= 0)
        throw std::out_of_range("El vector de arboles esta vacio.");
    int contador = 0;
    VDinamico<std::string> especies;
    for (int i = 0; i < this->arboles.getTamanioLogico(); ++i) {
        for (int j = 0; j < especies.getTamanioLogico(); ++j) {
            if (this->arboles[i]->getCodigoEspecie() != especies[j]) {
                contador++;
                std::string aInsertar = this->arboles[i]->getCodigoEspecie();
                especies.insertar(aInsertar);
            }
        }
    }
    return contador;
}

int Parque::contarTiposPlantas() {
    if (arboles.getTamanioLogico() <= 0)
        throw std::out_of_range("El vector de arboles esta vacio.");
    int contador = 0;
    VDinamico<std::string> plantas;
    for (int i = 0; i < this->arboles.getTamanioLogico(); ++i) {
        for (int j = 0; j < plantas.getTamanioLogico(); ++j) {
            if (this->arboles[i]->getTipoPlanta() != plantas[j]) {
                contador++;
                std::string aInsertar = this->arboles[i]->getTipoPlanta();
                plantas.insertar(aInsertar);
            }
        }
    }
    return contador;
}

Arbol* Parque::getArbolMasAlto() {
    if (arboles.getTamanioLogico() <= 0)
        throw std::out_of_range("El vector de arboles esta vacio.");
    float altura = 0;
    int posicion = 0;
    for (int i = 0; i < this->arboles.getTamanioLogico(); ++i) {
        if (altura < this->arboles[i]->getAltura()) {
            posicion = i;
            altura = this->arboles[i]->getAltura();
        }
    }
    return this->arboles[posicion];
}


