/*Parametros*/
param num_grupos,integer;
param num_equipos,integer;
set grupos:=1..num_grupos;
set equipos:=1..num_equipos;
param num_personas_en_grupo{grupos}, >0;

/*Variables*/
var x{i in equipos,j in grupos}, binary;
var num_personas_en_grupo_maximo >= 0;
var num_personas_en_grupo_minimo >= 0;


minimize objetivo: num_personas_en_grupo_maximo-num_personas_en_grupo_minimo;

s.t. una_persona_un_equipo{k in grupos}: sum{i in equipos} x[i,k] = 1;
s.t. diferencia_maxima_1_persona{i in equipos, j in equipos:j<>i}: sum{k in grupos} (x[i,k]-x[j,k])<=1;
s.t. restriccion_num_personas_en_grupo_maximo{i in equipos}: sum{k in grupos} num_personas_en_grupo[k]*x[i,k] <= num_personas_en_grupo_maximo;
s.t. restriccion_num_personas_en_grupo_minimo{i in equipos}: sum{k in grupos} num_personas_en_grupo[k]*x[i,k] >= num_personas_en_grupo_minimo;

solve;

printf "num_personas_en_grupo medio por equipo: %.2fKg\n", num_personas_en_grupo_medio_equipo;
for {equipo in equipos}
{  
	printf "Equipo %d:\n", equipo;
	for {persona in grupos: x[equipo,persona]} printf " %d\t %.2fKg\n", persona, num_personas_en_grupo[persona];
	printf "_________________\nTotal:\t %.2fKg\n\n", sum{persona in grupos: x[equipo,persona] == 1} num_personas_en_grupo[persona];
}

data;
param num_equipos := 3;
param num_grupos := 9;
param num_personas_en_grupo :=
 1 484
 2 114
 3 205
 4 288
 5 506
 6 503
 7 201
 8 127
 9 410;
end;