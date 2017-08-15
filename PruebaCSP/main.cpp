#include "prueba_csp.h"
#include "problema_csp.h"
#include "cronometro.h"
int main()
{
    prueba_csp::Prueba_csp p;
    Cronometro<std::milli> crono;

    crono.inicio();
    //Solo se implementa Backtracking y seleccion variable estatica
    if(p.resolver())
    {
       std::cout<<"SOLUCION"<<std::endl;
       prueba_csp::imprime_solucion(p.get_solucion());
       std::cout<<"\nNODOS VISITADOS= "<<p.get_nodos_expandidos()<<std::endl;
    }
    crono.fin();
    std::cout<<"Tiempo empleado: "<<crono<<" ms."<<std::endl;
    std::cout<<std::endl;

    return 0;
}
