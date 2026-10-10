//
// Created by Ángel Padilla Luzón on 10/10/2026.
//

#ifndef PRACTICACPP_CONTROLPARQUES_H
#define PRACTICACPP_CONTROLPARQUES_H

#include "../eedd/VDinamico.h"
#include "../eedd/ListaDEnlazada.h"
#include "Especie.h"
#include "Parque.h"

class ControlParques {
    VDinamico<Especie> especies;
    ListaDEnlazada<Parque> parques;

public:
    ControlParques();

    /**
     * Se encarga de enlazar la especie con el parque que la contiene.
     *
     * \param especie
     *      Especie que queremos enlazar con el parque.
     * \param parque
     *      Parque al que queremos asignarle la especie.
     */
    void asignarEspecieParque(const Especie& especie, Parque& parque);


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
};


#endif //PRACTICACPP_CONTROLPARQUES_H
