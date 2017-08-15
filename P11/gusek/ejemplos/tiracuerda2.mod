/*Parametros*/
param num_personas,integer;
param num_equipos,integer;
set personas:=1..num_personas;
set equipos:=1..num_equipos;
param pesos{personas}, >0;
param peso_medio_equipo := sum{i in personas} pesos[i] /num_equipos;

/*Variables*/
var x{i in equipos,j in personas}, binary;

var peso_maximo >= 0;
var peso_minimo >= 0;
minimize objetivo: peso_maximo-peso_minimo;

s.t. una_persona_un_equipo{j in personas}: sum{i in equipos} x[i,j] = 1;
s.t. diferencia_maxima_1_persona{i in equipos, j in equipos:j<>i}: sum{k in personas} (x[i,k]-x[j,k])<=1;

s.t. pesos_1{i in equipos}: sum{k in personas} pesos[k]*x[i,k] <= peso_maximo;
s.t. pesos_2{i in equipos}: sum{k in personas} pesos[k]*x[i,k] >= peso_minimo;

solve;
printf "Peso medio por equipo: %.2fKg\n", peso_medio_equipo;
for {equipo in equipos}
{  
	printf "Equipo: %d\n", equipo;
	for {persona in personas: x[equipo,persona]} printf " %d", persona;
	printf "\n%.2fKg\n\n", sum{persona in personas: x[equipo,persona] == 1} pesos[persona];
}

data;
param num_equipos := 3;
param num_personas := 9;
param pesos :=
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