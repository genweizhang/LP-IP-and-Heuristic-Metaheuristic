# clear the environment
reset;
# solver options
option solver cplex;
option cplex_options 'sensitivity';
# define the set, which is # number of songs
set I; 
# decision variable
var x{I} binary;
# the length of each song
param L{I};
# total length of all songs
param T;
# set constraints, assume side B is longer than side A
s.t.  positiveness: T-2*(sum{i in I} x[i]*L[i])>=0;
# objective function
minimize diff: T-2*(sum{i in I} x[i]*L[i]);
#read-in the data
data Exam1_question2.dat;
# solve and display the results
solve;
display x, diff;
