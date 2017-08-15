#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <thread>
#include <string>
#include <mutex>
#include "mapper.h"

class Casilla : public sf::RectangleShape {
public:
	Casilla() { empty = true; };
	Casilla(sf::Vector2f size)
	{
		this->setSize(size);
	}
	unsigned columna;
	unsigned fila;
private:
	bool empty = false;
};

class Tablero
{
private:
	unsigned lado;
	const sf::Vector2u dimension_ventana = { 800, 800 };
	std::vector<unsigned> reinas;
	std::thread hilo;
	std::vector<Casilla> casillas;
public:
	Tablero(const unsigned lado)
	{
		this->lado = lado;
	}
	~Tablero()
	{
		if (hilo.joinable())
			hilo.join();
	}

	void dibujar_tablero(std::string titulo, std::vector<unsigned> reinas)
	{
		hilo = std::thread(&Tablero::generar_tablero, this, titulo, reinas);
	}
	void dibujar_tablero(std::string titulo, std::vector<std::pair<unsigned, unsigned>> reinas_pair)
	{

		std::vector<unsigned> reinas;
		std::sort(reinas_pair.begin(), reinas_pair.end(),
			[](const std::pair<unsigned, unsigned> &a, const std::pair<unsigned, unsigned> &b) {return a.first < b.first; }
		);

		for (auto x : reinas_pair)
			reinas.push_back(x.second);

		hilo = std::thread(&Tablero::generar_tablero, this, titulo, reinas);
	}

private:
	void generar_tablero(std::string titulo, std::vector<unsigned>reinas)
	{
		sf::RenderWindow window;
		window.create(sf::VideoMode(dimension_ventana.x, dimension_ventana.y), titulo);
		set_reinas(reinas);
		while (true)
		{
			manejador_eventos(window);

			window.clear(sf::Color::White);
			for (auto casilla : casillas)
			{
				window.draw(casilla);
			}
			window.display();
		}
	}
	void set_reinas(std::vector<unsigned> reinas)
	{
		this->reinas = reinas;
		casillas.clear();
		unsigned k = 0;
		for (unsigned i = 0; i < lado; i++)
		{
			for (unsigned j = 0; j < lado; j++)
			{
				casillas.push_back(Casilla(sf::Vector2f(dimension_ventana.x / lado, dimension_ventana.y / lado)));
				casillas.back().setFillColor(sf::Color::White);
				casillas.back().move(dimension_ventana.x * j / lado, dimension_ventana.y * i / lado);
				casillas.back().setOutlineColor(sf::Color::Black);
				casillas.back().setOutlineThickness(2);
				if (k < reinas.size() && reinas[k] == j)
				{
					casillas.back().setFillColor(sf::Color::Black);
				}
				casillas.back().fila = i;
				casillas.back().columna = j;
			}
			k++;
		}
	}
	Casilla& get_casilla(sf::Vector2f pos)
	{
		for (unsigned i = 0; i < casillas.size(); ++i)
		{
			sf::Vector2f posicion = casillas[i].getPosition();
			sf::Vector2f tam = casillas[i].getSize();
			if (pos.x > posicion.x && pos.x < posicion.x + tam.x && pos.y> posicion.y && pos.y < posicion.y + tam.y)
			{
				return casillas[i];
			}
		}
		return Casilla();
	}

	Casilla& get_casilla(const unsigned columna, const unsigned fila)
	{
		for (auto casilla = casillas.begin(); casilla < casillas.end(); casilla++)
			if (casilla->columna == columna && casilla->fila == fila)
			{
				return *casilla;
			}
		return Casilla();
	}
	void mostrar_posiciones_amenazadas(Casilla& casilla)
	{
		Mapper_0_1<int> dominio(125, 255);
		sf::Color color = sf::Color(dominio((double)casilla.fila / this->lado), 0, 0);
		pintar_diagonales(casilla, color);
		pintar_columna(casilla.columna, color);
		pintar_fila(casilla.fila, color);
		casilla.setFillColor(sf::Color::Black);
	}
	void mostrar_posiciones_amenazadas()
	{
		for (auto casilla = casillas.begin(); casilla < casillas.end(); casilla++)
		{
			if (casilla->getFillColor() == sf::Color::Black)
			{
				Mapper_0_1<int> dominio(125, 255);
				sf::Color color = sf::Color(dominio((double)casilla->fila / this->lado), 0, 0);
				pintar_diagonales(*casilla, color);
				pintar_columna(casilla->columna, color);
				pintar_fila(casilla->fila, color);
				casilla->setFillColor(sf::Color::Black);
			}
		}
	}
	void redibujar_tablero()
	{
		for (auto &casilla : casillas)
			if (casilla.getFillColor() != sf::Color::Black)
				casilla.setFillColor(sf::Color::White);
	}
	void pintar_columna(unsigned columna, sf::Color color)
	{
		for (auto &casilla : casillas)
			if (casilla.columna == columna)
				if (casilla.getFillColor() != sf::Color::Black && casilla.getFillColor() != sf::Color::Yellow)
					casilla.setFillColor(color);
				else if (casilla.getFillColor() == sf::Color::Black)
					casilla.setFillColor(sf::Color::Yellow);
	}
	void pintar_fila(unsigned fila, sf::Color color)
	{
		for (auto & casilla : casillas)
			if (casilla.fila == fila)
				if (casilla.getFillColor() != sf::Color::Black && casilla.getFillColor() != sf::Color::Yellow)
					casilla.setFillColor(color);
				else if (casilla.getFillColor() == sf::Color::Black)
					casilla.setFillColor(sf::Color::Yellow);
	}
	void pintar_diagonales(Casilla &casilla, sf::Color color)
	{
		unsigned num_diagonal = 0;
		while (num_diagonal < 4) {
			int fin_fila, fin_columna, incremento_fila, incremento_columna;
			switch (num_diagonal++)
			{
			case 0:
				incremento_fila = -1; incremento_columna = -1; fin_columna = 0; fin_fila = 0;
				break;
			case 1:
				incremento_fila = +1; incremento_columna = +1; fin_columna = lado; fin_fila = lado;
				break;
			case 2:
				incremento_fila = -1; incremento_columna = +1; fin_columna = lado; fin_fila = 0;
				break;
			case 3:
				incremento_fila = +1; incremento_columna = -1; fin_columna = 0 + incremento_columna; fin_fila = lado;
				break;
			}
			fin_fila += incremento_fila;
			fin_columna += incremento_columna;

			int columna = casilla.columna;
			int fila = casilla.fila;
			while (columna != fin_columna && fila != fin_fila) {
				Casilla& casilla = get_casilla(columna, fila);
				if (casilla.getFillColor() != sf::Color::Black && casilla.getFillColor() != sf::Color::Yellow)
					casilla.setFillColor(color);
				else if (casilla.getFillColor() == sf::Color::Black)
					casilla.setFillColor(sf::Color::Yellow);
				columna += incremento_columna;
				fila += incremento_fila;
			}
		}
	}

	void manejador_eventos(sf::RenderWindow &window)
	{
		sf::Event evento;
		while (window.pollEvent(evento))
		{
			if (evento.type == sf::Event::Closed)
				window.close();
			if (evento.type == sf::Event::KeyPressed) {
				if (evento.key.code == 0)
				{
					std::cout << "Monstrando posiciones amenazadas" << std::endl;
					mostrar_posiciones_amenazadas();
				}
				else if (evento.key.code == 17)
				{
					std::cout << "Redibujando Tablero" << std::endl;
					redibujar_tablero();
				}
				else
					std::cout << "No hay ninguna funcion asignada a la tecla " << evento.key.code << std::endl;
			}
			if (evento.type == sf::Event::MouseButtonPressed)
			{
				Casilla& casilla = get_casilla(sf::Vector2f(evento.mouseButton.x, evento.mouseButton.y));

				if (evento.mouseButton.button == sf::Mouse::Button::Left)
				{
					if (casilla.getFillColor() == sf::Color::White)
						casilla.setFillColor(sf::Color::Black);
					else
						casilla.setFillColor(sf::Color::White);
				}
				else
					if (casilla.getFillColor() == sf::Color::Black)
					{
						mostrar_posiciones_amenazadas(casilla);
					}
			}
		}
	}
};