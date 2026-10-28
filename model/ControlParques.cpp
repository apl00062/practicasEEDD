//
// Created by Ángel Padilla Luzón on 10/10/2026.
//

#include "ControlParques.h"

#include <iostream>
#include <list>

ControlParques::ControlParques() {

}

ControlParques::ControlParques(VDinamico<Especie*> &especie, ListaDEnlazada<Parque*> &parques, AVL<Arbol*> &arboles) {
    this->especies = &especie;
    this->parques = &parques;
    this->arboles = &arboles;
}

Parque* ControlParques::getParque(unsigned int id) const {
    Iterador iterador(parques->getIterador());
    while (iterador.haySiguiente()) {
        if (iterador.dato()->getCodigoParque() == id) {
            return iterador.dato();
        }
        iterador.aSiguiente();
    }
    if (iterador.dato()->getCodigoParque() == id) {
        return iterador.dato();
    }

    throw std::invalid_argument("El id no existe.");
}

Especie* ControlParques::getEspecie(unsigned int posicion) {
    if (posicion >= this->getTamEspecies())
        throw std::invalid_argument("La posicion se encuentra fuera del vector.");

    return (*this->especies)[posicion];
}

int ControlParques::contarEspecieParque(const std::string& nombreComun) const {
    int contador = 0;
    Iterador iterador = parques->getIterador();
    while (iterador.haySiguiente()) {
        if (iterador.dato()->existeNombreComun(nombreComun))
            contador++;
        iterador.aSiguiente();
    }

    if (iterador.dato()->existeNombreComun(nombreComun))
        ++contador;

    return contador;
}

VDinamico<Especie*> ControlParques::listadoEspecieSubNombre(const std::string& subCadena) const {
    VDinamico<Especie*> listado;
    for (int i = 0; i < especies->getTamanioLogico(); ++i) {
        if ((*especies)[i]->getNombreCientfico().find(subCadena) != std::string::npos)
            listado.insertar((*especies)[i]);
    }
    return listado;
}

Parque *ControlParques::buscarParque(const std::string& nombreParque) const {
    Iterador iterador = parques->getIterador();
    while (iterador.haySiguiente()) {
        if (iterador.dato()->getNombreParque() == nombreParque)
            return iterador.dato();
        iterador.aSiguiente();
    }
    return nullptr;
}

Arbol* ControlParques::buscarArbol(const std::string& asNum) const {
    VDinamico<Arbol*> buscar = arboles->inorden();
    for (int i = 0; i < buscar.getTamanioLogico(); ++i) {
        if (buscar[i]->getAssetNum() == asNum)
            return buscar[i];
    }
    return nullptr;
}

VDinamico<Arbol*> ControlParques::listadoArbolesParque(const std::string &nombreParque) const {
    if (parques == nullptr)
        throw std::invalid_argument("No hay parques en el sistema.");

    Iterador iterador = parques->getIterador();
    VDinamico<Arbol*> arboles;
    while (iterador.haySiguiente()) {
        if (iterador.dato()->getNombreParque() == nombreParque)
            break;
        iterador.aSiguiente();
    }
    if (iterador.dato()->getNombreParque() != nombreParque)
        return arboles;

    for (int i = 0; i < iterador.dato()->getNArboles(); ++i) {
        arboles.insertar(iterador.dato()->getArbol(i));
    }

    return arboles;
}

Arbol *ControlParques::arbolMasAlto() const {
    if (parques == nullptr)
        throw std::invalid_argument("No hay parques en el sistema.");

    float altura = -1;
    Arbol *masAlto = nullptr;
    Iterador iterador = parques->getIterador();
    while (iterador.haySiguiente()) {
        if (iterador.dato()->getArbolMasAlto()->getAltura() > altura) {
            altura = iterador.dato()->getArbolMasAlto()->getAltura();
            masAlto = iterador.dato()->getArbolMasAlto();
        }
        iterador.aSiguiente();
    }
    if (iterador.dato()->getArbolMasAlto()->getAltura() > altura) {
        altura = iterador.dato()->getArbolMasAlto()->getAltura();
        masAlto = iterador.dato()->getArbolMasAlto();
    }

    return masAlto;
}

int ControlParques::contarEspecies(const std::string &nombreParque) const {
    if (parques == nullptr)
        throw std::invalid_argument("No hay parques en el sistema.");

    Iterador parque = parques->getIterador();
    int contador = 0;
    while (parque.haySiguiente())
    {
        if (parque.dato()->getNombreParque() == nombreParque)
        {
            contador = parque.dato()->contarNumeroEspecies();
            break;
        }
        parque.aSiguiente();
    }
    if (parque.dato()->getNombreParque() == nombreParque)
        contador = parque.dato()->contarNumeroEspecies();

    if (contador == 0)
        throw std::invalid_argument("El parque indicado no existe.");

    return contador;

}

int ControlParques::contarTipos() const {
    if (parques == nullptr)
        throw std::invalid_argument("No hay ningún parque en el sistema.");

    Iterador iterador = parques->getIterador();
    int contador = 0;
    VDinamico<std::string> especiesPresentes;
    especiesPresentes.insertar(iterador.dato()->getArbol(0)->getTipoPlanta());
    iterador.aSiguiente();
    while (iterador.haySiguiente()) {
        for (int i = 0; i < iterador.dato()->getNArboles(); ++i) {
            bool nuevo = true;
            for (int j = 0; j < especiesPresentes.getTamanioLogico(); ++j) {
                if (iterador.dato()->getArbol(i)->getTipoPlanta() == especiesPresentes[j])
                    nuevo = false;
            }
            if (nuevo) {
                ++contador;
                especiesPresentes.insertar(iterador.dato()->getArbol(i)->getTipoPlanta());
            }
        }
    }
    return contador;
}