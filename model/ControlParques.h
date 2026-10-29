//
// Created by Ángel Padilla Luzón on 10/10/2026.
//

#ifndef PRACTICACPP_CONTROLPARQUES_H
#define PRACTICACPP_CONTROLPARQUES_H

#include "../eedd/VDinamico.h"
#include "../eedd/ListaDEnlazada.h"
#include "../eedd/AVL.h"
#include "../io/LectorCSV.h"
#include "Especie.h"


class ControlParques {
    VDinamico<Especie> especies;
    ListaDEnlazada<Parque> parques;
    AVL<Arbol> arboles;

public:
    /// Constructor
    ControlParques(LectorCSV &lector_csv);

    /// Getters y Setters
    unsigned int getTamEspecies () { return especies.getTamanioLogico(); }
    unsigned int getTamParques () const { return parques.getTamLista(); }
    unsigned int getTamArboles () const { return arboles.getNumElementos(); }
    unsigned int getAlturaArbol () const { return arboles.getAltura(); }
    Parque* getParque(unsigned int id);
    Especie* getEspecie(unsigned int posicion);

    /**
    * Se encarga de contar los parque que tienen una especie dando como parámetro su nombre común.
    *
    * \param nombreComun
    *       Nombre de la especie que queremos buscar.
    */
    int contarEspecieParque(const std::string &nombreComun);


    /**
     * Devuelve aquellas especies que contengan en su nombre científico una subcadena dada como parámetro.
     *
     * \param subCadena
     *      Subcadena del nombre cientifico de una especie.
     */
    VDinamico<Especie*> listadoEspecieSubNombre(const std::string &subCadena);


    /**
     * Se encarga de buscar un parque dado un nombre.
     *
     * \param nombreParque
     *      Nombre del Parque que queremos buscar.
     */
    Parque* buscarParque(const std::string& nombreParque);

    Arbol* buscarArbol(const std::string& asNum);
    VDinamico<Arbol*> listadoArbolesParque(const std::string& nombreParque);
    Arbol* arbolMasAlto();
    int contarEspecies(const std::string& nombreParque);
    int contarTipos();
};


#endif //PRACTICACPP_CONTROLPARQUES_H
