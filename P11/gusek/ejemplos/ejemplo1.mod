var x1>=0;
var x2>=0;

s.t. rest1: x1+2*x2<=40;
s.t. rest2: 4*x1+3*x2<=120;

maximize objetivo:4*x1+5*x2;

solve;

display x1;
display x2;
display objetivo;


end;