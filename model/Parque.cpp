//
// Created by Ángel Padilla Luzón on 01/10/2026.
//

#include "Parque.h"

Parque::Parque() {
    especies = VDinamico<Especie>();
}


Parque::Parque(int codigoParque, const std::string &nombreParque) {
    this->codigoParque = codigoParque;
    this->nombreParque = nombreParque;
}


Parque::Parque(const Parque &original) {
    this->codigoParque = original.codigoParque;
    this->nombreParque = original.nombreParque;
    this->especies = original.especies;
}


Parque::~Parque() {

}


int Parque::getCodigoParque() {
    return this->codigoParque;
}


Especie Parque::getEspecie(int posicion) {
    return this->especies[posicion];
}


std::string Parque::getNombreParque() {
    return this->nombreParque;
}


void Parque::setCodigoParque(int codigoParque) {
    this->codigoParque = codigoParque;
}


void Parque::setNombreParque(std::string nombreParque) {
    this->nombreParque = nombreParque;
}


void Parque::insertarEspecie(const Especie& especie) {
    especies.insertar(especie);
}


bool Parque::existeNombreComun(std::string nombreComun) {
    for (int i = 0; i < especies.getTamanioLogico(); ++i) {
        if (especies[i].getNombreComun() == nombreComun)
            return true;
    }
    return false;
}


bool Parque::existeNombreCientifico(std::string nombreCientifico) {
    for (int i = 0; i < especies.getTamanioLogico(); ++i) {
        if (especies[i].getNombreCientfico() == nombreCientifico)
            return true;
    }
    return false;
}

bool Parque::operator==(const Parque &original) const{
    return this->codigoParque == original.codigoParque;
}
