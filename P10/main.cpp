#include "mochila.h"
#include "cronometro.h"
int main()
{
    mochila::Mochila m("24.txt");

    Cronometro<std::milli> crono;

    crono.inicio();
    if(m.resolver(bb::Seleccion_variable::estatica))
    {
        std::cout<<"SOLUCION"<<std::endl;
        m.imprime_solucion();
        std::cout<<"\nNODOS VISITADOS= "<<m.get_nodos_expandidos()<<std::endl;
    }
    crono.fin();
    std::cout<<"Tiempo empleado: "<<crono<<" ms."<<std::endl;
    std::cout<<std::endl;

    return 0;
}
