#ifndef HANOI_H_INCLUDED
#define HANOI_H_INCLUDED
//Añadir las cabeceras que necesiteis
namespace hanoi
{
	class Hanoi
	{
	public:
		Hanoi(unsigned num)
		{
			num_clavijas = num;
			//Aquí podeis rellenar "a mano" el estado inicial
			//usando vuestras variables miembro que describen el estado
		}
		bool operador_valido(unsigned, unsigned) const;
		Hanoi crea_hijo(unsigned, unsigned) const;
	private:
		static unsigned num_clavijas;
		//Complete la descripcion del estado

	};
	void muestra_estado(const Hanoi&);
}

#endif // HANOI_H_INCLUDED
