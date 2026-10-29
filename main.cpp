#include <fstream>
#include <iostream>
#include <sstream>

#include "eedd/VDinamico.h"
#include "model/Especie.h"
#include "io/LectorCSV.h"
#include "eedd/ListaDEnlazada.h"
#include "model/ControlParques.h"
#include "eedd/AVL.h"



/**
 * @brief Función para encontrar las especies con nombre común no nulo
 * @param vEspecies VDinámico en el que hacer la búsqueda
 * @return VDinámico de punteros a especies en el VDinámico completo
 *          que no tienen nombre común nulo
 */
/**
VDinamico<Especie*> getEspNComun(VDinamico<Especie*>& vEspecies)
{
    VDinamico<Especie*> vectorEspNComun;
    for ( int i = 0; i < vEspecies.getTamanioLogico(); ++i) {
        if (vEspecies[i]->getNombreComun() != "") {
            vectorEspNComun.insertar(vEspecies[i]);
        }
    }
    return vectorEspNComun;
}

/// ================= Operaciones para la prueba 1 de la Lista Doblemente Enlazada ===================
void insertarAlFinalLista(ListaDEnlazada<int> &enteros) {
    for (int i = 101; i < 200; ++i)
        enteros.insertaFinal(i);
}

void insertarAlPrincipioLista(ListaDEnlazada<int> &enteros) {
    for (int i = 98; i >= 1; --i)
        enteros.insertaInicio(i);
}

void insertarDelanteLista(ListaDEnlazada<int> &enteros) {
    Iterador<int> iterador = enteros.getIterador();
    while (iterador.dato() != 101)
        iterador.aSiguiente();

    int aInsertar = 100;
    enteros.insertar(iterador,aInsertar);
}

void insertarDetrasLista(ListaDEnlazada<int> &enteros) {
    Iterador<int> iterador = enteros.getIterador();
    while (iterador.dato() != 98)
        iterador.aSiguiente();

    int aInsertar = 99;
    enteros.insertar(iterador, aInsertar);
}

void borrarPrimerosYUltimos(ListaDEnlazada<int> &enteros) {
    for (int i = 0; i < 10; ++i) {
        enteros.borraFinal();
        enteros.borraInicio();
    }
}

void borrarMultiplosDiez(ListaDEnlazada<int> &enteros) {
    Iterador<int> iterador = enteros.getIterador();
    while (iterador.haySiguiente()) {
        if (iterador.dato()%10 == 0)
            enteros.borrar(iterador);
        else
            iterador.aSiguiente();
    }
}

void imprimirPorPantalla(ListaDEnlazada<int> &enteros, int id, std::string titulo) {
    std::string idS = std::to_string(id);
    std::ofstream archivo("data/numerosListas"+idS+".txt");
    archivo << titulo << std::endl;
    Iterador<int> iterador = enteros.getIterador();
    std::cout << "Archivo Numero Listas " << id << " creado." << std::endl;
    while (iterador.haySiguiente()) {
        archivo << "Numero: " << iterador.dato() << std::endl;
        iterador.aSiguiente();
    }
}

/// ===================================================================================

/// ======================== Operaciones para la prueba 2 de la Lista Doblemente Enlazada ===========================
void enlazarParques(ControlParques &controlParques) {
    for (int i = 0; i < controlParques.getTamEspecies(); ++i) {
        if (controlParques.getEspecie(i)->getTipoPlanta() == "ARBUSTO" ||
            controlParques.getEspecie(i)->getTipoPlanta() == "CONIFERA" ||
            controlParques.getEspecie(i)->getTipoPlanta() == "PALMACEA" ||
            controlParques.getEspecie(i)->getTipoPlanta() == "HERB_PERENNES" ||
            controlParques.getEspecie(i)->getTipoPlanta() == "FRONDOSA") {

            for (int j = 2; j <= controlParques.getTamParques(); j += 2) {
                controlParques.asignarEspecieParque(*controlParques.getEspecie(i), *controlParques.getParque(j));
            }
        }
        else {
            for (int j = 1; j < controlParques.getTamParques(); j += 2) {
                controlParques.asignarEspecieParque(*controlParques.getEspecie(i), *controlParques.getParque(j));
            }
        }
    }
}
**/
int main()
{
    try
    {
        //INSTANCIAR Y MOSTRAR EL VECTOR DE Especies
        LectorCSV lector_csv;
        ControlParques controlParques(lector_csv);

        std::cout << "-- EJERCICIO Nº1 --" << std::endl
                  << "Numero de Especies cargados: " << controlParques.getTamEspecies() << std::endl
                  << "Numero de Parques cargados: " << controlParques.getTamParques() << std::endl
                  << "Numero de Arboles cargados: "  << controlParques.getTamArboles() << std::endl
                  << "Altura del árbol AVL: " << controlParques.getAlturaArbol() << std::endl << std::endl;


        Arbol* aMostrar1 = controlParques.buscarArbol("9850684");
        Arbol* aMostrar2 = controlParques.buscarArbol("5702331");
        Arbol* aMostrar3 = controlParques.buscarArbol("5697360");
        Arbol* aMostrar4 = controlParques.buscarArbol("0000000");

        std::cout << "-- EJERCICIO Nº2 --" << std::endl;
        if (aMostrar1 == nullptr)
            std::cout << "El arbol 9850684 no existe. " << std::endl;
        else {
            std::cout << "El arbol 9850684 existe, y tiene los siguientes atributos: " << std::endl
                      << "Identificador: " << aMostrar1->getAssetNum() << std::endl
                      << "Codigo del Parque: " << aMostrar1->getCodigoParque() << std::endl
                      << "Nombre común: " << aMostrar1->getNombreComun() << std::endl
                      << "Nombre científico: " << aMostrar1->getNombreCientifico() << std::endl
                      << "Tipo de Planta: " << aMostrar1->getTipoPlanta() << std::endl << std::endl;
        }
        if (aMostrar2 == nullptr)
            std::cout << "El arbol 5702331 no existe. " << std::endl;
        else {
            std::cout << "El arbol 5702331 existe, y tiene los siguientes atributos: " << std::endl
                      << "Identificador: " << aMostrar2->getAssetNum() << std::endl
                      << "Codigo del Parque: " << aMostrar2->getCodigoParque() << std::endl
                      << "Nombre común: " << aMostrar2->getNombreComun() << std::endl
                      << "Nombre científico: " << aMostrar2->getNombreCientifico() << std::endl
                      << "Tipo de Planta: " << aMostrar2->getTipoPlanta() << std::endl << std::endl;
        }
        if (aMostrar3 == nullptr)
            std::cout << "El arbol 5697360 no existe. " << std::endl;
        else {
            std::cout << "El arbol 5697360 existe, y tiene los siguientes atributos: " << std::endl
                      << "Identificador: " << aMostrar3->getAssetNum() << std::endl
                      << "Codigo del Parque: " << aMostrar3->getCodigoParque() << std::endl
                      << "Nombre común: " << aMostrar3->getNombreComun() << std::endl
                      << "Nombre científico: " << aMostrar3->getNombreCientifico() << std::endl
                      << "Tipo de Planta: " << aMostrar3->getTipoPlanta() << std::endl << std::endl;
        }
        if (aMostrar4 == nullptr)
            std::cout << "El arbol 0000000 no existe. " << std::endl << std::endl;
        else {
            std::cout << "El arbol 0000000 existe, y tiene los siguientes atributos: " << std::endl
                      << "Identificador: " << aMostrar4->getAssetNum() << std::endl
                      << "Codigo del Parque: " << aMostrar4->getCodigoParque() << std::endl
                      << "Nombre común: " << aMostrar4->getNombreComun() << std::endl
                      << "Nombre científico: " << aMostrar4->getNombreCientifico() << std::endl
                      << "Tipo de Planta: " << aMostrar4->getTipoPlanta() << std::endl << std::endl;
        }

        VDinamico<Arbol*> ejercicio3 = controlParques.listadoArbolesParque("JARDINES DEL BUEN RETIRO");
        std::cout <<"-- Ejercicio Nº3 --" << std::endl;
        for (int i = 0; i < 10; ++i)
        {
            std::cout << "Identificador del arbol n" << i+1 << ": " << ejercicio3[i]->getAssetNum() << std::endl;
            std::cout << "Numero de Parque: " << ejercicio3[i]->getNumParque() << std::endl;
            std::cout << "Nombre del Distrito: " << ejercicio3[i]->getNombreDistrito() << std::endl << std::endl;
        }
/**
        int menuPrincipal = 0;

        while (menuPrincipal < 4) {
            int practica1 = 0;
            int practica2 = 0;
            int practica3 = 0;
            std::cout << "--- ELEIGE LA ENTREGA QUE QUIERES COMPROBAR: ---" << std::endl
                << " 1. Practica 1." << std::endl
                << " 2. Practica 2." << std::endl
                << " 3. Practica 3." << std::endl
                << " 4. Salir. " << std::endl;
            std::cin >> menuPrincipal;
            switch (menuPrincipal) {
                case(1):
                    while (practica1 != 5) {
                        practica1 = 0;
                        std::cout << "--- PRÁCTICA 1 ---" << std::endl
                            << " 1. Mostrar los 50 primeros identificadores." << std::endl
                            << " 2. Mostrar los 50 primeros identificadores, una vez ordenados." << std::endl
                            << " 3. Busqueda de posicion de codigos de especies (Busqueda binaria)." << std::endl
                            << " 4. Busqueda de nombre comun no nulo." << std::endl
                            << " 5. Volver Atrás." << std::endl;
                        std::cin >> practica1;

                        switch(practica1) {
                            case(1):
                                //Mostrar los 50 primeros identificadores
                                std::cout<<"==================================================="<< std::endl;
                                std::cout << "Identificador de las primeras 50 especies" << std::endl;
                                for (int i = 0; i < 50; ++i)
                                {
                                    std::cout<<std::to_string(i+1)<<": "<<vectorCompletoPr1[i]->getCodigoEspecie()<<std::endl;
                                }
                                break;

                            case(2):
                                //Ordenación del vector
                                std::cout<<"==================================================="<< std::endl;
                                vectorCompletoPr1.ordenar();
                                std::cout << "Vector ordenado. Mostrar las primeras 50 especies" << std::endl;
                                for (int i = 0; i < 50; i++)
                                {
                                    std::cout<< std::to_string(i+1) << " ";
                                    vectorCompletoPr1[i]->mostrarInfo();
                                }
                                break;

                            case(3):
                                Busqueda de posición de codigos de especies
                                std::cout<<"==================================================="<< std::endl;
                                std::cout << "Posición de códigos de especies: " << std::endl;
                                int posicion;
                                especie.setCodigoEspecie("CTA");
                                posicion = vectorCompletoPr1.busquedaDicotomica(Especie("CTA", "","",""));
                                std::cout << "   Posicion de CTA: " << posicion << std::endl;
                                posicion = vectorCompletoPr1.busquedaDicotomica(Especie("DMD", "","",""));
                                std::cout << "   Posicion de DMD: " << posicion << std::endl;
                                posicion = vectorCompletoPr1.busquedaDicotomica(Especie("HCN", "","",""));
                                std::cout << "   Posicion de HCN: " << posicion << std::endl;
                                posicion = vectorCompletoPr1. busquedaDicotomica(Especie("NDOF", "","",""));
                                std::cout << "   Posicion de NDOF : " << posicion << std::endl;
                                posicion = vectorCompletoPr1.busquedaDicotomica(Especie("JAX", "","",""));
                                std::cout << "   Posicion de JAX: " << posicion << std::endl;

                                break;

                            case(4):
                                //Búsqueda de Nombre común no nulo
                                std::cout<<"==================================================="<<std::endl;
                                std::cout << "Nombre comun no nulo" << std::endl;
                                std::cout<<"Numero de elemntos no nulos: "<<vectorEspNComun.getTamanioLogico()<< std::endl;
                                for (int i = 0; i < vectorEspNComun.getTamanioLogico(); i++)
                                {
                                    std::cout<< std::to_string(i+1) << " ";
                                    vectorEspNComun[i]->mostrarInfo();
                                }
                                break;

                            case(5):
                                break;
                            }
                        }
                        break;

                    case(2):
                        while (practica2 < 3) {
                            practica2 = 0;
                            std::cout << "--- Practica 2 ---" << std::endl
                                << " 1. Prueba con Enteros. " << std::endl
                                << " 2. Prueba con Control de Parques. (Ya no se puede acceder, las fuciones han cambiado)" << std::endl
                                << " 3. Volver Atrás." << std::endl;
                            std::cin >> practica2;
                            switch (practica2) {
                                case(1): {
                                    int id = 1;
                                    std::string insertar;
                                    insertarAlFinalLista(enteros);
                                    insertar = " === 1. Valores crecientes desde 101 a 200. ===";
                                    imprimirPorPantalla(enteros, id, insertar);
                                    id++;
                                    insertarAlPrincipioLista(enteros);
                                    insertar = " === 2. Decrecientes desde 98 a 1. === ";
                                    imprimirPorPantalla(enteros, id, insertar);
                                    id++;
                                    insertarDelanteLista(enteros);
                                    insertar = " === 3. Insertar el dato 100 delante del 101. === ";
                                    imprimirPorPantalla(enteros, id, insertar);
                                    id++;
                                    insertarDetrasLista(enteros);
                                    insertar = " === 4. Insertar el dato 99 detras del 98. ===";
                                    imprimirPorPantalla(enteros, id, insertar);
                                    id++;
                                    borrarPrimerosYUltimos(enteros);
                                    insertar = " === 5. Borrar los 10 primeros y los 10 ultimos. ===";
                                    imprimirPorPantalla(enteros, id, insertar);
                                    id++;
                                    borrarMultiplosDiez(enteros);
                                    insertar = " === 6. Borrar los multiplos de 10. ===";
                                    imprimirPorPantalla(enteros, id, insertar);
                                    break;
                            }
                                case (2):
                                    enlazarParques(controlParques);

                                    std::cout << "=== Prueba 1. Nombres Comunes ===" << std::endl;
                                    if (controlParques.buscarParque("PARQUE PRINCESA LEONOR")->
                                                existeNombreComun("Eucalipto rojo"))
                                        std::cout << "El Parque Princesa Leonor, SI contiene la especie Eucalipto Rojo."
                                                  << std::endl;
                                    else
                                        std::cout << "El Parque Princesa Leonor, NO contiene la especie Eucalipto Rojo."
                                                  << std::endl;

                                    if (controlParques.buscarParque("PARQUE PRINCESA LEONOR")->
                                                existeNombreComun("Arce de Sierra"))
                                        std::cout << "El Parque Princesa Leonor, SI contiene la especie Arce de Sierra."
                                                  << std::endl;
                                    else
                                        std::cout << "El Parque Princesa Leonor, NO contiene la especie Arce de Sierra."
                                                  << std::endl;


                                    std::cout << " === Prueba 2. Nombres Cientificos ===" << std::endl;
                                    if (controlParques.buscarParque("PARQUE MADRID RIO")->
                                                existeNombreCientifico("Hebe floribunda"))
                                        std::cout << "El Parque Madrid Rio, SI contiene la especie Hebe floribunda."
                                                  << std::endl;
                                    else
                                        std::cout << "El Parque Madrid Rio, NO contiene la especie Hebe floribunda."
                                                  << std::endl;

                                    if (controlParques.buscarParque("PARQUE MADRID RIO")->
                                                existeNombreComun("Ananas camosa"))
                                        std::cout << "El Parque Madrid Rio, SI contiene la especie Ananas camosa."
                                                  << std::endl;
                                    else
                                        std::cout << "El Parque Madrid Rio, NO contiene la especie Ananas camosa."
                                                  << std::endl;

                                    std::cout << "=== Prueba 3. Busqueda de Parques ===" << std::endl;
                                    if (controlParques.buscarParque("PARQUE JUAN CARLOS III") == nullptr)
                                        std::cout << "El Parque Juan Carlos III, no existe." << std::endl;
                                    else
                                        std::cout << "El Parque Juan Carlos III, tiene el codigo: "
                                                  << controlParques.buscarParque("PARQUE JUAN CARLOS III")->getCodigoParque()
                                                  << std::endl;
                                    if (controlParques.buscarParque("VIVERO DE MIGAS CALIENTES") == nullptr)
                                        std::cout << "El Parque Vivero de Migas Calientes, no existe." << std::endl;
                                    else
                                        std::cout << "El Parque Vivero de Migas Calientes, tiene el codigo: "
                                                  << controlParques.buscarParque("VIVERO DE MIGAS CALIENTES")->getCodigoParque()
                                                  << std::endl;

                                    std::cout << "=== Prueba 4. Subcadena Rosa ===" << std::endl;
                                    std::ofstream archivo("data/especiesRosa.txt");
                                    VDinamico<Especie*> subCadenaRosa = controlParques.listadoEspecieSubNombre("Rosa");
                                    for (int i = 0; i < subCadenaRosa.getTamanioLogico(); ++i) {
                                        archivo << "Especie: " << subCadenaRosa[i]->getNombreCientfico() << std::endl;
                                    }
                                    std::cout << " Archivo especies Rosa creado." << std::endl;
                                    archivo.close();

                                    std::cout << "=== Prueba 5. Parques que contienen Abetos ===" << std::endl;
                                    std::cout << controlParques.contarEspecieParque("Abeto") << std::endl;
                                    break;

                        }
                        break;

                    case(3):
                        while (practica3 < 2) {

                        }

                    case(4):
                         break;
                    }
                }
            }
            */


    }
    catch (const std::exception& e)
    {
        std::cerr << std::endl << "main.cpp -> " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
