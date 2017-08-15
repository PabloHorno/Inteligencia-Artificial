#include "controlador.h"
#include <iostream>
#include <string>




int main()
{

	const auto filas = 6u;
	const auto columnas = 6u;

	controlador::Controlador c(filas, columnas);

	c.ejecutar();

	return 0;
}
