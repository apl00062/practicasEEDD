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
        VDinamico<Arbol*> arboles;

    public:
        // Constructores
        Parque() = default;
        Parque(int codigoParque, const  std::string &nombreParque);
        Parque(const Parque& original);

        // Destructor
        ~Parque() = default;

        // Getters
        int getCodigoParque() const;
        std::string getNombreParque() const;
        Arbol* getArbol(int posicion);
        unsigned int getNArboles ();

        // Setters
        void setCodigoParque(int codParque);
        void setNombreParque (const std::string &nomParque);

        // Operadores
        bool operator==(const Parque &original) const;

        // Utilidades
        bool existeNombreComun(const std::string &nombreComun);
        void insertarArbol(Arbol* arbol);
        Arbol* getArbolMasAlto();
        int contarNumeroEspecies();
        int contarTiposPlantas();





};


#endif //PRACTICACPP_PARQUE_H
