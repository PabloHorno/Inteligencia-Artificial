#ifndef DARDOS_PI_H_INCLUDED
#define DARDOS_PI_H_INCLUDED
#include <stdexcept>
#include <iostream>
#include <cstdlib>
class Dardos_Pi
{
public:
    Dardos_Pi(const unsigned iteraciones)
    {
        try
        {
            if(iteraciones<100)
            {
                throw std::invalid_argument("Las iteraciones deben ser iguales o superiores a 100");
            }
        }
        catch(const std::invalid_argument &mensaje)
        {
            std::cout<<mensaje.what()<<std::endl;
            exit(EXIT_FAILURE);
        }
		calcularPi(iteraciones);
    }
	double get_pi() const { return pi; }
private:
	double pi;
	void calcularPi(const unsigned iteraciones);
};

#endif // DARDOS_PI_H_INCLUDED
