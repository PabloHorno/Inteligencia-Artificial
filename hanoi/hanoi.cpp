#include "hanoi.h"
#include <iostream>

namespace hanoi
{
    unsigned Hanoi::num_clavijas=0; //Inicializa la variable estática, común a todos los nodos Hanoi
    bool Hanoi::operador_valido(unsigned origen,unsigned destino) const
    {
        bool salida=false;
        //A completar
        return salida;
    }
    Hanoi Hanoi::crea_hijo(unsigned origen,unsigned destino) const
    {
        Hanoi hijo(*this); //Copia el padre (*this) en hijo
        //A completar
        return hijo;
    }

    void muestra_estado(const Hanoi& h)
    {
        //No es necesaria hacer esta funcion.
    }
}
