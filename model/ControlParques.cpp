//
// Created by Ángel Padilla Luzón on 10/10/2026.
//

#include "ControlParques.h"


const std::string RUTA_FICHERO_ESPECIES = "data/arbolado-especies.csv";
const std::string RUTA_FICHERO_PARQUES = "data/parques.csv";
const std::string RUTA_FICHERO_ARBOLES = "data/arboladoMadrid.csv";

ControlParques::ControlParques(LectorCSV &lector_csv) {

    if (!lector_csv.cargarVector(especies, RUTA_FICHERO_ESPECIES))
        throw std::invalid_argument("Ha ocurrido un problema con la carga de Especies.");

    if (!lector_csv.cargarArbol(arboles, RUTA_FICHERO_ARBOLES, especies))
        throw std::invalid_argument("Ha ocurrido un problema con la cargar de Arboles.");

    VDinamico<Arbol> arboleh = arboles.inorden();
    if (!lector_csv.cargarLista(parques, RUTA_FICHERO_PARQUES, arboleh))
        throw std::invalid_argument("Ha ocurrido un problema con la carga de Parques.");


}

Parque* ControlParques::getParque(const unsigned int id) const {
    Iterador<Parque> iterador(parques.getIterador());
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

    Especie* toRet = &(especies)[posicion];
    return toRet;
}

int ControlParques::contarEspecieParque(const std::string& nombreComun) const {
    int contador = 0;
    Iterador<Parque> iterador = parques.getIterador();
    while (iterador.haySiguiente()) {
        if (iterador.dato().existeNombreComun(nombreComun))
            contador++;
        iterador.aSiguiente();
    }

    if (iterador.dato().existeNombreComun(nombreComun))
        ++contador;

    return contador;
}

VDinamico<Especie*> ControlParques::listadoEspecieSubNombre(const std::string& subCadena) const {
    VDinamico<Especie*> listado;
    for (int i = 0; i < especies->getTamanioLogico(); ++i) {
        if ((*especies)[i].getNombreCientfico().find(subCadena) != std::string::npos) {
            Especie* aInsertar = &(*especies)[i];
            listado.insertar(aInsertar);
        }
    }
    return listado;
}

Parque *ControlParques::buscarParque(const std::string& nombreParque) const {
    Iterador<Parque> iterador = parques->getIterador();
    while (iterador.haySiguiente()) {
        if (iterador.dato().getNombreParque() == nombreParque)
            return &iterador.dato();
        iterador.aSiguiente();
    }
    return nullptr;
}

Arbol* ControlParques::buscarArbol(const std::string& asNum) const {
    VDinamico<Arbol> buscar = arboles->inorden();
    for (int i = 0; i < buscar.getTamanioLogico(); ++i) {
        if (buscar[i].getAssetNum() == asNum)
            return &buscar[i];
    }
    return nullptr;
}

VDinamico<Arbol*> ControlParques::listadoArbolesParque(const std::string &nombreParque) const {
    if (parques == nullptr)
        throw std::invalid_argument("No hay parques en el sistema.");

    Iterador<Parque> iterador = parques->getIterador();
    VDinamico<Arbol*> arboleh;
    while (iterador.haySiguiente()) {
        if (iterador.dato().getNombreParque() == nombreParque)
            break;
        iterador.aSiguiente();
    }
    if (iterador.dato().getNombreParque() != nombreParque)
        return arboleh;

    for (int i = 0; i < iterador.dato().getNArboles(); ++i) {
        Arbol* aInsertar = iterador.dato().getArbol(i);
        arboleh.insertar(aInsertar);
    }

    return arboleh;
}

Arbol *ControlParques::arbolMasAlto() const {
    if (parques == nullptr)
        throw std::invalid_argument("No hay parques en el sistema.");

    float altura = -1;
    Arbol *masAlto = nullptr;
    Iterador<Parque> iterador = parques->getIterador();
    while (iterador.haySiguiente()) {
        if (iterador.dato().getArbolMasAlto()->getAltura() > altura) {
            altura = iterador.dato().getArbolMasAlto()->getAltura();
            masAlto = iterador.dato().getArbolMasAlto();
        }
        iterador.aSiguiente();
    }
    if (iterador.dato().getArbolMasAlto()->getAltura() > altura) {
        altura = iterador.dato().getArbolMasAlto()->getAltura();
        masAlto = iterador.dato().getArbolMasAlto();
    }

    return masAlto;
}

int ControlParques::contarEspecies(const std::string &nombreParque) const {
    if (parques == nullptr)
        throw std::invalid_argument("No hay parques en el sistema.");

    Iterador<Parque> iterador = parques->getIterador();
    int contador = 0;
    while (iterador.haySiguiente())
    {
        if (iterador.dato().getNombreParque() == nombreParque)
        {
            contador = iterador.dato().contarNumeroEspecies();
            break;
        }
        iterador.aSiguiente();
    }
    if (iterador.dato().getNombreParque() == nombreParque)
        contador = iterador.dato().contarNumeroEspecies();

    if (contador == 0)
        throw std::invalid_argument("El parque indicado no existe.");

    return contador;

}

int ControlParques::contarTipos() const {
    if (parques == nullptr)
        throw std::invalid_argument("No hay ningún parque en el sistema.");

    Iterador<Parque> iterador = parques->getIterador();
    int contador = 0;
    VDinamico<std::string> especiesPresentes;
    std::string aInsertar = iterador.dato().getArbol(0)->getTipoPlanta();
    especiesPresentes.insertar(aInsertar);
    iterador.aSiguiente();
    while (iterador.haySiguiente()) {
        for (int i = 0; i < iterador.dato().getNArboles(); ++i) {
            bool nuevo = true;
            for (int j = 0; j < especiesPresentes.getTamanioLogico(); ++j) {
                if (iterador.dato().getArbol(i)->getTipoPlanta() == especiesPresentes[j])
                    nuevo = false;
            }
            if (nuevo) {
                ++contador;
                std::string aInsertar2 = iterador.dato().getArbol(i)->getTipoPlanta();
                especiesPresentes.insertar(aInsertar2);
            }
        }
    }
    return contador;
}