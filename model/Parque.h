//
// Created by Ángel Padilla Luzón on 01/10/2026.
//

#include "Arbol.h"
#include "../eedd/VDinamico.h"

#ifndef PRACTICACPP_PARQUE_H
#define PRACTICACPP_PARQUE_H


class Parque {
        int codigoParque;
        std::string nombreParque;
        VDinamico<Arbol> arboles;

    public:
        // Constructores
        Parque();
        Parque(int codigoParque, const  std::string &nombreParque);
        Parque(const Parque& original);

        // Destructor
        ~Parque();

        // Getters
        int getCodigoParque() const;
        std::string getNombreParque() const;
        Arbol* getArbol(int posicion);
        unsigned int getNArboles ();

        // Setters
        void setCodigoParque(int codigoParque);
        void setNombreParque (std::string nombreParque);

        // Operadores
        bool operator==(const Parque &original) const;

        // Utilidades
        bool existeNombreComun(const std::string &nombreComun);
        void insertarArbol(const Arbol& arbol);
        Arbol* getArbolMasAlto();
        int contarNumeroEspecies();
        int contarTiposPlantas();





};


#endif //PRACTICACPP_PARQUE_H
