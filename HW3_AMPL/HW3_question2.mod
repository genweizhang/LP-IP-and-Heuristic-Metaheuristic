# clear the environment
reset;
# solver options
option solver cplex;
# option cplex_options 'sensitivity';
# define two sets, which are the number of of commodities and silos.
set I;  # animal number 
set J;  # cage numbers

# decision variable
var x{I, J} binary;
var y{J} binary;

# set constraints
s.t.  prey1 {j in J}: x[2,j]+x[5,j]+x[10,j]<=3*(1-x[1,j]);
s.t.  prey2 {j in J}: x[1,j]+x[4,j]+x[7,j]<=3*(1-x[2,j]);
s.t.  prey3 {j in J}: x[8,j]+x[10,j]<=2*(1-x[3,j]);
s.t.  prey4 {j in J}: x[2,j]+x[6,j]<=2*(1-x[4,j]);
s.t.  prey5 {j in J}: x[1,j]+x[9,j]<=2*(1-x[5,j]);
s.t.  prey6 {j in J}: x[4,j]+x[10,j]<=2*(1-x[6,j]);
s.t.  prey7 {j in J}: x[2,j]<=1-x[7,j];
s.t.  prey8 {j in J}: x[3,j]+x[9,j]<=2*(1-x[8,j]);
s.t.  prey9 {j in J}: x[5,j]+x[8,j]+x[10,j]<=3*(1-x[9,j]);
s.t.  prey10 {j in J}: x[1,j]+x[3,j]+x[6,j]+x[9,j]<=4*(1-x[10,j]);
s.t.  limit1 {j in J}:  sum{i in I} x[i, j] <=10*y[j];
s.t.  limit2 {i in I}:  sum{j in J} x[i,j]=1;

# objective function
minimize cages: sum{j in J} y[j];

#read-in the data
data HW3_question2.dat;
# solve and display the results
solve;
display x, sum{j in J} y[j];