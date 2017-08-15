#include "problema_busqueda_taquin.h"
#include <unordered_map>
#include <queue>
#include <iostream>
namespace taquin
{
    bool Problema_busqueda_taquin::a_estrella()
    {

        struct Nodo_prioridad
        {
            size_t indice;
            size_t coste_estimado;
            bool operator <(const Nodo_prioridad &nodo) const
            {
                return nodo.coste_estimado<coste_estimado;
            }
        };
        struct Nodo
        {
            Nodo_taquin nodo;
            size_t padre;
            size_t coste_actual;
        };

        solucion.clear();
        std::priority_queue<Nodo_prioridad> lista_prioridad;
        std::vector<Nodo> lista; //{nodo,padre,coste_actual}
        std::unordered_map<std::string,size_t>claves;

        //Inicializacion
        lista.push_back({nodo_inicial,0,0});
        claves[nodo_inicial.get_clave()]=0;
        lista_prioridad.push({0,heuristica(nodo_inicial,nodo_objetivo)});

        bool exito=false;
		nodos_expandidos = 0;
		nodos_repetidos = 0;
        size_t indice = 0;
        while(!lista_prioridad.empty())
        {
            // Completar
			exito = lista[indice].nodo == nodo_objetivo; //Prueba meta
			if (exito)
				break;

			std::vector<Nodo_taquin> hijos = lista[indice].nodo.expandir();
			++nodos_expandidos;
			for (Nodo_taquin& x : hijos)
			{
				Nodo hijo = { x,indice, coste_operador(lista[indice].nodo,x) + lista[indice].coste_actual };
				std::string clave_hijo = hijo.nodo.get_clave();
				if (claves.count(clave_hijo))
				{
					++nodos_repetidos;
					size_t indice_hash_hijo = claves[clave_hijo];
					if (hijo.coste_actual < lista[indice_hash_hijo].coste_actual)
						lista[indice_hash_hijo] = hijo;
				}
				else
				{
					lista.push_back(hijo);
					lista_prioridad.push({ lista.size() - 1, hijo.coste_actual + heuristica(hijo.nodo,nodo_objetivo) });
					claves.insert({ clave_hijo, lista.size() - 1 });
				}
			}
			indice = lista_prioridad.top().indice;
			lista_prioridad.pop();
        }

        if(exito)
        {
            while(indice!=0)
            {
				solucion.insert(solucion.begin(), lista[indice].nodo);
                indice=lista[indice].padre;
            }
			solucion.insert(solucion.begin(), lista[indice].nodo);
        }
        return exito;
    }
}
