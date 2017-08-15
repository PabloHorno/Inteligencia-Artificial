#include "dardos_pi.h"
#include <random>
#include <chrono>

void Dardos_Pi::calcularPi(const unsigned iteraciones)
{
	std::mt19937 rng;
	std::uniform_real_distribution<double> aleatorio(-1., 1.);
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	rng.seed(seed);

	unsigned numero_dardos_en_circulo = 0;
	for (int i = 0; i < iteraciones; ++i) {
		std::pair<double, double> pos = { aleatorio(rng) ,aleatorio(rng) };
		if ((pow(pos.first, 2) + pow(pos.second, 2)) <= 1)
			++numero_dardos_en_circulo;
	}
	aleatorio(rng);

	pi = 4. * numero_dardos_en_circulo / iteraciones;
}
