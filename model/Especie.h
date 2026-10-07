//
// Created by Ángel Padilla Luzón on 19/09/2026.
//

#ifndef PR1_ESPECIE_H
#define PR1_ESPECIE_H

#include <string>

class Especie {
    std::string codigoEspecie;
    std::string nombreComun;
    std::string nombreCientifico;
    std::string tipoPlanta;

    public:
        /// Constructores
            Especie();
            Especie(std::string codigoEspecie, std::string nombreComun, std::string nombreCientifico, std::string tipoPlanta);
            Especie(const Especie& original);

        /// Destructor
            ~Especie();

        /// Getters y Setters
            void setCodigoEspecie (std::string codigoEspecie);
            void setNombreComun (std::string nombreComun);
            void setNombreCientifico (std::string nombreCientifico);
            void setTipoPlanta (std::string tipoPlanta);

            std::string getCodigoEspecie () const { return codigoEspecie;}
            std::string getNombreComun () const { return nombreComun;}
            std::string getNombreCientfico () const { return nombreCientifico;}
            std::string getTipoPlanta () const { return tipoPlanta;}

        /// Operadores
            bool operator==(const Especie& original);
            bool operator<(const Especie& original) const;

        /**
         * Funcion que muestra por pantalla todos los atributos de la clase.
        */
        void mostrarInfo();
};


#endif //PR1_ESPECIE_H
