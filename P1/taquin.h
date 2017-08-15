#ifndef TAQUIN_H_INCLUDED
#define TAQUIN_H_INCLUDED

#include <cstddef>
#include <vector>
#include <limits>


namespace taquin
{
    struct Nodo_taquin
    {
        unsigned posicion[9];
        unsigned pos_cas_vac;
        int padre;  //int pues el nodo inicial tiene un valor de indice invalido -1
        unsigned profundidad;
        bool visitado;
    };

    class Taquin
    {
    public:
        Taquin(unsigned i[],unsigned f[]) //Constructor
        {
            set_inicial(i);
            set_objetivo(f);
        }
        void amplitud();
        void profundidad()
        {
            size_t max_valor = std::numeric_limits<size_t>::max();
            profundidad(max_valor);
        }
        void profundidad(size_t);
        void solucion();


    private:
        void set_inicial(const unsigned v[]);  //Podrían ser públicas y de esta forma probar distintas configuraciones
        void set_objetivo(const unsigned v[]); //en el mismo programa y con la misma variable Taquin
        bool prueba_meta(const unsigned [],const unsigned []);
        void expandir(const size_t);
        bool repetido(const Nodo_taquin&,size_t);
        void inicializar_lista();

        std::vector <Nodo_taquin> lista;
        unsigned indice_objetivo;  //Indice del árbol en el que se encuentra la solucion
        bool exito;                //A true si encontramos la solucion
        unsigned posicion_inicial[9];
        unsigned posicion_objetivo[9];
     };
}

#endif // TAQUIN_H_INCLUDED
