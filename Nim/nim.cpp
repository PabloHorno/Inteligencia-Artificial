#include "nim.h"

std::vector<Nim> Nim::expandir()
{
    std::vector<Nim> hijos;
	for (unsigned i = 0; i < std::size(estado); i++)
	{
		Nim hijo(estado);
		unsigned num_bloques = std::size(estado);
		for (unsigned i = 1; i < num_bloques; i++)
		{

		}
	}

    return hijos;
}

void Nim::muestra()
{
	for (auto x : estado)
		std::cout << x << " ";
	std::cout << std::endl;
}
