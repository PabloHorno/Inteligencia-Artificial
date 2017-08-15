/* BPP, Bin Packing Problem */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* Given a set of items I = {1,...,num_items} with weight peso_item[i] > 0, the Bin
   Packing Problem (BPP) is to pack the items into bins of capacity capacidad
   in such a way that the number of bins used is minimal. */
   
/*Modificado por  Marta Vidal Román & Pablo Horno Pérez EN 2017*/

param num_items, integer, > 0;
/* Numero de Items */

set I := 1..num_items;
/* set of items */

param peso_item{i in 1..num_items}, > 0;
/* peso_item[i] es el peso del item i */

param capacidad, > 0;
/* capacidad del contenedor */

/* Necesitamos estimar un numero maximo de contenedores suficientes para contener todos los elementos.
El número de elementos num_items se puede utilizar, sin embargo, no es una buena idea.
Para obtener una estimación más adecuada se utiliza la siguiente heurística:
ponemos los elementos en un contenedor mientras sea posible, y si el contenedor está lleno, usamos otro.
El número de contenedores utilizados de esta manera nos da una estimación más apropiada.*/

param z{i in I, j in 1..num_items} :=
/* z[i,j] = 1 si item i esta en el contenedor, si no z[i,j] = 0 */

   if i = 1 and j = 1 then 1
   /* item 1 al contenedor 1 */

   else if exists{jj in 1..j-1} z[i,jj] then 0
   /* si el item i esta asignado en algun contenedor, no lo metemos en el contenedor j */

   else if sum{ii in 1..i-1} peso_item[ii] * z[ii,j] + peso_item[i] > capacidad then 0
   /* si el item i no entra en el contenedor j, no lo metemos en j*/

   else 1;
   /* si no se cumple ninguna meter el item en j */

check{i in I}: sum{j in 1..num_items} z[i,j] = 1;
/* cada item en un solo contenedor */

check{j in 1..num_items}: sum{i in I} peso_item[i] * z[i,j] <= capacidad;
/* no hay sobrecarga de contenedor */

param num_contenedores := sum{j in 1..num_items} if exists{i in I} z[i,j] then 1;

display num_contenedores;

set J := 1..num_contenedores;
/* set de contenedores */

var x{i in I, j in J}, binary;
/* x[i,j] = 1 si item i esta en contenedor j */

var used{j in J}, binary;
/* used[j] = 1 significa contenedor J tiene almenos un elemento */

s.t. one{i in I}: sum{j in J} x[i,j] = 1;
/* Cada objeto en un solo contenedor*/

s.t. lim{j in J}: sum{i in I} peso_item[i] * x[i,j] <= capacidad * used[j];
/* Si el contenedor j se usa, verificamos que no este sobrepasando su limite de capacidad*/

minimize obj: sum{j in J} used[j];
/* Objetivo para minimizar el numero de contenedores */

data;

param num_items := 9;

param peso_item := 
1 5, 
2 3, 
3 6, 
4 7, 
5 2, 
6 3,
7 8,
8 8,
9 8;

param capacidad := 8;

end;
