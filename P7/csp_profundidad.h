namespace problema_csp
{
	template<typename T>
	bool Problema_csp<T>::profundidad()
	{
		struct Nodo
		{
			T nodo;
			bool visitado;
		};
		std::vector<Nodo> lista;
		lista.push_back({ nodo_inicial,false });

		size_t indice = 0;
		bool exito = false;
		nodos_expandidos = 0;
		while (exito == false && lista.size() > 0)
		{
			if (lista.back().visitado)
			{
				lista.pop_back();
			}
			else
			{
				exito = lista.back().nodo.prueba_meta();

				if (!exito) {
					lista.back().visitado = true;
					for (auto hijo : lista.back().nodo.expandir())
					{
						lista.push_back({ hijo,false });
						nodos_expandidos++;
					}
				}
			}
		}
		if (exito)
		{
			nodo_solucion = lista.back().nodo;
		}
		return exito;
	}
}
