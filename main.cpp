#include <fstream>
#include <iostream>
#include <sstream>

#include "eedd/VDinamico.h"
#include "model/Especie.h"
#include "io/LectorCSV.h"
#include "eedd/ListaDEnlazada.h"
#include "model/ControlParques.h"
#include "eedd/AVL.h"


const std::string RUTA_FICHERO_ESPECIES = "data/arbolado-especies.csv";
const std::string RUTA_FICHERO_PARQUES = "data/parques.csv";
const std::string RUTA_FICHERO_ARBOLES = "data/arboladoMadrid.csv";

/**
 * @brief Función para encontrar las especies con nombre común no nulo
 * @param vEspecies VDinámico en el que hacer la búsqueda
 * @return VDinámico de punteros a especies en el VDinámico completo
 *          que no tienen nombre común nulo
 */
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
/**void enlazarParques(ControlParques &controlParques) {
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
        VDinamico<Especie*> especies;
        ListaDEnlazada<Parque*> parques;
        AVL<Arbol*> arboles;


        if (!lector_csv.cargarLista(parques, RUTA_FICHERO_PARQUES) ||
            !lector_csv.cargarVector(especies, RUTA_FICHERO_ESPECIES) ||
            !lector_csv.cargarArbol(arboles, RUTA_FICHERO_ARBOLES))
        {
            std::cerr << "Error: no se pudo abrir el fichero '" << RUTA_FICHERO_ESPECIES << "'.\n";
            std::cerr << "Comprueba que ejecutas el programa desde la raiz del proyecto "
                         "(o revisa el Working Directory en la configuracion de ejecucion).\n";
            return 1;
        }
        std::cout << "Numero de Especies cargados: " << especies.getTamanioLogico() << std::endl
                  << "Numero de Parques cargados: " << parques.getTamLista() << std::endl
                  << "Numero de Arboles cargados: "  << arboles.getNumElementos() << std::endl
                  << "Altura del árbol AVL: " << arboles.getAltura() << std::endl;


        ControlParques controlParques(especies, parques, arboles);
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
                                /**Busqueda de posición de codigos de especies
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
                                /**case (2):
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
