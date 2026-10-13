#include <fstream>
#include <iostream>
#include <sstream>

#include "eedd/VDinamico.h"
#include "model/Especie.h"
#include "io/LectorCSV.h"
#include "eedd/ListaDEnlazada.h"
#include "model/ControlParques.h"


const std::string RUTA_FICHERO_ESPECIES = "data/arbolado-especies.csv";
const std::string RUTA_FICHERO_PARQUES = "data/parques.csv";

/**
 * @brief Función para encontrar las especies con nombre común no nulo
 * @param vEspecies VDinámico en el que hacer la búsqueda
 * @return VDinámico de punteros a especies en el VDinámico completo
 *          que no tienen nombre común nulo
 */
VDinamico<Especie*> getEspNComun(VDinamico<Especie>& vEspecies)
{
    VDinamico<Especie*> vectorEspNComun;
    for ( int i = 0; i < vEspecies.getTamanioLogico(); ++i) {
        if (vEspecies[i].getNombreComun() != "") {
            vectorEspNComun.insertar(&vEspecies[i]);
        }
    }
    return vectorEspNComun;
}

/// ================= Operaciones para la prueba 1 de la Lista Doblemente Enlazada ===================
void insertarAlFinalLista(ListaDEnlazada<int> &enteros) {
    for (int i = 101; i <= 200; ++i)
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

void imprimirPorPantalla(ListaDEnlazada<int> &enteros) {
    Iterador<int> iterador = enteros.getIterador();
    while (iterador.haySiguiente()) {
        std::cout << "Numero: " << iterador.dato() << std::endl;
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
            for (int j = 1; j < controlParques.getTamParques(); j += 2) {
                std::cout << controlParques.getParque(j)->getNombreParque() << std::endl;
                std::cout << controlParques.getEspecie(i)->getTipoPlanta() << std::endl;

                controlParques.asignarEspecieParque(*controlParques.getEspecie(i), *controlParques.getParque(j));
            }
        }
        else {
            for (int j = 0; j < controlParques.getTamParques(); j += 2) {
                controlParques.asignarEspecieParque(*controlParques.getEspecie(i), *controlParques.getParque(j));
            }
        }
    }
}

int main()
{
    try
    {
        //INSTANCIAR Y MOSTRAR EL VECTOR DE Especies
        LectorCSV lector_csv;
        VDinamico<Especie> vectorCompletoPr1;
        VDinamico<Especie> vectorCompleto;
        ListaDEnlazada<int> enteros;
        ListaDEnlazada<Parque> listaParques;
        Especie especie;


        if (!lector_csv.cargarVector(vectorCompletoPr1, RUTA_FICHERO_ESPECIES) ||
            !lector_csv.cargarLista(listaParques, RUTA_FICHERO_PARQUES) ||
            !lector_csv.cargarVector(vectorCompleto, RUTA_FICHERO_ESPECIES))
        {
            std::cerr << "Error: no se pudo abrir el fichero '" << RUTA_FICHERO_ESPECIES << "'.\n";
            std::cerr << "Comprueba que ejecutas el programa desde la raiz del proyecto "
                         "(o revisa el Working Directory en la configuracion de ejecucion).\n";
            return 1;
        }
        std::cout << "Vector leido de fichero"<< std::endl;
        std::cout << "Lista leida de fichero" << std::endl;


        VDinamico<Especie*> vectorEspNComun = getEspNComun(vectorCompletoPr1);

        vectorCompleto.ordenar();

        ControlParques controlParques(vectorCompleto, listaParques);

        int menuPrincipal = 0;

        while (menuPrincipal < 3) {
            int practica1 = 0;
            int practica2 = 0;
            std::cout << "--- ELEIGE LA ENTREGA QUE QUIERES COMPROBAR: ---" << std::endl
                << " 1. Practica 1." << std::endl
                << " 2. Practica 2." << std::endl
                << " 3. Salir. " << std::endl;
            std::cin >> menuPrincipal;
            switch (menuPrincipal) {
                case(1):
                    while (practica1 != 5) {
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
                                    std::cout<<std::to_string(i+1)<<": "<<vectorCompletoPr1[i].getCodigoEspecie()<<std::endl;
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
                                    vectorCompletoPr1[i].mostrarInfo();
                                }
                                break;

                            case(3):
                                //Busqueda de posición de codigos de especies
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
                            std::cout << "--- Practica 2 ---" << std::endl
                                << " 1. Prueba con Enteros. " << std::endl
                                << " 2. Prueba con Control de Parques." << std::endl;
                            std::cin >> practica2;
                            switch (practica2) {
                                case(1): {
                                    insertarAlFinalLista(enteros);
                                    std::cout << " 1. Valores crecientes desde 101 a 200. " << std::endl;
                                    imprimirPorPantalla(enteros);
                                    insertarAlPrincipioLista(enteros);
                                    std::cout << " 2. Decrecientes desde 98 a 1. " << std::endl;
                                    imprimirPorPantalla(enteros);
                                    insertarDelanteLista(enteros);
                                    std::cout << " 3. Insertar el dato 100 delante del 101. " << std::endl;
                                    imprimirPorPantalla(enteros);
                                    insertarDetrasLista(enteros);
                                    std::cout << " 4. Insertar el dato 99 detras del 98. " << std::endl;
                                    imprimirPorPantalla(enteros);
                                    borrarPrimerosYUltimos(enteros);
                                    std::cout << " 5. Borrar los 10 primeros y los 10 ultimos. " << std::endl;
                                    imprimirPorPantalla(enteros);
                                    borrarMultiplosDiez(enteros);
                                    std::cout << " 6. Borrar los multiplos de 10. " << std::endl;
                                    imprimirPorPantalla(enteros);
                                    break;
                            }
                                case (2):
                                    enlazarParques(controlParques);
                                    /**
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
                                    VDinamico<Especie*> subCadenaRosa = controlParques.listadoEspecieSubNombre("Rosa");
                                    for (int i = 0; i < controlParques.getTamEspecies(); ++i) {
                                        std::cout << "Especie: " << subCadenaRosa[i]->getNombreCientfico();
                                    }**/
                                    break;
                        }
                        break;

                    case(3):
                        break;
                    }
                }
            }
    }
    catch (const std::exception& e)
    {
        std::cerr << std::endl << "main.cpp -> " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
