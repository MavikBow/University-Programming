# lab 2

param I;
param J;

set Client = 1..I;
set WHouse = 1..J;

param a_ij{Client, WHouse};
param C_i{Client};
param W_j{WHouse};
param S_j{WHouse};
param W1_extra;
param S1_extra;

# the amount from Client_i stored in WHouse_j
var x_ij{Client, WHouse} integer, >=0;
# the amount from Client_i stored in S1+ storage
var x_i6{Client} integer, >= 0;
var is_open{j in WHouse} binary;
var is_extended binary;

#s.t. open{j in 1..3}: is_open[j] = 1;
s.t. store_all{i in Client}: sum{j in WHouse} x_ij[i,j] = C_i[i];
s.t. fit_all{j in WHouse}: sum{i in Client} x_ij[i,j] <= S_j[j] * is_open[j];
s.t. fit_extention: sum{i in Client} x_i6[i] <= is_open[1] * S1_extra * is_extended;

minimize c: sum{j in WHouse} W_j[j]*is_open[j] +
sum{i in Client, j in WHouse} a_ij[i,j] * x_ij[i,j] + 
is_extended * W1_extra * sum{i in Client} x_i6[i] + 
is_extended * sum{i in Client} x_i6[i] * a_ij[i,1];

