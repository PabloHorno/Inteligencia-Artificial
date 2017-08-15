#include <chrono>
#include <random>

namespace problema_csp
{
	//iteraciones tiene a la entrada el límite de iteraciones.
	//A la salida las iteraciones realizadas
	template<typename T>
	bool Problema_csp<T>::las_vegas_expandir(size_t &iteraciones)
	{
		std::mt19937 rng;
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		rng.seed(seed); //¿Qué pasa si se comenta esta línea? No generamos semilla diferente en cada inicio del programa, obtenemos mismos aleatorios.

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

				std::vector<T> hijos = nodo.expandir();
				if (!hijos.size()) {
					nodo = nodo_inicial;
					iteraciones++;
				}
				else
				{
					nodos_expandidos += hijos.size();
					std::uniform_int_distribution<unsigned>aleatorio(0, hijos.size() - 1);
					nodo = hijos[aleatorio(rng)];
					if (iteraciones > limite_iteraciones)
						break;
				}
			}
		}
		if (exito)
		{
			nodo_solucion = nodo;
		}
		return exito;
	}
}
