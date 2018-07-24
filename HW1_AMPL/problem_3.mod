#HW1 assignment, DSA5113, Dr. Charles Nicholson
# problem 3 code

# clean the current environment
reset;

# specify the solver options
option solver cplex;
option cplex_options 'sensitivity';

# define decision variables
var D16>=0;  #amount of money invested with 6-month option at month 1
var D13>=0;  #amount of money invested with 3-month option at month 1
var D11>=0;  #amount of money invested with 1-month option at month 1
var D23>=0;  #amount of money invested with 3-month option at month 2
var D21>=0;  #amount of money invested with 1-month option at month 2
var D33>=0;  #amount of money invested with 3-month option at month 3
var D31>=0;  #amount of money invested with 1-month option at month 3
var D43>=0;  #amount of money invested with 3-month option at month 4
var D41>=0;  #amount of money invested with 1-month option at month 4
var D51>=0;  #amount of money invested with 1-month option at month 5
var D61>=0;  #amount of money invested with 1-month option at month 6

# objective function
maximize month6: D16*1.035+D51*1.005+D43*1.021+13000;

# set the constraints, key idea: sum of cash inflows=sum of cash outflow for each month.

s.t. start: D16+D11+D13=300000;
s.t. month1: D23+D21=D11*1.005-50000;
s.t. month2: D33+D31=D21*1.005+12000;
s.t. month3: D43+D41=D13*1.021+D31*1.005-23000;
s.t. month4: D51=D23*1.021+D41*1.005+20000;
s.t. month5: D61=D33*1.021+D51*1.005-41000;

solve;

display  D16, D13, D11, D21, D23, D33, D31, D43, D41, D51, D61;





