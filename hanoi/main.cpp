#include "hanoi.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    using namespace std;
    hanoi::Hanoi nodo(3);
    muestra_estado(nodo);

    //Crea todos los hijos del nodo h
    //suponiendo que se ha inicializado en el constructor

    std::vector<hanoi::Hanoi> hijos;
    for(int i=0; i<3; ++i)
    {
        for(int j=0; j<3; ++j)
        {
            if(i!=j)
                if(nodo.operador_valido(i,j))
                {
                    hijos.push_back(nodo.crea_hijo(i,j));
                }
        }
    }

    //Muestra los hijos
    for(auto &x:hijos)
        muestra_estado(x);

    return 0;
}
