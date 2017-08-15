#include <algorithm>
template <typename T>
unsigned Problema_csp<T>::seleccion_variable_mrv()
{
	auto variable = std::min_element(variables_sin_etiquetar.begin(), variables_sin_etiquetar.end(),
		[this](const auto &a, const auto &b)->bool
	{
		if (dominio[a].size() < dominio[b].size())
			return true;
		else
			return false;
	});
	std::swap(*variable, variables_sin_etiquetar.back());

	return variables_sin_etiquetar.back();
}