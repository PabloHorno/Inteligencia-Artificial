/*Parametros*/
param num_grupos,integer;
param num_furgonetas,integer;
set grupos:=1..num_grupos;
set furgonetas:=1..num_furgonetas;
param num_personas_en_grupo{grupos}, >0;
param num_medio_personas_en_furgoneta := sum{i in grupos} num_personas_en_grupo[i] /num_furgonetas;

/*Variables*/
var x{i in furgonetas,j in grupos}, binary;
var num_maximo_personas >= 0, <=8;
var num_minimo_personas >= 0;


minimize objetivo: num_maximo_personas-num_minimo_personas;

s.t. una_persona_un_equipo{k in grupos}: sum{i in furgonetas} x[i,k] = 1;
s.t. restriccion_peso_maximo{i in furgonetas}: sum{k in grupos} num_personas_en_grupo[k]*x[i,k] <= num_maximo_personas;
s.t. restriccion_peso_minimo{i in furgonetas}: sum{k in grupos} num_personas_en_grupo[k]*x[i,k] >= num_minimo_personas;

solve;

printf "Numero medio de personas por furgoneta: %dPers.\n", num_medio_personas_en_furgoneta;
for {furgoneta in furgonetas}
{  
	printf "Furgoneta %d:\n", furgoneta;
	for {grupo in grupos: x[furgoneta,grupo]} printf " %d\t %dPers.\n", grupo, num_personas_en_grupo[grupo];
	printf "_________________\nTotal:\t %dPers.\n\n", sum{grupo in grupos: x[furgoneta,grupo] == 1} num_personas_en_grupo[grupo];
}

data;
param num_furgonetas := 3;
param num_grupos := 5;
param num_personas_en_grupo :=
1 8, 
2 8, 
3 8, 
4 8, 
5 1;
end;