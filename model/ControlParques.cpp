//
// Created by Ángel Padilla Luzón on 10/10/2026.
//

#include "ControlParques.h"

#include <iostream>
#include <list>

ControlParques::ControlParques() {

}

void ControlParques::asignarEspecieParque(const Especie &especie, Parque &parque) {
    Parque* aAsignar = parques.buscarDato(parque);
    if (aAsignar != nullptr)
        aAsignar->insertarEspecie(especie);
    else
        std::cout << "El parque: " + parque.getNombreParque() + " no se encuentra en el sistema." << std::endl;
}

int ControlParques::contarEspecieParque(const std::string& nombreComun) {
    int contador = 0;
    Iterador<Parque> iterador = parques.getIterador();
    while (iterador.haySiguiente()) {
        if (iterador.dato().existeNombreComun(nombreComun))
            contador++;
    }
    return contador;
}

VDinamico<Especie*> ControlParques::listadoEspecieSubNombre(const std::string& subCadena) {
    VDinamico<Especie*> listado;
    for (int i = 0; i < especies.getTamanioLogico(); ++i) {
        if (especies[i].getNombreCientfico().find(subCadena) != std::string::npos)
            listado.insertar(&especies[i]);
    }
    return listado;
}

Parque *ControlParques::buscarParque(const std::string& nombreParque) {
    Iterador<Parque> iterador = parques.getIterador();
    while (iterador.haySiguiente()) {
        if (iterador.dato().getNombreParque() == nombreParque)
            return &iterador.dato();
    }
    return nullptr;
}
