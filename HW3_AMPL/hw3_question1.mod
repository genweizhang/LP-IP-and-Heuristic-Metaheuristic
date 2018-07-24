# clear the environment
reset;
# solver options
option solver cplex;
# option cplex_options 'sensitivity';
# define two sets, which are the number of of commodities and silos.
set J;  # Commodities
set I;  # silos

# decision variable
var x{J,I}>=0;
# another binary variable to 	
var y{J,I} binary;

# the loading cost of storing each commodity at each silo
param c{J, I};
# silo capacity parameter and commodity amount parameters:
param sc{I}; # silo capacity
param ca{J}; # commodity amount

# set constraints
s.t.  scap {i in I}: sum{j in J} x[j,i]<=sc[i];
s.t.  ccap {j in J}:  sum{i in I} x[j,i] =ca[j];
s.t.  limit1 {i in I}: sum{j in J} y[j,i]<=1;
s.t.  limit2 {i in I, j in J}: x[j,i]<=y[j,i]*sc[i];

# objective function
minimize cost: sum{i in I, j in J} x[j,i]*c[j,i];
#read-in the data
data HW3_question1.dat;
# solve and display the results
solve;
display x, y, cost;

