#include <iostream>
#include "Nim.h"
using namespace std;

int main()
{
    Nim nim({3,6,7,8});
    auto hijos=nim.expandir();
    nim.muestra();

    for(auto x:hijos)
      x.muestra();

}
