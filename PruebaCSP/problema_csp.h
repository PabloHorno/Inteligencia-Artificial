#ifndef PROBLEMA_CSP_H_INCLUDED
#define PROBLEMA_CSP_H_INCLUDED

#include <vector>
#include <functional>
#include <random>
#include <chrono>
#include <iostream>

namespace csp
{
    template<typename T>
    class Problema_csp
    {
    public:
        Problema_csp() {}

        bool resolver()
        {
            seleccion_variable = [this]() -> unsigned
            {
                return(seleccion_variable_estatica());
            };
            return (backtracking());
        }
        std::vector<std::pair<unsigned,T>>& get_solucion()
        {
            return solucion;
        }
        std::size_t get_nodos_expandidos() const
        {
            return nodos_expandidos;
        }
    protected:
        unsigned num_variables;
        std::vector<std::vector<T>>dominio;
        std::vector<std::pair<unsigned,T>>solucion;
    private:
        std::vector<unsigned>variables_sin_etiquetar; //Vector instrumental que almacena las variables aún fuera de la solución
        unsigned nodos_expandidos; //Para comparar entre algoritmos

        void inicializa();
        //FUNCIONES QUE CARGAN EL DOMINIO Y DESCRIBEN EL GRAFO DE RESTRICCIONES
        //virtuales pues dependen de cada problema particular
        virtual bool consistente(const unsigned variable,const T valor)=0;
        virtual void inicializa_dominio()=0;

        //SELECCION Y BLOQUEO VARIABLE

        std::function<unsigned (void)> seleccion_variable; //Puntero a funcion seleccion_variable
        unsigned seleccion_variable_estatica();
        unsigned seleccion_variable_aleatoria();
        unsigned seleccion_variable_mrv();
        void bloquea_variable();
        void libera_variable(const unsigned variable);

        //ALGORITMOS

        //1) Backtracking
        bool backtracking(); //--> Función general bactracking
        bool expandir_bt(const unsigned variable,std::vector<std::pair<unsigned,T>>& lista_asignaciones);
        virtual void restaura_estado(const std::pair<unsigned,T> &asignacion)=0;  //Llamada virtual diferente para cada problema
        virtual void actualiza_estado(const std::pair<unsigned,T> &asignacion)=0; //Llamada virtual diferente para cada problema

        //GENERADOR ALEATORIOS
        std::mt19937 rng;

        //PARA DEPURACION
        void imprime_dominio();
    };



    template <typename T>
    void Problema_csp<T>::inicializa()
    {
        inicializa_dominio(); //Llamada virtual diferente para cada problema

        //Borra listas

        variables_sin_etiquetar.clear();
        for(unsigned i=0; i!=num_variables; ++i) //Todas las variables sin etiquetar(sin asignar un valor) inicialmente
            variables_sin_etiquetar.push_back(i);

        solucion.clear();
        //Genera semilla para aleatorios
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        rng.seed(seed);
    }

    //Para depuracion
    template <typename T>
    void Problema_csp<T>::imprime_dominio()
    {
        for(unsigned i=0; i!=num_variables(); ++i)
        {
            for(auto j:dominio(i))
            {
                std::cout<<j<<" ";
            }
            std::cout<<std::endl;
        }
    }

#include "csp_seleccion_variable.h"
#include "csp_backtracking.h" //Fichero de plantillas

}
#endif // PROBLEMA_CSP_H_INCLUDED
