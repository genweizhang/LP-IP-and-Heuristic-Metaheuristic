# AMPL model for the Minimum Cost Network Flow Problem
# By default, this model assumes that b[i] = 0, c[i,j] = 0,
# l[i,j] = 0 and u[i,j] = Infinity.
# Parameters not specified in the data file will get their default values.

reset;
options solver cplex;

set NODES;                        # nodes in the network
set ARCS within {NODES, NODES};   # arcs in the network 

param b {NODES} default 0;        # supply/demand for node i
param c {ARCS}  default 0;        # cost of one of flow on arc(i,j)
param l {ARCS}  default 0;        # lower bound on flow on arc(i,j)
param u {ARCS}  default Infinity; # upper bound on flow on arc(i,j)
param fix; 						  # fixed cost of selling product to Koogle

# decision variable x and binary variable y

var x {ARCS};                # flow on arc (i,j)
var y binary;	     		 # binary y to dertermine whether or not selling product to Koogle


minimize cost: sum{(i,j) in ARCS} c[i,j] * x[i,j] +fix*y ;  #objective: minimize arc flow cost

# set constraints
# Flow Out(i) - Flow In(i) = b(i)
subject to flow_balance {i in NODES}:
sum{j in NODES: (i,j) in ARCS} x[i,j] - sum{j in NODES: (j,i) in ARCS} x[j,i] = b[i];
# within lower and upper bounds
subject to capacity {(i,j) in ARCS}: l[i,j] <= x[i,j] <= u[i,j];
# if sell product to Koogle, make sure y=1
subject to Koogle: x[8,9]<=450*y;

# read-in data and solve it
data Exam1_question3.dat;
solve;
display x, y;
