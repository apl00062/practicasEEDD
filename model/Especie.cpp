//
// Created by Ángel Padilla Luzón on 19/09/2026.
//

#include "Especie.h"

#include <iostream>

Especie::Especie() {
    this->codigoEspecie = "";
    this->nombreComun = "";
    this->nombreCientifico = "";
    this->tipoPlanta = "";
}

Especie::Especie(std::string codigoEspecie, std::string nombreComun, std::string nombreCientifico, std::string tipoPlanta) {
    this->codigoEspecie = codigoEspecie;
    this->nombreComun = nombreComun;
    this->nombreCientifico = nombreCientifico;
    this->tipoPlanta = tipoPlanta;
}

Especie::Especie(const Especie &original) {
    this->codigoEspecie = original.codigoEspecie;
    this->nombreComun = original.nombreComun;
    this->nombreCientifico = original.nombreCientifico;
    this->tipoPlanta = original.tipoPlanta;
}

Especie::~Especie() {

}

void Especie::setCodigoEspecie(std::string codigoEspecie) {
    this->codigoEspecie = codigoEspecie;
}

void Especie::setNombreComun(std::string nombreComun) {
    this->nombreComun = nombreComun;
}

void Especie::setNombreCientifico(std::string nombreCientifico) {
    this->nombreCientifico = nombreCientifico;
}

void Especie::setTipoPlanta(std::string tipoPlanta) {
    this->tipoPlanta = tipoPlanta;
}

bool Especie::operator==(const Especie &original) {
    if (this->codigoEspecie == original.getCodigoEspecie())
        return true;
    return false;
}

bool Especie::operator<(const Especie &original) const {
    if (this->codigoEspecie < original.codigoEspecie)
        return true;
    return false;
}


void Especie::mostrarInfo() {
    std::cout << "Codigo Especie: " << this->codigoEspecie << std::endl
        << "Nombre Comun: " << this->nombreComun << std::endl
        << "Nombre Científico: " << this->nombreCientifico << std::endl
        << "Tipo Planta: "  << this->tipoPlanta << std::endl;
}
