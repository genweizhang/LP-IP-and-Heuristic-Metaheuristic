#Boomer global air service problem
reset;
#set-up options
option solver cplex;
option cplex_options 'sensitivity';

set I={1..5}; # four different locations or airports: moline, boston, newyork and dallas + back to moline

#decision variables
var x{I} >=0; # jet feul added at location i for CE750 aircraft

var y1 binary; # control whether waive ramp fee in boston or not
var y2 binary; # control whether waive ramp fee in newyork or not
var y3 binary; # control whether waive ramp fee in dallas or not

var d1 binary;
var d2 binary;
var d3 binary;
var d4 binary;
var d5 binary;

#objective
minimize cost: 0.593*(x[1]+x[5])+1.246*x[2]+1.115*x[3]+0.897*x[4]+800*y1+450*y2+400*y3;

#constraints
s.t. molinetanker:   7000+x[1] <= 13000;
s.t. molineramp:   7000+x[1]+2*200<=36400-22200;
s.t. bostonland: 7000+x[1]+2*200-4800<=31800-22200;
s.t. bostonland2: 7000+x[1]-4800>=2400;
s.t. bostontanker: 7000+x[1]-4800+x[2]<=13000;
s.t. bostonramp: 7000+x[1]-4800+x[2]+4*200<=36400-22200;
s.t. nyland: 7000+x[1]-4800+x[2]+4*200-2000<=31800-22200;
s.t. nyland2: 7000+x[1]-4800+x[2]-2000>=2400;
s.t. nytanker: 7000+x[1]-4800+x[2]-2000+x[3]<=13000;
s.t. nyramp: 7000+x[1]-4800+x[2]+8*200-2000+x[3]<=36400-22200;
s.t. dallasland: 7000+x[1]-4800+x[2]+8*200-2000+x[3]-5300<=31800-22200;
s.t. dallasland2: 7000+x[1]-4800+x[2]-2000+x[3]-5300>=2400;
s.t. dallastanker: 7000+x[1]-4800+x[2]-2000+x[3]-5300+x[4]<=13000;
s.t. dallasramp: 7000+x[1]-4800+x[2]+8*200-2000+x[3]-5300+x[4]<=36400-22200;
s.t. moline2land: 7000+x[1]-4800+x[2]+8*200-2000+x[3]-5300+x[4]-3100<=31800-22200;
s.t. moline2land2: 7000+x[1]-4800+x[2]-2000+x[3]-5300+x[4]-3100>=2400;
s.t. moline2tanker: 7000+x[1]-4800+x[2]-2000+x[3]-5300+x[4]-3100+x[5]=7000;
s.t. waive1: x[2]>=3350*(1-y1);
s.t. waive2: x[3]>=2010*(1-y2);
s.t. waive3: x[4]>=2345*(1-y3);

# part (b)
s.t. limit1: 670*d1<=x[1];
s.t. limit11: x[1]<=100000*d1;
s.t. limit2: 670*d2<=x[2];
s.t. limit22: x[2]<=100000*d2;
s.t. limit3: 670*d3<=x[3];
s.t. limit33: x[3]<=100000*d3;
s.t. limit4: 670*d4<=x[4];
s.t. limit44: x[4]<=100000*d4;
s.t. limit5: 670*d5<=x[5];
s.t. limit55: x[5]<=100000*d5;

# solve and display the results
solve;
display x,cost;




