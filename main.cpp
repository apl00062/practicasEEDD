#include <fstream>
#include <iostream>
#include <sstream>

#include "eedd/VDinamico.h"
#include "model/Especie.h"
#include "io/LectorCSV.h"
#include <string>


const std::string RUTA_FICHERO_ESPECIES = "data/arbolado-especies.csv";

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


int main()
{
    try
    {
        //INSTANCIAR Y MOSTRAR EL VECTOR DE Especies
        LectorCSV lector_csv;
        VDinamico<Especie> vectorCompleto;
        Especie especie;
        if (!lector_csv.cargar(vectorCompleto, RUTA_FICHERO_ESPECIES))
        {
            std::cerr << "Error: no se pudo abrir el fichero '" << RUTA_FICHERO_ESPECIES << "'.\n";
            std::cerr << "Comprueba que ejecutas el programa desde la raiz del proyecto "
                         "(o revisa el Working Directory en la configuracion de ejecucion).\n";
            return 1;
        }
        std::cout << "Vector leido de fichero"<< std::endl;

        VDinamico<Especie*> vectorEspNComun = getEspNComun(vectorCompleto);

        int practica1;
        int menuPrincipal;

        while (menuPrincipal != 3) {
            std::cout << "--- ELEIGE LA ENTREGA QUE QUIERES COMPROBAR: ---" << std::endl
                << " 1. Practica 1." << std::endl
                << " 2. Practica 2." << std::endl;
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
                                    std::cout<<std::to_string(i+1)<<": "<<vectorCompleto[i].getCodigoEspecie()<<std::endl;
                                }
                                break;

                            case(2):
                                //Ordenación del vector
                                std::cout<<"==================================================="<< std::endl;
                                vectorCompleto.ordenar();
                                std::cout << "Vector ordenado. Mostrar las primeras 50 especies" << std::endl;
                                for (int i = 0; i < 50; i++)
                                {
                                    std::cout<< std::to_string(i+1) << " ";
                                    vectorCompleto[i].mostrarInfo();
                                }
                                break;

                            case(3):
                                //Busqueda de posición de codigos de especies
                                std::cout<<"==================================================="<< std::endl;
                                std::cout << "Posición de códigos de especies: " << std::endl;
                                int posicion;
                                especie.setCodigoEspecie("CTA");
                                posicion = vectorCompleto.busquedaDicotomica(Especie("CTA", "","",""));
                                std::cout << "   Posicion de CTA: " << posicion << std::endl;
                                posicion = vectorCompleto.busquedaDicotomica(Especie("DMD", "","",""));
                                std::cout << "   Posicion de DMD: " << posicion << std::endl;
                                posicion = vectorCompleto.busquedaDicotomica(Especie("HCN", "","",""));
                                std::cout << "   Posicion de HCN: " << posicion << std::endl;
                                posicion = vectorCompleto. busquedaDicotomica(Especie("NDOF", "","",""));
                                std::cout << "   Posicion de NDOF : " << posicion << std::endl;
                                posicion = vectorCompleto.busquedaDicotomica(Especie("JAX", "","",""));
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
                                break;;
                            }
                        }
                        break;

                    case(2):

                        break;

                    case(3):
                        break;

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
