#include "prueba_csp.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
namespace prueba_csp
{
    void Prueba_csp::inicializa_dominio()
    {
        //COMPLETAR
		dominio = std::vector<std::vector<int>>(num_variables, std::vector<int>(num_variables, 0));
		for (unsigned i = 0; i < num_variables; i++)
			for (unsigned j = 1; j < 9; j++)
				dominio[i].push_back(j);
    }
    bool Prueba_csp::consistente(const unsigned variable,const int valor)
    { //Os recuerdo desde esta funcion de la clase derivada tenemos acceso a la solucion actual
      //al ser solucion un miembro protected de la clase madre Problema_csp

      //Para calcular el valor absoluto de una diferencia de enteros puede usarse abs()

		for (auto var:solucion)
		{
			if (var.second == valor)
				return false;

			if (vecinas(variable, var.first))
				if (abs(valor - var.second) < 2)
					return false;
		}
		return true;
    }
    bool Prueba_csp::vecinas(unsigned var_1,unsigned var_2)
    {
        if(var_1>var_2)
            std::swap(var_1,var_2);

        bool salida=false;
        switch(var_1)
        {
            case 0:
                if(var_2<4)
                    salida=true;
                break;
            case 1:
                if(var_2<6 && var_2!=3)
                    salida=true;
                break;
            case 2:
                if(var_2<7)
                    salida=true;
                break;
            case 3:
                if(var_2==5 || var_2==6)
                    salida=true;
                break;
            case 4:
                if(var_2==5 || var_2==7)
                    salida=true;
                break;
            case 5:
                if(var_2==6 || var_2==7)
                    salida=true;
                break;
            default:
               salida=true;
        }
        return salida;
    }


    void imprime_solucion(std::vector<std::pair<unsigned,int>>& solucion)
    {
        std::sort(solucion.begin(),solucion.end());
        for(auto v:solucion)
        {
            std::cout<<"("<<v.first<<","<<v.second<<")"<<std::endl;
        }
    }
}
