//
// Created by Ángel Padilla Luzón on 10/10/2026.
//

#include "ControlParques.h"

#include <iostream>
#include <list>

ControlParques::ControlParques() {

}

ControlParques::ControlParques(VDinamico<Especie> &especie, ListaDEnlazada<Parque> &parques) {
    this->especies = &especie;
    this->parques = &parques;
}

Parque* ControlParques::getParque(unsigned int id) {
    Iterador<Parque> iterador(parques->getIterador());
    while (iterador.haySiguiente()) {
        if (iterador.dato().getCodigoParque() == id) {
            return &iterador.dato();
        }
        iterador.aSiguiente();
    }
    if (iterador.dato().getCodigoParque() == id) {
        return &iterador.dato();
    }

    throw std::invalid_argument("El id no existe.");
}

Especie* ControlParques::getEspecie(unsigned int posicion) {
    if (posicion >= this->getTamEspecies())
        throw std::invalid_argument("La posicion se encuentra fuera del vector.");

    return &(*this->especies)[posicion];
}

int ControlParques::contarEspecieParque(const std::string& nombreComun) {
    int contador = 0;
    Iterador<Parque> iterador = parques->getIterador();
    while (iterador.haySiguiente()) {
        if (iterador.dato().existeNombreComun(nombreComun))
            contador++;
        iterador.aSiguiente();
    }

    if (iterador.dato().existeNombreComun(nombreComun))
        ++contador;

    return contador;
}

VDinamico<Especie*> ControlParques::listadoEspecieSubNombre(const std::string& subCadena) {
    VDinamico<Especie*> listado;
    for (int i = 0; i < especies->getTamanioLogico(); ++i) {
        if ((*especies)[i].getNombreCientfico().find(subCadena) != std::string::npos)
            listado.insertar(&(*especies)[i]);
    }
    return listado;
}

Parque *ControlParques::buscarParque(const std::string& nombreParque) {
    Iterador<Parque> iterador = parques->getIterador();
    while (iterador.haySiguiente()) {
        if (iterador.dato().getNombreParque() == nombreParque)
            return &iterador.dato();
        iterador.aSiguiente();
    }
    return nullptr;
}

Arbol* ControlParques::buscarArbol(const std::string& asNum)
{
    
}
