//FELIX MIGUEL TRESPADERNE
//INTELIGENCIA ARTIFICIAL APLICADA AÑO 2017
//Inspirado en Simulated Annealing Methods, sección 10.9 del libro
//NUMERICAL RECIPES IN C


#include "recocido_simulado_tsp.h"
double get_distancia_media(ruta::Ruta& ruta);
void Recocido_simulado_TSP::inicializacion(ruta::Ruta& ruta, const double probabilidad)
{
	//A completar: esta función debe modificarse para que sintonice los parámetros de forma automática
	num_descensos = ruta.get_num_ciudades() * 100;
	num_permutaciones = ruta.get_num_ciudades() * 1000;
	num_exitos_maximo = 2000;
	temperatura = -get_distancia_media(ruta)*1000. / log(probabilidad);
	factor_descenso = 0.99;
	std::cout << "INICIALIZACION" << std::endl;
	std::cout << "temperatura = " << temperatura << std::endl;
}
double get_distancia_media(ruta::Ruta& ruta)
{
	double media = 0;
	for (unsigned i = 0; i < ruta.get_num_ciudades()*0.3; i++)
	{
		std::pair<double, double> distancias;
		ruta.inicializa_recorrido();
		distancias.first = ruta.get_distancia_actual();

		ruta.inicializa_recorrido();
		distancias.second = ruta.get_distancia_actual();
		media += distancias.first - distancias.second;
	}
	media = abs(media / ((unsigned)ruta.get_num_ciudades()*0.3));
	return media;
}
// Calcula una ruta mediante recocido simulado
void Recocido_simulado_TSP::ejecutar(ruta::Ruta& ruta)
{
	std::mt19937 rng;
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	rng.seed((unsigned)seed);
	std::uniform_real_distribution<double> aleatorio_0_a_1(0, 1);

	//A completar: el alumno invocará desde aquí a inicializacion para
	//sintonizar los parametros del algoritmo
	inicializacion(ruta);
	ruta.inicializa_recorrido();
	auto distancia_actual = ruta.get_distancia_actual();
	mejor_distancia = distancia_actual;
	iteracion_actual = 0;
	mejor_recorrido = ruta.get_recorrido();

	observador.notifica(Evento_Modelo::nuevo_recorrido);

	abortar = false;

	for (; iteracion_actual < num_descensos; ++iteracion_actual)
	{
		unsigned num_exitos = 0;
		for (unsigned j = 0; j < num_permutaciones; j++)
		{
			if (abortar)
			{
				return;
			}
			ruta.crea_recorrido_vecino();

			auto distancia_provisional = ruta.get_distancia_provisional();
			auto incremento = distancia_provisional - distancia_actual;

			int indice_incremento = incremento / temperatura;

			if (incremento < 0 || (indice_incremento < 10 && aleatorio_0_a_1(rng) < look_up_table[indice_incremento])) //DECISON METROPOLIS
			{
				//Actualizamos la ruta actual
				ruta.actualiza_ruta();
				distancia_actual = distancia_provisional;

				if (distancia_actual < mejor_distancia)
				{  //Notificamos al Controlador
					mejor_distancia = distancia_actual;
					mejor_recorrido = ruta.get_recorrido();
					observador.notifica(Evento_Modelo::nuevo_recorrido);
				}
				if (++num_exitos > num_exitos_maximo)
					break;
			}
		}
		if (num_exitos == 0)
			break;
		temperatura *= factor_descenso;
	}
}
void Recocido_simulado_TSP::inicializar_look_up_table()
{
	std::cout << "Preparando LUT..." << std::endl;
	for (unsigned i = 0; i < tam_look_up_table; ++i)
		look_up_table.push_back(1 / exp((i*10. / tam_look_up_table)));
	std::cout << "Fin LUT." << std::endl;
}
