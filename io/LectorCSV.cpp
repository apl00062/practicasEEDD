#include "LectorCSV.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include "../model/Especie.h"

/**
 * @brief Carga el fichero CSV indicado, mostrando cada especie por pantalla.
 *
 * Cada línea se analiza y, si tiene el número de campos esperado, se
 * construye una Especie que se almacena en el VDinamico
 * Las filas con un número de campos
 * distinto del esperado se descartan (ver filasDescartadas()).
 *
 * @param rutaFichero Ruta del fichero CSV a leer.
 * @return true si el fichero se ha podido abrir, false en caso contrario.
 */
bool LectorCSV::cargarVector(VDinamico<Especie> &vector, const std::string& rutaFichero) {

    filasDescartadas_ = 0;

    std::ifstream fichero(rutaFichero);
    if (!fichero.is_open()) {
        return false;
    }

    std::string linea;
    if (std::getline(fichero, linea)) {
        eliminarBOM(linea);
    }

    //Declaradas fuera del bucle por eficiencia
    std::string codigo, nombreComun, nombreCientifico, tipoPlanta;

    while (std::getline(fichero, linea)) {
        if (linea.empty()) {
            continue;
        }

        if (contarCampos(linea) != 4) {
            ++filasDescartadas_;
            continue;
        }

        codigo = extraerCampo(linea, 0);
        nombreComun = extraerCampo(linea, 1);
        nombreCientifico = extraerCampo(linea, 2);
        tipoPlanta = extraerCampo(linea, 3);
        Especie aInsertar = Especie(codigo,nombreComun,nombreCientifico,tipoPlanta);
        vector.insertar(aInsertar);
    }

    numeroEspecies_= vector.getTamanioLogico();
    return true;
}

bool LectorCSV::cargarArbol(AVL<Arbol> &arbol, const std::string& rutaFichero, VDinamico<Especie> &especies) {

    filasDescartadas_ = 0;

    std::ifstream fichero(rutaFichero);
    if (!fichero.is_open()) {
        return false;
    }

    std::string linea;
    if (std::getline(fichero, linea)) {
        eliminarBOM(linea);
    }

    //Declaradas fuera del bucle por eficiencia
    std::string assetnum, numParque, numDistrito, nombDistrito, numBarrio, nombBarrio;
    std::string x, y, codEspecie, perimetro, alturaTotal;


    while (std::getline(fichero, linea)) {

        if (!linea.empty() && linea.back() == '\r') {
            linea.pop_back();
        }

        if (linea.empty()) {
            continue;
        }

        if (contarCamposArbol(linea) != 12) {

            ++filasDescartadas_;
            continue;
        }


        assetnum = extraerCampoArbol(linea, 0);
        numParque = extraerCampoArbol(linea, 1);
        int nParque = std::stoi(numParque);
        numDistrito = extraerCampoArbol(linea, 2);
        int nDistrito = std::stoi(numDistrito);
        nombDistrito = extraerCampoArbol(linea, 3);
        numBarrio = extraerCampoArbol(linea, 4);
        int nBarrio = std::stoi(numBarrio);
        nombBarrio = extraerCampoArbol(linea, 5);
        x = extraerCampoArbol(linea, 6);
        double fx = std::stod(x);
        y = extraerCampoArbol(linea, 7);
        double fy = std::stod(y);
        codEspecie = extraerCampoArbol(linea, 8);
        perimetro = extraerCampoArbol(linea, 10);
        alturaTotal = extraerCampoArbol(linea, 11);

        if (perimetro.empty() || alturaTotal.empty()) {
            ++filasDescartadas_;
            continue;
        }

        std::replace(perimetro.begin(), perimetro.end(), ',', '.');
        std::replace(alturaTotal.begin(), alturaTotal.end(), ',', '.');

        float perim = std::stof(perimetro);
        float altura = std::stof(alturaTotal);

        Arbol aInsertar = Arbol(assetnum, nParque,nDistrito,nombDistrito, nBarrio,
            nombBarrio,fx,fy,perim,altura);
        for (int i = 0; i < this->numeroEspecies_; ++i)
        {

            if (especies[i].getCodigoEspecie() == codEspecie)
            {
                aInsertar.setEspecie(&especies[i]);
                break;
            }
        }
        arbol.inserta(aInsertar);

    }

    numeroArboles_= arbol.getNumElementos();
    return true;
}

/**
 * @brief Número de especies leídas correctamente.
 * @return Cantidad de especies mostradas durante la última llamada a cargar().
 */
std::size_t LectorCSV::numeroEspecies() const {
    return numeroEspecies_;
}

/**
 * @brief Número de filas descartadas por no tener el número de campos esperado.
 * @return Cantidad de filas descartadas durante la última llamada a cargar().
 */
std::size_t LectorCSV::filasDescartadas() const {
    return filasDescartadas_;
}

/**
 * @brief Cuenta los campos de una línea CSV sin almacenarlos.
 *
 * Tiene en cuenta comillas envolventes y comillas escapadas ("") dentro
 * de un campo entrecomillado, tal como especifica RFC4180.
 *
 * @param linea Línea física a analizar.
 * @return Número de campos que contiene la línea.
 */
std::size_t LectorCSV::contarCampos(const std::string& linea) {
    std::size_t numCampos = 1;
    bool dentroComillas = false;
    const std::size_t n = linea.size();

    for (std::size_t i = 0; i < n; ) {
        const char c = linea[i];

        if (dentroComillas) {
            if (c == '"') {
                if (i + 1 < n && linea[i + 1] == '"') {
                    i += 2;
                } else {
                    dentroComillas = false;
                    ++i;
                }
            } else {
                ++i;
            }
        } else if (c == '"') {
            dentroComillas = true;
            ++i;
        } else if (c == ',') {
            ++numCampos;
            ++i;
        } else {
            ++i;
        }
    }

    return numCampos;
}

/**
 * @brief Extrae un único campo (por índice) de una línea CSV.
 *
 * Recorre la línea completa pero solo acumula el contenido del campo
 * solicitado; el resto de campos se descarta sin llegar a almacenarse.
 * Tiene en cuenta comillas envolventes y comillas escapadas ("").
 *
 * @param linea Línea física a analizar.
 * @param indiceObjetivo Índice (base 0) del campo a extraer.
 * @return Contenido del campo solicitado.
 */
std::string LectorCSV::extraerCampo(const std::string& linea, std::size_t indiceObjetivo) {
    std::string campo;
    std::size_t indiceActual = 0;
    bool dentroComillas = false;
    const std::size_t n = linea.size();

    for (std::size_t i = 0; i < n; ) {
        const char c = linea[i];

        if (dentroComillas) {
            if (c == '"') {
                if (i + 1 < n && linea[i + 1] == '"') {
                    if (indiceActual == indiceObjetivo) {
                        campo += '"';
                    }
                    i += 2;
                } else {
                    dentroComillas = false;
                    ++i;
                }
            } else {
                if (indiceActual == indiceObjetivo) {
                    campo += c;
                }
                ++i;
            }
        } else if (c == '"') {
            dentroComillas = true;
            ++i;
        } else if (c == ',') {
            if (indiceActual == indiceObjetivo) {
                return campo;
            }
            ++indiceActual;
            ++i;
        } else {
            if (indiceActual == indiceObjetivo) {
                campo += c;
            }
            ++i;
        }
    }

    return campo;
}

/**
 * @brief Elimina el BOM UTF-8 (0xEF 0xBB 0xBF) al inicio de la línea, si existe.
 * @param linea Línea a modificar in-place.
 */
void LectorCSV::eliminarBOM(std::string& linea) {
    static const char bom[3] = { static_cast<char>(0xEF), static_cast<char>(0xBB), static_cast<char>(0xBF) };
    if (linea.size() >= 3 && linea[0] == bom[0] && linea[1] == bom[1] && linea[2] == bom[2]) {
        linea.erase(0, 3);
    }
}

/**
 * @brief Muestra por pantalla los datos de una especie.
 * @param especie Especie a mostrar.
 */
void LectorCSV::mostrarEspecie(const Especie& especie) {
    std::cout << " - [" << especie.getCodigoEspecie() << "] " << especie.getNombreComun()
              << " (" << especie.getNombreCientfico() << ") - "
              << especie.getTipoPlanta() << "\n";
}


bool LectorCSV::cargarLista(ListaDEnlazada<Parque> &lista, const std::string& rutaFichero, VDinamico<Arbol*> &arboles) {

    filasDescartadas_ = 0;

    std::ifstream fichero(rutaFichero);
    if (!fichero.is_open()) {
        return false;
    }

    std::string linea;
    if (std::getline(fichero, linea)) {
        eliminarBOM(linea);
    }


    int codigoParque;
    std::string nombreParque;

    while (std::getline(fichero, linea)) {
        if (linea.empty()) {
            continue;
        }

        if (contarCampos(linea) != 2) {
            ++filasDescartadas_;
            continue;
        }

        codigoParque = std::stoi(extraerCampo(linea, 0));
        nombreParque = extraerCampo(linea, 1);
        Parque aInsertar = Parque(codigoParque, nombreParque);

        for (int i = 0; i < arboles.getTamanioLogico(); ++i) {
            if (arboles[i]->getCodigoParque() == codigoParque) {
                aInsertar.insertarArbol(arboles[i]);
            }
        }

        lista.insertaFinal(aInsertar);
    }

    numeroParques_ = lista.getTamLista();
    return true;
}

std::size_t LectorCSV::numeroParques() const {
    return numeroParques_;
}

std::size_t LectorCSV::contarCamposArbol(const std::string& linea) {
    std::size_t numCampos = 1;
    bool dentroComillas = false;
    const std::size_t n = linea.size();

    for (std::size_t i = 0; i < n; ) {
        const char c = linea[i];

        if (dentroComillas) {
            if (c == '"') {
                if (i + 1 < n && linea[i + 1] == '"') {
                    i += 2;
                } else {
                    dentroComillas = false;
                    ++i;
                }
            } else {
                ++i;
            }
        } else if (c == '"') {
            dentroComillas = true;
            ++i;
        } else if (c == ';') {
            ++numCampos;
            ++i;
        } else {
            ++i;
        }
    }

    return numCampos;
}

std::string LectorCSV::extraerCampoArbol(const std::string& linea, std::size_t indiceObjetivo) {
    std::string campo;
    std::size_t indiceActual = 0;
    bool dentroComillas = false;
    const std::size_t n = linea.size();

    for (std::size_t i = 0; i < n; ) {
        const char c = linea[i];

        if (dentroComillas) {
            if (c == '"') {
                if (i + 1 < n && linea[i + 1] == '"') {
                    if (indiceActual == indiceObjetivo) {
                        campo += '"';
                    }
                    i += 2;
                } else {
                    dentroComillas = false;
                    ++i;
                }
            } else {
                if (indiceActual == indiceObjetivo) {
                    campo += c;
                }
                ++i;
            }
        } else if (c == '"') {
            dentroComillas = true;
            ++i;
        } else if (c == ';') {
            if (indiceActual == indiceObjetivo) {
                return campo;
            }
            ++indiceActual;
            ++i;
        } else {
            if (indiceActual == indiceObjetivo) {
                campo += c;
            }
            ++i;
        }
    }

    return campo;
}