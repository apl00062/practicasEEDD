//
// Created by Ángel Padilla Luzón on 01/10/2026.
//

#include "Especie.h"
#include "../eedd/VDinamico.h"

#ifndef PRACTICACPP_PARQUE_H
#define PRACTICACPP_PARQUE_H


class Parque {
    private:
        int codigoParque;
        std::string nombreParque;
        VDinamico<Especie*> especies;

    public:
        // Constructores
        Parque();
        Parque(int codigoParque, std::string nombreParque, VDinamico<Especie*> especies);
        Parque(const Parque& original);

        // Destructor
        ~Parque();

        // Getters
        int getCodigoParque();
        std::string getNombreParque();

        Especie* getEspecie(int posicion);

        // Setters
        void setCodigoParque(int codigoParque);
        void setNombreParque (std::string nombreParque);

        // Utilidades
        void insertarEspecie(Especie especie);
        bool existeNombreComun(std::string nombreComun);
        bool existeNombreCientifico(std::string nombreCientifico);




};


#endif //PRACTICACPP_PARQUE_H
