#ifndef NIM_H_INCLUDED
#define NIM_H_INCLUDED
#include <vector>
#include <iostream>
#include <cstdlib>

class Nim
{
public:
   Nim(std::vector<unsigned> posicion_inicial)
   {
	   estado = posicion_inicial;
   }
   std::vector<Nim> expandir();
   void muestra();

private:
	std::vector<unsigned> estado;
};

#endif // NIM_H_INCLUDED
