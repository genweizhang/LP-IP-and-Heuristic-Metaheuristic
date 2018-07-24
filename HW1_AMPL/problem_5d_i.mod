#HW1 assignment, DSA5113, Dr. Charles Nicholson
# problem 5d step i code

# clean the current environment
reset;

# specify the solver options
option solver cplex;
option cplex_options 'sensitivity';

# define decision variables: 
# produce whole tomato, using Wa pounds of grade-A and Wb pounds of grade-B
var Wa>=0;
var Wb>=0;
# produce tomato juice, using Ja pounds of grade-A and Jb pounds of grade-B
var Ja>=0;
var Jb>=0;
# produce tomato paste, using Pa pounds of grade-A and Pb pounds of grade-B
var Pa>=0;
var Pb>=0;

#  calculate the profit for making whole, juice and paste 
#  this is per case profit, without considering the cost of tomato.
param profw=0.12;
param profj=-0.09;
param profp=0.12; 
# define the converion factor from case to pound
param wppc=18;
param jppc=20;
param pppc=25;


# set constraints. It has seven constraints: demand, availablity and rating quality requirment 

s.t. demandW: (Wa+Wb)/wppc<=800000;
s.t. demandJ: (Ja+Jb)/jppc<=50000;
s.t. demandP: (Pa+Pb)/pppc<=80000;
s.t. limitA: Wa+Ja+Pa<=600000;
s.t. limitB: Wb+Jb+Pb<=2400000;
s.t. ratingW: Wa-3*Wb>=0;
s.t. ratingJ: 3*Ja-Jb>=0;

# objective function.
maximize profit: (Wa+Wb)/wppc*profw+(Ja+Jb)/jppc*profj+(Pa+Pb)/pppc*profp;
 
solve;
# show the results of production mix

display Wa, Wb, Ja, Jb, Pa, Pb;
 
