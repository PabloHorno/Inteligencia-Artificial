#include "reversi.h"
#include <cstddef>
#include <iostream>

void Reversi::inicializar()
{
	for (unsigned i = 0; i < filas; i++)
	{
		for (unsigned j = 0; j < columnas; j++)
		{
			posicion.set_tablero(i, j, Turno::vacia);
		}
	}
	posicion.set_tablero((filas / 2) - 1, (columnas / 2) - 1, Turno::humano);
	posicion.set_tablero((filas / 2), (columnas / 2), Turno::humano);
	posicion.set_tablero((filas / 2) - 1, (columnas / 2), Turno::ordenador);
	posicion.set_tablero((filas / 2), (columnas / 2) - 1, Turno::ordenador);
	posicion.set_turno(Turno::humano);
	posicion.set_pasa(Tipo_tablero::no_pasa);
	jugadas_validas_humano = posicion.calcula_jugadas();
	heuristica = 0;
	algoritmo = Algoritmo::alpha_beta;
	profundidad_maxima = 11;
}

void Reversi::ejecuta_movimiento(const unsigned fil, const unsigned col)
{
	auto jugadas_validas = posicion.calcula_jugadas();
	if (!jugadas_validas.empty())
	{
		if (turno_humano())
		{
			for (auto &jugada : jugadas_validas)
			{
				if (jugada.x == fil &&jugada.y == col) //La casilla (fil,col)es una de las jugadas validas
				{
					posicion.actualiza_tablero(jugada);
					posicion.set_turno(Turno::ordenador);
					posicion.set_pasa(Tipo_tablero::no_pasa);
				}
			}
		}
		else
		{
			for (auto &jugada : jugadas_validas)
			{
				if (jugada.x == fil &&jugada.y == col) //La casilla (fil,col)es una de las jugadas validas
				{
					posicion.actualiza_tablero(jugada);
					posicion.set_turno(Turno::humano);
					posicion.set_pasa(Tipo_tablero::no_pasa);
				}
			}
		}
	}
	else
	{
		if (posicion.get_pasa() == Tipo_tablero::no_pasa)
		{
			posicion.set_pasa(Tipo_tablero::pasa);
			if (turno_humano())
				posicion.set_turno(Turno::humano);
			else
				posicion.set_turno(Turno::ordenador);
		}
		else
		{
			posicion.set_pasa(Tipo_tablero::terminal);
		}
	}
}

void Reversi::ejecuta_movimiento()
{
	do
	{
		if (algoritmo == Algoritmo::minimax)
		{
			heuristica = estrategia_minimax();
		}
		else if (algoritmo == Algoritmo::alpha_beta)
		{
			heuristica = estrategia_alpha_beta();
		}
		posicion.set_turno(Turno::humano);
		jugadas_validas_humano = posicion.calcula_jugadas();
		if (!jugadas_validas_humano.size())                        //Tablero en pasa para humano
		{
			if (posicion.get_pasa() == Tipo_tablero::no_pasa)
			{
				posicion.set_pasa(Tipo_tablero::pasa);
				posicion.set_turno(Turno::ordenador);
			}
			else
			{
				posicion.set_pasa(Tipo_tablero::terminal);
			}
		}
	} while (turno_ordenador());
}
//#define DEBUG
int Reversi::estrategia_alpha_beta()
{
	std::vector<Nodo_reversi_alpha_beta> lista;
	Nodo_reversi_alpha_beta nodo_inicial(posicion);
	nodo_inicial.set_nodo_inicial();
	lista.push_back(nodo_inicial);
	auto valor_alpha = lista.back().get_alpha();
	bool poda = false;
	while (!lista.empty())
	{
		auto padre = lista.back().get_padre();
		if (!lista.back().get_visitado())
		{
			lista.back().set_visitado();
			if (lista.back().get_pasa() == Tipo_tablero::terminal)
			{
#ifdef DEBUG
				std::cout << "POSICION TERMINAL" << std::endl;
#endif // DEBUG
				lista.back().set_alpha_o_beta(lista.back().evalua_posicion(true));
			}
			else if (lista.back().get_profundidad() == profundidad_maxima)
			{
#ifdef DEBUG
				std::cout << "POSICION PROFUNDIDAD MAXIMA" << std::endl;
#endif // DEBUG
				lista.back().set_alpha_o_beta(lista.back().evalua_posicion(false));
			}
			else
			{
				if (padre >= 0) {
					lista.back().set_alpha(lista[padre].get_alpha());
					lista.back().set_beta(lista[padre].get_beta());
				}
				auto padre_del_nodo_expandido = lista.size() - 1;
				int i = 0;
				for (auto &hijo : lista.back().expandir()) {
					hijo.set_padre(padre_del_nodo_expandido);
					lista.push_back(hijo);
					++i;
				}
#ifdef DEBUG
				std::cout << "EXPANDO Y PONGO EL DEL PADRE " << i << std::endl;
#endif // DEBUG
			}

		}
		else
		{

			if (padre >= 0) {
#ifdef DEBUG
				std::cout << "ACTUALIZO APHA BETA PADRE" << std::endl;
#endif // DEBUG
				auto alpha_padre = lista[padre].get_alpha();
				auto beta_padre = lista[padre].get_beta();
				auto alpha = lista.back().get_alpha();
				auto beta = lista.back().get_beta();

				if (lista.back().get_turno() == Turno::ordenador) {
					if (alpha < beta_padre)
						lista[padre].set_beta(alpha);
					if (beta < alpha_padre)
						lista[padre].set_alpha(beta);
				}
				else {
					if (alpha > beta_padre)
						lista[padre].set_beta(alpha);
					if (beta > alpha_padre)
						lista[padre].set_alpha(beta);
				}
				if (padre == 0) {
					posicion.set_tablero(lista.back().get_tablero());
					posicion.set_pasa(lista.back().get_pasa());
					valor_alpha = alpha;
				}
				else if (lista[padre].get_beta() <= lista[padre].get_alpha())
				{
					int i = 0;
					while (lista.back().get_padre() == padre) {
						++i;
						lista.pop_back();
					}
#ifdef DEBUG
					std::cout << "PODA " << i << std::endl;
#endif // DEBUG
				}
			}
			lista.pop_back();
		}
	}
#ifdef DEBUG

	std::cout << valor_alpha << std::endl;

#endif // DEBUG
	return valor_alpha;
}

int Reversi::estrategia_minimax()
{
	std::vector<Nodo_reversi_minimax> lista;
	Nodo_reversi_minimax nodo_inicial(posicion);
	nodo_inicial.set_nodo_inicial();
	lista.push_back(nodo_inicial);
	auto valor_minimax = lista[0].get_minimax(); //valor final para MAX

	while (!lista.empty())
	{
		if (!lista.back().get_visitado())
		{
			lista.back().set_visitado();
			if (lista.back().get_pasa() == Tipo_tablero::terminal)  //Posición terminal
			{
				lista.back().set_minimax(lista.back().evalua_posicion(true));
			}
			else if (lista.back().get_profundidad() == profundidad_maxima)  //Suspensión
			{
				lista.back().set_minimax(lista.back().evalua_posicion(false));
			}
			else
			{
				auto tam_lista = lista.size();
				auto minimax_actual = lista.back().get_minimax();
				for (auto &hijo : lista.back().expandir())
				{
					hijo.set_padre(tam_lista - 1);
					hijo.set_minimax(-minimax_actual);
					lista.push_back(hijo);
				}
			}
		}
		else
		{
			//          actualiza minimax padre
			auto padre = lista.back().get_padre();
			if (padre >= 0)
			{
				auto minimax_hijo = lista.back().get_minimax();
				auto minimax_padre = lista[padre].get_minimax();
				if (lista.back().get_turno() == Turno::ordenador) //El padre es humano: nodo MIN
				{
					if (minimax_hijo < minimax_padre)
					{
						lista[padre].set_minimax(minimax_hijo);
					}
				}
				else  //El padre es ordenador: nodo MAX
				{
					if (minimax_hijo > minimax_padre)
					{
						lista[padre].set_minimax(minimax_hijo);
						if (padre == 0) //Mejoramos la puntuacion del nodo raiz
						{
							posicion.set_tablero(lista.back().get_tablero());
							posicion.set_pasa(lista.back().get_pasa());
							valor_minimax = minimax_hijo;
						}
					}
				}
			}
			lista.pop_back();  //Eliminamos el nodo actual
		}
	}
	return(valor_minimax);
}