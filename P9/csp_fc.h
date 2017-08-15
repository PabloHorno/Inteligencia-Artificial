#ifndef CSP_FC_H_INCLUDED
#define CSP_FC_H_INCLUDED

//Actualiza dominio Forward Checking
template<typename T>
bool Problema_csp<T>::actualiza_dominio_fc(const std::pair<unsigned,T> &asignacion)
{
	auto var_1 = asignacion.first;
	auto val_1 = asignacion.second;
	for (auto var_2 : variables_sin_etiquetar) //int para fil y col para no tener problemas al restar en funcion abs()
	{
		if (relacionadas(var_1, var_2))
		{
			for (unsigned i = 0; i < dominio[var_2].size(); i++)
			{
				auto val_2 = dominio[var_2][i];
				if (!consistente(var_1, val_1, var_2, val_2))
				{
					lista_exclusiones_dominio[var_1].push_back({ var_2,val_2 });
					dominio[var_2][i] = dominio[var_2].back();
					dominio[var_2].pop_back();
					--i;
				}
			}
		}
		if (dominio[var_2].empty())
			return true;
	}
	return false;
}

#endif // CSP_FC_H_INCLUDED
