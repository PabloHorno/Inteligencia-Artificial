#include "ruta.h"
#include <algorithm>
namespace ruta
{
	double Ruta::calcula_distancia(const std::vector<unsigned>& recorrido)
	{
		return(ciudades.calcula_distancia(recorrido));
	}

	void Ruta::insercion_segmento()
	{
		recorrido_provisional = recorrido_actual;
		unsigned p[3] = { aleatorio_num_ciudades_mas_1(rng),0,0 };

		while (p[0] == p[1] || p[0] == p[2] || p[1] == p[2])
			for (unsigned i = 1; i < std::size(p); i++)
				p[i] = aleatorio_num_ciudades_mas_1(rng);

		std::sort(p, p + std::size(p));

		auto aleatorio = aleatorio_0_a_1(rng);
		if (aleatorio < 0.25)	//Insertará el segmento p1p2 en la posición p3
			mover_segmento(p[0], p[1], p[2]);
		else if (aleatorio < 0.5)	//Insertará el segmento p2p1 en la posición p3
			mover_segmento(p[1], p[0], p[2]);
		else if (aleatorio < 0.75)	//Insertará el segmento p2p3 en la posición p1
			mover_segmento(p[1], p[2], p[0]);
		else	//Insertará el segmento p3p2 en la posición p1
			mover_segmento(p[2], p[1], p[0]);

		distancia_provisional = calcula_distancia(recorrido_provisional);
	}
	void Ruta::mover_segmento(const unsigned p1, const unsigned p2, const unsigned p3)
	{
		auto it1 = recorrido_provisional.begin() + p1;
		auto it2 = recorrido_provisional.begin() + p2;
		auto it3 = recorrido_provisional.begin() + p3;

		if (it1 > it2)
		{
			std::swap(it1, it2);
			std::reverse(it1, it2);
		}
		if (it3 > it1)
			std::rotate(it1, it2, it3);
		else {
			std::vector<unsigned> aux = std::vector<unsigned>(it1,it2);
			recorrido_provisional.erase(it1, it2);
			recorrido_provisional.insert(it3, aux.begin(), aux.end());
		}
	}
	// Elige una sección dada por 3 puntos de la ruta y la rota
	// pasando el punto intermedio a ser el primero
	void Ruta::rotacion_3_puntos()
	{
		// Copiamos recorrido actual en el posible nuevo recorrido
		recorrido_provisional = recorrido_actual;
		unsigned c[3];

		//Elegimos aleatoriamente 3 indices de ciudades
		c[0] = aleatorio_num_ciudades(rng);
		c[1] = aleatorio_num_ciudades(rng);
		c[2] = aleatorio_num_ciudades(rng);

		//Exigimos que sean distintos
		while ((c[0] == c[1] ||
			c[0] == c[2] ||
			c[1] == c[2]))
		{
			c[0] = aleatorio_num_ciudades(rng);
			c[1] = aleatorio_num_ciudades(rng);
			c[2] = aleatorio_num_ciudades(rng);
		}
		//Los ordenamos de menor a mayor
		std::sort(c, c + 3);

		//Ejecutamos la rotacion
		auto it1 = recorrido_provisional.begin() + c[0];
		auto it2 = recorrido_provisional.begin() + c[1];
		auto it3 = recorrido_provisional.begin() + c[2];
		std::rotate(it1, it2, it3);
		distancia_provisional = calcula_distancia(recorrido_provisional);
	}

	// Elige una sección dada por 2 puntos de la ruta y la rota
	void Ruta::rotacion_2_puntos()
	{
		// Copiamos recorrido actual en el posible nuevo recorrido
		recorrido_provisional = recorrido_actual;

		unsigned c1 = aleatorio_num_ciudades(rng);
		unsigned c2;

		do
		{
			c2 = aleatorio_num_ciudades(rng);
		} while (c1 == c2);
		if (c1 > c2)
		{
			auto aux = c2;
			c2 = c1;
			c1 = aux;
		}

		auto it1 = recorrido_provisional.begin() + c1;
		auto it2 = recorrido_provisional.begin() + c2;

		reverse(it1, it2);
		distancia_provisional = calcula_distancia(recorrido_provisional);
	}

	// Elige 2 puntos de la ruta y los intercambia
	void Ruta::intercambio_2_puntos()
	{
		// Copiamos recorrido actual en el posible nuevo recorrido
		recorrido_provisional = recorrido_actual;

		unsigned c1 = aleatorio_num_ciudades(rng);
		unsigned c2;
		do
		{
			c2 = aleatorio_num_ciudades(rng);
		} while (c1 == c2);

		recorrido_provisional[c1] = recorrido_actual[c2];
		recorrido_provisional[c2] = recorrido_actual[c1];
		distancia_provisional = calcula_distancia(recorrido_provisional);
	}

	void Ruta::inicializa_recorrido()
	{
		crea_recorrido_aleatorio(num_ciudades, recorrido_actual);
		//crea_recorrido(num_ciudades,recorrido_actual);
		//crea_recorrido_avaro(recorrido_actual,ciudades);
		distancia_actual = ciudades.calcula_distancia(recorrido_actual);
	}
	void Ruta::crea_recorrido_vecino()
	{
		//A completar
		//El alumno debe programar una cuarta modificacion del recorrido
		//Seleccionar un segmento del recorrido y un punto, e insertar el segmento a partir del punto

		 //Jugamos con distintas modificaciones para "enriquecer" el problema
		auto aleatorio = aleatorio_0_a_1(rng);

		//La selección aleatoria deberá modificarse para contemplar el 4º tipo de modificación
		//de ruta
		if (aleatorio < 0.25)  //Umbrales para valores aleatorios elegidos "a pelo"
			rotacion_3_puntos();
		else if (aleatorio < 0.5)
			rotacion_2_puntos();
		else if (aleatorio < -0.75)
			insercion_segmento();
		else
			intercambio_2_puntos();
	}
	// Genera recorrido aleatorio
	void crea_recorrido_aleatorio(unsigned num_ciudades, std::vector<unsigned>& recorrido)
	{
		recorrido.clear();

		for (unsigned i = 0; i != num_ciudades; ++i)
		{
			recorrido.push_back(i);
		}
		std::random_shuffle(recorrido.begin() + 1, recorrido.end());
	}

	// Genera un recorrido según el orden de ciudad inicial
	void crea_recorrido(unsigned num_ciudades, std::vector<unsigned>& recorrido)
	{
		recorrido.clear();
		for (unsigned i = 0; i != num_ciudades; ++i)
		{
			recorrido.push_back(i);
		}
	}

	// Ruta que escoge la primera ciudad, luego la más cercana, luego la mas cercana a esta última, etc...
	void crea_recorrido_avaro(std::vector<unsigned>& recorrido, const ciudades::Ciudades& ciudades)
	{
		recorrido.clear();
		std::set<unsigned> set_ciudades; //Lista ordenada (posiblemente un arbol rojinegro)
		std::set<unsigned>::iterator it;

		auto num_ciudades = ciudades.get_num_ciudades();

		for (unsigned i = 0; i != num_ciudades; ++i)
		{
			set_ciudades.insert(i);
		}

		unsigned ciudad = 0; //Nuestra primera ciudad del recorrido
		for (unsigned i = 0; i < num_ciudades - 1; ++i)
		{
			// Añadimos ciudad
			recorrido.push_back(ciudad);
			// Eliminamos la ciudad de nuestro conjunto
			it = set_ciudades.find(ciudad); //Al estar ordenadas dentro de set su búsqueda es rápida
			set_ciudades.erase(it);
			ciudad = get_vecino_mas_proximo(ciudad, set_ciudades, ciudades);
		}
		recorrido.push_back(ciudad);
	}
	// Buscamos ciudad mas proxima a ciudad de entre las que quedan en set
	unsigned get_vecino_mas_proximo(const unsigned c, const std::set<unsigned>& set_ciudades, const ciudades::Ciudades& ciudades)
	{
		unsigned ciudad = 0;
		std::set<unsigned>::iterator it = set_ciudades.begin();
		// Inicializa la distancia minima
		double min_dist = ciudades.get_distancia(c, *it);


		for (it = set_ciudades.begin(); it != set_ciudades.end(); it++)
		{
			unsigned n = *it;
			double dist = ciudades.get_distancia(c, n);

			if (dist <= min_dist)
			{
				ciudad = n;
				min_dist = dist;
			}
		}
		return ciudad;
	}

}
