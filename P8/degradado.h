#pragma once

template<typename T>
class Degradado_0_1
{
public:
	Degradado_0_1(T limite_inferior, T limite_superior)
	{
		this->limite_inferior = limite_inferior;
		this->limite_superior = limite_superior;
		if (this->limite_inferior > this->limite_superior)
			std::swap(this->limite_inferior, this->limite_superior);
	}
	T operator()(double x) {
		return x*(limite_superior - limite_inferior) + limite_inferior;
	}
private:
	T limite_inferior, limite_superior;
};