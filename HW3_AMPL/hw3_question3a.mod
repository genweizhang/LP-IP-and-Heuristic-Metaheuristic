# clear the environment
reset;
# solver options
option solver cplex;
# option cplex_options 'sensitivity';

# define two sets, which are the number of of commodities and silos.
set I;  # job number 
set J;  # number of weeks

# parameters
param L{I}; # length of each job
param W{J}; # Available workers each week
param n{I,1..5} default 0; # needed workers 

# variables:
var fi{I, J} integer >=0; #  workers needed for job i in starting week .
var se{I, J} integer >=0; #  workers needed for job i in the second week after starting week 
var th{I, J} integer >=0; #  workers needed for job i in the third week after starting week 
var fo{I, J} integer >=0; #  workers needed for job i in the fourth week after starting week 
var ff{I, J} integer >=0; #  workers needed for job i in the fifth week after starting week
var wo{I,J} integer >=0; # workers needed for job i in week j
var x{I,J} binary default 0; # starting week of project i at week j
var wm integer >=0;# week max number of workers


# set constraints
s.t.  start1 {i in I}: sum{j in J: j<=15-L[i]} x[i,j]=1; # only one starting week
s.t.  start2 {i in I}: sum{j in J:j>=16-L[i]} x[i,j]=0;  # only one starting week
s.t.  week1 {i in I, t in J}: fi[i,t]=n[i,1]*x[i,t];   # assign week one needed workers
s.t.  week2 {i in I, t in J: t<=13}: se[i,t+1]=n[i,2]*x[i,t]; # assign week two needed workers
s.t.  week3 {i in I, t in J: t<=12}: th[i,t+2]=n[i,3]*x[i,t]; # assign week three needed workers
s.t.  week4 {i in I, t in J: t<=11}: fo[i,t+3]=n[i,4]*x[i,t]; # assign week four needed workers
s.t.  week5 {i in I, t in J: t<=10}: ff[i,t+4]=n[i,5]*x[i,t]; # assign week five needed workers
s.t.  addup {i in I, j in J}: wo[i,j]=fi[i,j]+se[i,j]+th[i,j]+fo[i,j]+ff[i,j]; # sum all weeks needed workers into one variable
s.t.  limit {j in J}: sum{i in I}wo[i,j]<=W[j]; # workers availability during each week
s.t.  weekmax {j in J}: wm>=sum{i in I}wo[i,j];  # varaible wm represent the maximum workers for any week


# objective function
minimize worker: wm;

#read-in the data
data hw3_question3a.dat;
# solve and display the results
solve;
display x,wo, wm;