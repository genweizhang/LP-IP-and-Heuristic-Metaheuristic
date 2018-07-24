#HW1 assignment, DSA5113, Dr. Charles Nicholson
# problem 4 code

# clean the current environment
reset;

# specify the solver options
option solver cplex;
option cplex_options 'sensitivity';

# set of seasons
set I circular;

# several parameters
param d{I}; # the demand in each season 
param c >=0; # the cost of holding a pair of sandal per season
param lim>=0; # the limit of prodcution in each season
 
# decsison variable
var x{I}>=0; # the amount of sandals produce in a season
var y{I}>=0; # the amount of sandals holding in a season

# objective function
minimize cost: sum {i in I} c*y[i];

# define the constraints

s.t. demand {i in I}: x[i]+y[prev(i)]>=d[i];
s.t. capability {i in I}: x[i]<=lim;
s.t. relation {i in I}: y[i]=x[i]+y[prev(i)]-d[i];

# Specify the location of the Data
data problem_4.dat;

solve;
display x, y; 
