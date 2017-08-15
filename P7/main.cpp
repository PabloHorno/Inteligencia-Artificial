#include "nodo_reinas.h"
#include "problema_csp.h"
#include <iostream>
#include "tablero.h"
#include "cronometro.h"
int main()
{
    const unsigned dimension=100;
    const size_t iteraciones_max=1000;
    //Opciones de tipo de Nodo
    //Nodo sin set
    nodo_reinas::Nodo_reinas nodo_inicial(dimension, {}); //Vector vacio inicial
    //Nodo con set
    nodo_reinas::Nodo_reinas_set nodo_inicial_set(dimension, {}); //Vector vacio inicial

    problema_csp::Problema_csp<nodo_reinas::Nodo_reinas> problema(nodo_inicial);
    problema_csp::Problema_csp<nodo_reinas::Nodo_reinas_set> problema_set(nodo_inicial_set);

    size_t iteraciones;
	Tablero tablero(dimension);
	Cronometro<std::milli> crono;
    //PROFUNDIDAD SIN SET
   /* if(problema.profundidad())
    {
        std::cout<<"\nPROFUNDIDAD SIN SET\n";
		crono.inicio();
		nodo_reinas::imprime_posicion(problema.get_solucion());
		crono.fin();
		std::cout << "Tiempo empleado " << crono.get_intervalo() << " ms" << std::endl;
		//tablero.dibujar_tablero("PROFUNDIDAD SIN SET", problema.get_solucion().get_posicion());
    }

    //PROFUNDIDAD CON SET
    if(problema_set.profundidad())
    {
        std::cout<<"\nPROFUNDIDAD CON SET\n";
		crono.inicio();
        nodo_reinas::imprime_posicion(problema_set.get_solucion());
		crono.fin();
		std::cout << "Tiempo empleado " << crono.get_intervalo() << " ms" << std::endl;
		//tablero.dibujar_tablero("PROFUNDIDAD CON SET", problema_set.get_solucion().get_posicion());
    }

    iteraciones=iteraciones_max;

    //LAS_VEGAS_EXPANDIR SIN SET
    if(problema.las_vegas_expandir(iteraciones))
    {
        std::cout<<"\nLAS_VEGAS_EXPANDIR SIN SET\n";
		crono.inicio();
        nodo_reinas::imprime_posicion(problema.get_solucion());
		crono.fin();
		std::cout << "Tiempo empleado " << crono.get_intervalo() << " ms" << std::endl;
		//tablero.dibujar_tablero("LAS_VEGAS_EXPANDIR SIN SET", problema.get_solucion().get_posicion());
    }
    std::cout<<"Numero de iteraciones: "<<iteraciones<<"\n";

    //LAS_VEGAS_EXPANDIR CON SET
    iteraciones=iteraciones_max;
    if(problema_set.las_vegas_expandir(iteraciones))
    {
        std::cout<<"\nLAS_VEGAS_EXPANDIR CON SET\n";
		crono.inicio();
        nodo_reinas::imprime_posicion(problema_set.get_solucion());
		crono.fin();
		std::cout << "Tiempo empleado " << crono.get_intervalo() << " ms" << std::endl;
		//tablero.dibujar_tablero("LAS_VEGAS_EXPANDIR CON SET", problema_set.get_solucion().get_posicion());
    }
    std::cout<<"Numero de iteraciones: "<<iteraciones<<"\n";

    //LAS_VEGAS_SUCESOR_ALEATORIO SIN SET
    iteraciones=iteraciones_max;
    if(problema.las_vegas_sucesor_aleatorio(iteraciones))
    {
        std::cout<<"\nLAS VEGAS SUCESOR ALEATORIO SIN SET\n";
		crono.inicio();
        nodo_reinas::imprime_posicion(problema.get_solucion());
		crono.fin();
		std::cout << "Tiempo empleado " << crono.get_intervalo() << " ms" << std::endl;
		//tablero.dibujar_tablero("LAS VEGAS SUCESOR ALEATORIO SIN SET", problema.get_solucion().get_posicion());
    }
    std::cout<<"Numero de iteraciones: "<<iteraciones<<"\n";
	*/
    //LAS_VEGAS_SUCESOR_ALEATORIO CON SET
    iteraciones=iteraciones_max;
    if(problema_set.las_vegas_sucesor_aleatorio(iteraciones))
    {
        std::cout<<"\nLAS VEGAS SUCESOR ALEATORIO CON SET\n";
		crono.inicio();
        nodo_reinas::imprime_posicion(problema_set.get_solucion());
		crono.fin();
		std::cout << "Tiempo empleado " << crono.get_intervalo() << " ms" << std::endl;
		tablero.dibujar_tablero("LAS VEGAS SUCESOR ALEATORIO CON SET", problema_set.get_solucion().get_posicion());
    }
    std::cout<<"Numero de iteraciones: "<<iteraciones<<"\n";
    return 0;
}
