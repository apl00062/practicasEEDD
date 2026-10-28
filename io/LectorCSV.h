#ifndef LECTOR_CSV_H
#define LECTOR_CSV_H

#include <cstddef>
#include <string>

#include "../model/Especie.h"
#include "../model/Parque.h"
#include "../model/Arbol.h"
#include "../eedd//VDinamico.h"
#include "../eedd/ListaDEnlazada.h"
#include "../eedd/AVL.h"

// Lee el fichero data/arbolado-especies.csv: valores separados por comas,
// donde un valor puede ir entrecomillado y contener comas y comillas
// escapadas ("") dentro de las comillas (formato tipo RFC4180). Asume que
// cada fila lógica ocupa una única línea física del fichero.
//
// No almacena las especies leídas: cada una se construye y se muestra por
// pantalla en el momento en que se lee, y se descarta a continuación. No
// utiliza std::vector ni ninguna otra estructura de datos en ningún punto.
class LectorCSV {
public:
    bool cargarVector(VDinamico<Especie*> &vector, const std::string& rutaFichero);
    bool cargarLista(ListaDEnlazada<Parque*> &lista, const std::string& rutaFichero);
    bool cargarArbol(AVL<Arbol*> &arbol, const std::string& rutaFichero);

    std::size_t numeroEspecies() const;
    std::size_t filasDescartadas() const;
    std::size_t numeroParques() const;

private:
    VDinamico<Especie*> vectorEspecie;

    std::size_t numeroEspecies_ = 0;
    std::size_t filasDescartadas_ = 0;
    std::size_t numeroParques_ = 0;
    std::size_t numeroArboles_ = 0;

    static std::size_t contarCampos(const std::string& linea);
    static std::size_t contarCamposArbol(const std::string& linea);
    static std::string extraerCampo(const std::string& linea, std::size_t indiceObjetivo);
    static std::string extraerCampoArbol(const std::string& linea, std::size_t indiceObjetivo);
    static void eliminarBOM(std::string& linea);
    static void mostrarEspecie(const Especie& especie);
};

#endif // LECTOR_CSV_H
