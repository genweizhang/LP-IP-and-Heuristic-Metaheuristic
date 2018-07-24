#Breakfast Problem
reset;
#set-up options
option solver cplex;
option cplex_options 'sensitivity';

set I;  # number of suppliers

#decision variables
var y{I} integer >=0; #number of boxes that provided by supplier
var x{I} binary;

# parameters
param s{I}; # the set-up cost
param v{I}; # the variable cost
param m{I}; # the max quant supplier can provide


#objective
minimize cost: sum{i in I} (s[i]*x[i]+ y[i]/100*v[i]);
#constraints
s.t. capacity:  sum{i in I } y[i]= 11000;
s.t. chosen {i in I}:  y[i]<=m[i]*x[i];
     

#read-in the data
data Question1.dat;

# solve and display the results
solve;
display x,y, cost;