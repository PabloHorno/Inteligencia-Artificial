/*Parametros*/
param n,integer;
set items:={1..n}; 
param W, >0;
param peso{items}, >0, integer;
param valor{items}, >0, integer;

/*Variables*/
var x{1..n}, binary;

maximize objetivo: sum{i in items} x[i]*valor[i];

s.t. restriccion: sum{i in items} peso[i]*x[i] <= W;

solve;

display{i in items: x[i]<>0}: x[i]; 
display objetivo;

data;
param n := 8;
param W := 100;
param peso :=
	1 10
	2 10
	3 15
	4 20
	5 20
	6 24
	7 24
	8 50;

param valor :=
	1 10
	2 10
	3 15
	4 20
	5 20
	6 24
	7 24
	8 50;