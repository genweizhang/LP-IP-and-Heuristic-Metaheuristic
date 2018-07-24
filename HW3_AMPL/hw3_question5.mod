#Galaxy Industries revisit Programming Problem
reset;
#set-up options
option solver cplex;
option cplex_options 'sensitivity';

#decision variables
var sr1 integer >=0; #number of SpaceRay guns to manufacture range from 0 to 125
var sr2 integer >=0; #number of SpaceRay guns to manufacture range from 125 to 225
var sr3 integer >=0; #number of SpaceRay guns to manufacture range from 225 to 375
var sr4 integer >=0; #number of SpaceRay guns to manufacture range above 375
var z1 integer >=0; #number of Zapper guns to manufacture range from 0 to 50
var z2 integer >=0; #number of Zapper guns to manufacture range from 50 to 125
var z3 integer >=0; #number of Zapper guns to manufacture range above 125
var y1 binary;
var y2 binary;
var y3 binary;
var y4 binary;
var y5 binary;

#objective
maximize profit: 8*(sr1+sr2+sr3+sr4)+5*(z1+z2+z3)-(1.5*sr1+1.05*sr2+0.95*sr3+0.75*sr4)-(1.05*z1+0.75*z2+1.5*z3);
#constraints
s.t. plastic:   2*(sr1+sr2+sr3+sr4) +   (z1+z2+z3) <= 1000;
s.t. labor:     3*(sr1+sr2+sr3+sr4) + 4*(z1+z2+z3) <= 2400;
s.t. production:  (sr1+sr2+sr3+sr4) +   (z1+z2+z3) <= 700;
s.t. management:  (sr1+sr2+sr3+sr4) -   (z1+z2+z3) <= 350;
s.t. cs1:  sr1 >=125*y1;
s.t. cs12: sr1 <=125;
s.t. cs2:  sr2 >=100*y2; 
s.t. cs22: sr2 <=100*y1;
s.t. cs3:  sr3 >=150*y3;  
s.t. cs32: sr3 <=150*y2;
s.t. cs4:  sr4 <=1000*y3;
s.t. cz1:  z1 >=50*y4; 
s.t. cz12: z1 <=50;
s.t. cz2:  z2 >=75*y5; 
s.t. cz22: z2 <=75*y4;
s.t. cz3:  z3 <=1000*y5;

# solve and display the results
solve;
display sr1,sr2,sr3,sr4,z1,z2;




