

#ifndef PR1_VDINAMICO_H
#define PR1_VDINAMICO_H

template<typename T>
class VDinamico {
        unsigned int tamLogico;
        unsigned int tamFisico;
        T* vector;

        /**
         * Metodo que, dado un número, en este caso el tamaño lógico, devuelve la siguiente potencia mayor.
         * \param tamLogico
         *      Tamaño lógico del vector actual.
         * \return
         *      Devuelve la potencia de 2 calculada.
        */
        unsigned int potenciaDeDos(unsigned int tamLogico);

        /**
         * Metodo que, si el tamaño lógico del vector es mayor que el tamaño físico, amplia el tamaño del vector. LLama
         * al metodo potencidDeDos() para hallar el nuevo tamaño, crea un nuevo vector con este tamaño y borra el vector
         * anterior.
         * \param tamLogico
         *      Tamaño logico del vector actual.
        */
        void aumentarTamVector(unsigned int tamLogico);

    public:
        /// Constructores: Por defecto, Parametrizado, Copia y Copia parcial.
        VDinamico();
        VDinamico(unsigned int tamLogico, T &dato);
        VDinamico(const VDinamico& original);
        VDinamico(const VDinamico& original, unsigned int posicionInicial, unsigned int numeroElementos);

        /// Destructor
        ~VDinamico();

        /// Getter y Setter
        unsigned int getTamanioLogico() { return this->tamLogico; }

        /// Operadores
        VDinamico& operator=(const VDinamico& original);
        T& operator[](int posicion);
        bool operator==(const VDinamico& original);
        /**
         * Metodo que inserta un nuevo dato en la posicion indicada. Si el tamaño logico es mayor o igual al fisico,
         * llama a la función aumentarTamVector(). Aumenta el tamaño logico en 1.
         * \param dato
         *      Dato que queremos insertar en el vector.
         * \param posicon
         *      Posicion en la que queremos insertar el dato, si no hay valor, lo insertará al final.
        */
        void insertar(const T& dato, unsigned int posicon = UINT_MAX);

        /**
         * Metodo que disminuye el tamaño lógico en 1, sabiendo que en la siguiente insercción el dato se sobreescribirá
         * y que nunca se consultará ya que no está en el rango del tamaño lógico.
         * \param posicion
         *      Posicion en la que queremos borrar el dato, si no hay valor, se borrará el último dato.
        */
        void eliminar(unsigned int posicion = UINT_MAX);

        /**
         * Metodo que llama a la función sort.
        */
        void ordenar();

        /**
         * Busqueda binaria.
         * \param dato
         *      Dato que queremos buscar
         * \return
         *      Posición donde se encuentra el dato.
        */
        int busquedaDicotomica(const T& dato);

};

#include "VDinamico.cpp"
#endif
