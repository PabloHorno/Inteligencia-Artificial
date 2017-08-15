#include "dardos_pi.h"
#include <iomanip>
int main()
{
	Dardos_Pi pi(100000000); //El constructor recibe el numero de iteraciones y calcula pi
	std::cout << std::setprecision(10) << pi.get_pi() << std::endl; //get_pi() es la unica función de la interfaz de Dardos_Pi
	return 0;
}

