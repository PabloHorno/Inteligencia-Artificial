#include "reinas.h"
#include "problema_csp.h"
#include "cronometro.h"
#include "tablero.h"

int main()
{
	unsigned dimension = 28;
	reinas::Reinas reinas(dimension);
	Tablero tablero(dimension);
	Cronometro<std::milli> crono;
	crono.inicio();
	if (reinas.resolver(csp::Seleccion_variable::aleatoria, csp::Algoritmo::fc))
	{
		std::cout << "SOLUCION" << std::endl;
		reinas::imprime_solucion(reinas.get_solucion());
		tablero.dibujar_tablero("SOLUCION", reinas.get_solucion());
		std::cout << "\nNODOS VISITADOS= " << reinas.get_nodos_expandidos() << std::endl;
	}
	crono.fin();
	std::cout << "Tiempo empleado: " << crono << " ms." << std::endl;
	std::cout << std::endl;

	return 0;
}
