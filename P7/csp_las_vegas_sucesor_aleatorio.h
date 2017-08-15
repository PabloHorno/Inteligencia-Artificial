#include <chrono>
#include <random>

namespace problema_csp
{
	//iteraciones tiene a la entrada el límite de iteraciones.
	//A la salida las iteraciones realizadas
	template<typename T>
	bool Problema_csp<T>::las_vegas_sucesor_aleatorio(size_t &iteraciones)
	{
		std::mt19937 rng;
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		rng.seed(seed); //¿Qué pasa si se comenta esta línea?

		T nodo(nodo_inicial);

		bool exito = false;
		nodos_expandidos = 0;

		const auto limite_iteraciones = iteraciones;
		iteraciones = 0;
		while (exito == false)
		{
			exito = nodo.prueba_meta(); //Prueba de meta
			if (!exito)
			{
				if (!nodo.sucesor_aleatorio(rng)) {
					nodo = nodo_inicial;
					iteraciones++;
				}
				else
					++nodos_expandidos;

				if (iteraciones > limite_iteraciones)
					break;
			}
		}
		if (exito)
		{
			nodo_solucion = nodo;
		}
		return exito;
	}
}
