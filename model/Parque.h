//
// Created by Ángel Padilla Luzón on 01/10/2026.
//

#include "Especie.h"
#include "../eedd/VDinamico.h"

#ifndef PRACTICACPP_PARQUE_H
#define PRACTICACPP_PARQUE_H


class Parque {
        int codigoParque;
        std::string nombreParque;
        VDinamico<Especie> especies;

    public:
        // Constructores
        Parque();
        Parque(int codigoParque, const  std::string &nombreParque);
        Parque(const Parque& original);

        // Destructor
        ~Parque();

        // Getters
        int getCodigoParque();
        std::string getNombreParque();
        Especie getEspecie(int posicion);

        // Setters
        void setCodigoParque(int codigoParque);
        void setNombreParque (std::string nombreParque);

        // Operadores
        bool operator==(const Parque &original) const;

        // Utilidades
        void insertarEspecie(const Especie& especie);
        bool existeNombreComun(std::string nombreComun);
        bool existeNombreCientifico(std::string nombreCientifico);




};


#endif //PRACTICACPP_PARQUE_H
