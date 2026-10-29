//
// Created by apl on 20/10/2026.
//

#include "Arbol.h"


Arbol::Arbol() {
    this->especie = nullptr;
}

Arbol::Arbol(const std::string& assetNum, int numParque, int numDistrito, const std::string& nombreDistrito,
    int numBarrio, const std::string& nombreBarrio, double x, double y, float perimetro, float altura) {

    this->assetNum = assetNum;
    this->numParque = numParque;
    this->numDistrito = numDistrito;
    this->nombreDistrito = nombreDistrito;
    this->numBarrio = numBarrio;
    this->nombreBarrio = nombreBarrio;
    this->x = x;
    this->y = y;
    this->perimetro = perimetro;
    this->altura = altura;
    this->especie = nullptr;
}

Arbol::Arbol(const std::string& assetNum)
{
    this->assetNum = assetNum;
}

Arbol::Arbol(const Arbol& original) {
    this->assetNum = original.assetNum;
    this->numParque = original.numParque;
    this->numDistrito = original.numDistrito;
    this->nombreDistrito = original.nombreDistrito;
    this->numBarrio = original.numBarrio;
    this->nombreBarrio = original.nombreBarrio;
    this->x = original.x;
    this->y = original.y;
    this->perimetro = original.perimetro;
    this->altura = original.altura;
    this->especie = original.especie;
}

Arbol::~Arbol() {
    this->especie = nullptr;
}

void Arbol::setEspecie(Especie* especie) {
    if (especie == nullptr)
        throw std::invalid_argument("La especie no puede ser nula");

    this->especie = especie;
}

float Arbol::getAltura() const {
    return this->altura;
}

std::string Arbol::getAssetNum() const
{
    return this->assetNum;
}

int Arbol::getNumParque() const
{
    return this->numParque;
}

std::string Arbol::getNombreDistrito() const
{
    return this->nombreDistrito;
}

bool Arbol::operator<(const Arbol &original) const {
    if (this->assetNum < original.getAssetNum())
        return true;

    return false;
}

bool Arbol::operator==(const Arbol &original) const
{
    if (this->assetNum == original.getAssetNum())
        return true;
    return false;
}

std::string Arbol::getCodigoEspecie() const{
    return especie->getCodigoEspecie();
}

std::string Arbol::getNombreComun() const{
    return especie->getNombreComun();
}

std::string Arbol::getTipoPlanta() const {
    return especie->getTipoPlanta();
}

Especie *Arbol::getEspecie() const {
    return this->especie;
}

int Arbol::getCodigoParque() const {
    return this->numParque;
}

std::string Arbol::getNombreCientifico() const {
    return this->especie->getNombreCientfico();
}
