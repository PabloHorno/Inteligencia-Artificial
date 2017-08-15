#ifndef PRUEBA_CSP_H_INCLUDED
#define PRUEBA_CSP_H_INCLUDED
#include "problema_csp.h"
#include <vector>

namespace prueba_csp
{
    class Prueba_csp:public csp::Problema_csp<int>
    {
    public:
        Prueba_csp()
        {
            num_variables=8;
        }
        void actualiza_estado(const std::pair<unsigned,int> &asignacion)
        {;}
        void restaura_estado(const std::pair<unsigned,int> &asignacion)
        {;}
        bool consistente(const unsigned variable,const int valor);
        void inicializa_dominio();
    private:
        bool vecinas(unsigned var_1,unsigned var_2);
    };
    void imprime_solucion(std::vector<std::pair<unsigned,int>>& solucion);

}
#endif // PRUEBA_CSP_H_INCLUDED
