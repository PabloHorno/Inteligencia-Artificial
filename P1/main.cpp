#include <iostream>
#include <ctime>
#include "taquin.h"

int main()
{
    using namespace std;
    clock_t start = clock();
    unsigned f[]= {1,2,3,4,5,6,7,8,0};
    unsigned i[]= {5,6,7,8,1,2,3,4,0}; //Problema con solución a máxima profundidad
    //unsigned i[]= {8,1,3,4,5,2,6,7,0};
    taquin::Taquin taq(i,f);

    cout<<"EN AMPLITUD\n";
    taq.amplitud();
    taq.solucion();

    cout<<"EN PROFUNDIDAD\n";
    taq.profundidad(31);
    taq.solucion();
    clock_t end = clock();
    double time_elapsed = double(end - start);
    cout<<"Tiempo empleado: "<<time_elapsed/1000<<endl;

}
