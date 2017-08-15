#include "taquin.h"
#include <iostream>

namespace taquin
{
    void copia_posicion(const unsigned origen[],unsigned destino[])
    {
        for(auto i=0; i<9; ++i)
            destino[i]=origen[i];
    }
    void Taquin::inicializar_lista()
    {
        exito=false;
        struct Nodo_taquin nodo_inicial;

        for(int i=0; i<9; ++i)
        {
            nodo_inicial.posicion[i]=posicion_inicial[i];
            if(posicion_inicial[i]==0)
                nodo_inicial.pos_cas_vac=i;
        }

        nodo_inicial.padre=-1;
        nodo_inicial.profundidad=0;
        nodo_inicial.visitado=false;

        lista.clear();                  //Borramos la lista de nodos
        lista.push_back(nodo_inicial);

    }
    void Taquin::set_objetivo(const unsigned v[])
    {
        copia_posicion(v,posicion_objetivo);
    }
    void Taquin::set_inicial(const unsigned v[])
    {
        copia_posicion(v,posicion_inicial);
    }

    void Taquin::amplitud()
    {
        size_t indice=0;
        inicializar_lista();

        while(exito==false && indice<lista.size()) // lista.size me va a dar el indice del ultimo elemento
        {
            exito=prueba_meta(lista[indice].posicion,posicion_objetivo);

            if(exito==false)
            {
                expandir(indice);
                indice++;
            }
        }
        if(exito)
            indice_objetivo=indice;

    }
   void Taquin::profundidad(size_t limite)
    {
        size_t indice=0;
        inicializar_lista();

        while(exito==false && indice<lista.size()&& lista.size()>0)
        {
			if (lista[indice].visitado == true || lista[indice].profundidad == limite)
                lista.pop_back();
            else
            {
				exito = prueba_meta(lista[indice].posicion, posicion_objetivo);
				if (!exito)
				{
					expandir(indice);
					lista[indice].visitado = true;
				}
            }
            indice=lista.size()-1;
        }
       if(exito)
        indice_objetivo=indice;
    }

    void Taquin::expandir(const size_t indice)
    {
        static const unsigned matriz_expansion[9][5]= {{2,1,7,0,0},{3,0,2,8,0},{2,1,3,0,0},{3,2,4,8,0},{2,3,5,0,0},{3,4,6,8,0},{2,5,7,0,0},{3,0,6,8,0},{4,1,3,5,7}};
        //En la posicion 0 tengo 2 sitios para moverme, la posicion 1 y la posicion 7 {2,1,7,0,0} los otros 0 , 0 son para completar la matriz de tamaño 5
        struct Nodo_taquin hijo;
        hijo.profundidad=lista[indice].profundidad+1;
        hijo.padre=indice;
        hijo.visitado=false; //Este campo no es necesario en la Búsqueda en Amplitud

        auto num_hijos=matriz_expansion[lista[indice].pos_cas_vac][0];
        for(unsigned i=0; i<num_hijos; i++)
        {
            hijo.pos_cas_vac=matriz_expansion[lista[indice].pos_cas_vac][i+1];

            copia_posicion(lista[indice].posicion,hijo.posicion);

            hijo.posicion[lista[indice].pos_cas_vac]=lista[indice].posicion[hijo.pos_cas_vac];
            hijo.posicion[hijo.pos_cas_vac]=0;

            if(!repetido(hijo,indice))
                lista.push_back(hijo);
        }
    }
    bool Taquin::repetido(const Nodo_taquin& nodo,size_t indice)
    {
        //Estrategia buscar nodos repetidos en ancestros
        for (int i=0; i<indice; i++)
            if(prueba_meta(nodo.posicion,lista[i].posicion))
                return true;
        return false;
    }

    bool Taquin::prueba_meta(const unsigned v1[],const unsigned v2[])
    {
        size_t i=0;

        while(i<9)
        {
            if(v1[i]!=v2[i])
                return false;
            ++i;
        }
        return true;
    }

	void Taquin::solucion()
	{
		unsigned i;
		if (exito == false)
		{
			std::cout << "No se encontro solucion" << std::endl;
		}
		else
		{
			unsigned num_posiciones = lista[indice_objetivo].profundidad + 1;
			std::vector<std::vector<unsigned>> solucion;
			int indice = indice_objetivo;  //indice tomará el vaor -1

			for (i = num_posiciones; i--;) //Mucho cuidado con los unsigned cuando decrementamos
			{
				std::vector<unsigned> vector_posiciones;
				for (unsigned posicion : lista[indice].posicion)
					vector_posiciones.push_back(posicion);

				solucion.push_back(vector_posiciones);
				indice = lista[indice].padre;
			}
			for (int i = num_posiciones - 1; i >= 0; --i)
			{
				for (auto x : solucion[i])
					std::cout << x << " ";

				std::cout << std::endl;
			}
		}
	}
}
