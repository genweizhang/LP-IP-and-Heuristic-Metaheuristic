# clear the environment
reset;
# solver options
option solver cplex;
# option cplex_options 'sensitivity';
# define two sets, which are the number of doctors and procedures.
set I;  # doctors
set J;  # number of procedures
param s{I,J} default 0; # skills of each doctor
param p{I}; # associated pay for calling each doctor; 

# decision variable
var x{I} binary;

# set constraints
s.t.  require {j in J}: sum{i in I} s[i,j]*x[i]>=1;

# objective function
minimize cost: sum {i in I} x[i]*p[i];

#read-in the data
data hw3_question4.dat;
# solve and display the results
solve;
display x, cost;