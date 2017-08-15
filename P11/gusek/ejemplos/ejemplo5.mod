/*Parametros */
param n;
param p;
set items:={1..n};

param coste{items};

/*Variables*/
var x{items}, binary;

/*Funcion objetivo*/
minimize Coste_Total: sum{i in items} coste[i]*x[i];

/*Restricciones*/
s.t. justo_p_items: sum{i in items} x[i] = p;

/*Resolver*/
solve;

/*Mostrar resultado*/
display{i in items: x[i]=1}: x[i];
display Coste_Total;