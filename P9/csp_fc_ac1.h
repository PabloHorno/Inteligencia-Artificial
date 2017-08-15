#ifndef CSP_AC1_H_INCLUDED
#define CSP_AC1_H_INCLUDED

template <typename T>
bool Problema_csp<T>::actualiza_dominio_fc_ac1(const std::pair<unsigned, T>& asignacion)
{
	bool bloqueo = actualiza_dominio_fc(asignacion);
	if (!bloqueo)  //Consistencia de arco ac-1 en variables sin asignar
		bloqueo = actualiza_dominio_ac1(asignacion.first);
	return bloqueo;
}

//Actualiza dominios de variables sin asignar entre si: algoritmo AC-1
template <typename T>
bool Problema_csp<T>::actualiza_dominio_ac1(const unsigned variable)
{
	bool cambio = true;
	while (cambio)
	{
		cambio = false;
		for (auto var_i : variables_sin_etiquetar)
		{
			for (auto var_j : variables_sin_etiquetar)
			{
				if (var_i != var_j && relacionadas(var_i, var_j))
				{
					if (revisar_ac1(variable, var_i, var_j))
					{
						cambio = true;
						if (dominio[var_i].empty())
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

template <typename T>
bool Problema_csp<T>::revisar_ac1(const unsigned variable, const unsigned var_i, const unsigned var_j)
{
	bool cambio = false;
	//Completar

	for (unsigned i = 0; i < dominio[var_i].size(); i++)
	{
		auto val_i = dominio[var_i][i];

		cambio = true;
		for (auto val_j : dominio[var_j]) {
			if (consistente(var_i, val_i, var_j, val_j)) {
				cambio = false;
				break;
			}
		}
		if (cambio)
		{
			lista_exclusiones_dominio[variable].push_back({ var_i, val_i });
			dominio[var_i][i] = dominio[var_i].back();
			dominio[var_i].pop_back();
			i--;
			if (!dominio[variable].size())
				return true;
		}
	}

	return cambio;
}
#endif // CSP_AC1_H_INCLUDED
