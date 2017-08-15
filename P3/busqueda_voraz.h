#include <unordered_map>
#include <queue>
namespace problema_busqueda
{
	template <typename T>
	bool Problema_busqueda<T>::voraz()
	{
		struct Nodo_prioridad
		{
			size_t indice;
			decltype(nodo_inicial.tipo_dato_coste()) coste_estimado;
			bool operator <(const Nodo_prioridad &nodo) const
			{
				return nodo.coste_estimado<coste_estimado;
			}
		};
		struct Nodo
		{
			T nodo;
			size_t padre;
			decltype(nodo_inicial.tipo_dato_coste()) coste_actual;
		};

		solucion.clear();
		std::priority_queue<Nodo_prioridad> lista_prioridad;
		std::vector<Nodo> lista; //{nodo,padre,coste_actual}
		lista.push_back({ nodo_inicial,0,0 });

		//En la tabla Hash guardamos el valor del coste actual del nodo
		std::unordered_map<decltype(nodo_inicial.get_clave()), decltype(lista.size())>claves;
		claves[nodo_inicial.get_clave()] = 0;
		lista_prioridad.push({ 0,heuristica(nodo_inicial,nodo_objetivo) });

		bool exito = false;
		nodos_expandidos = 0;
		size_t indice = 0;
		while (exito == false && !lista_prioridad.empty())
		{
			exito = lista[indice].nodo == nodo_objetivo;
			if (exito)
				break;

			std::vector<T> hijos = lista[indice].nodo.expandir();
			++nodos_expandidos;
			for (T& x : hijos)
			{
				Nodo hijo = { x,indice, heuristica(hijo.nodo,nodo_objetivo) };
				decltype(hijo.nodo.get_clave()) clave_hijo = hijo.nodo.get_clave();
				if (claves.count(clave_hijo))
				{
					size_t indice_hash_hijo = claves[clave_hijo];
					if (hijo.coste_actual < lista[indice_hash_hijo].coste_actual)
						lista[indice_hash_hijo] = hijo;
				}
				else
				{
					lista.push_back(hijo);
					lista_prioridad.push({ lista.size() - 1, heuristica(hijo.nodo,nodo_objetivo) });
					claves.insert({ clave_hijo, lista.size() - 1 });
				}
			}
			indice = lista_prioridad.top().indice;
			lista_prioridad.pop();
		}

		if (exito)
		{
			while (indice != 0)
			{
				solucion.push_back(lista[indice].nodo);
				indice = lista[indice].padre;
			}
			solucion.push_back(lista[indice].nodo);
		}
		return exito;
	}
}
