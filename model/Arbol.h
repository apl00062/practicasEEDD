//
// Created by apl on 20/10/2026.
//

#ifndef PRACTICACPP_ARBOL_H
#define PRACTICACPP_ARBOL_H

#include <iostream>
#include "Especie.h"

class Arbol
{
    std::string assetNum;
    int numParque;
    int numDistrito;
    std::string nombreDistrito;
    int numBarrio;
    std::string nombreBarrio;
    double x;
    double y;
    float perimetro;
    float altura;

    Especie *especie;

public:
    /// Constructores: Por defecto, Parametrizado, Por copia
    Arbol();
    Arbol(const std::string& assetNum, int numParque, int numDistrito, const std::string& nombreDistrito,
            int numBarrio, const std::string& nombreBarrio, double x, double y, float perimetro, float altura);
    Arbol(const std::string& assetNum);
    Arbol(const Arbol& original);

    /// Destructor
    ~Arbol();

    /// Getters y Setters
    void setEspecie(Especie *especie);
    float getAltura() const;
    std::string getAssetNum() const;
    int getNumParque() const;
    std::string getNombreDistrito() const;

    bool operator<(const Arbol& original) const;
    bool operator==(const Arbol& original) const;

    /// Getters provenientes del puntero a especie
    std::string getCodigoEspecie() const;
    std::string getTipoPlanta() const;
    std::string getNombreComun() const ;
    Especie* getEspecie() const;
    int getCodigoParque() const;
    std::string getNombreCientifico() const;
};


#endif //PRACTICACPP_ARBOL_H
