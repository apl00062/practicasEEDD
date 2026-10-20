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
        int getCodigoParque();
        std::string getNombreParque();
        Arbol& getArbol(int posicion);

        // Setters
        void setCodigoParque(int codigoParque);
        void setNombreParque (std::string nombreParque);

        // Operadores
        bool operator==(const Parque &original) const;

        // Utilidades
        void insertarArbol(const Arbol& arbol);
        const Arbol& getArbolMasAlto();
        int contarNumeroEspecies();
        int contarTiposPlantas();





};


#endif //PRACTICACPP_PARQUE_H
