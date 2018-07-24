### Distance guided local search
## DSA5113-HW5 Charles Nicholson

# Student name: Genwei Zhang
# Date: 05/06/2018
#------------------------------------------------------------------------------


#need some python libraries
import copy
import math
from random import Random   # need this for the random number generation 
import numpy as np


#to setup a random number generator, we will specify a "seed" value
#need this for the random number generation -- do not change
seed = 5113
myPRNG = Random(seed)

#to get a random number between 0 and 1, use this:             myPRNG.random()
#to get a random number between lwrBnd and upprBnd, use this:  myPRNG.uniform(lwrBnd,upprBnd)
#to get a random integer between lwrBnd and upprBnd, use this: myPRNG.randint(lwrBnd,upprBnd)

#number of dimensions
n = 2

# lower and upper bounds
lbound=-500
ubound=500


#Schwefel function to evaluate a real-valued solution x    
# note: the feasible space is an n-dimensional hypercube centered at the origin with side length = 2 * 500
               
def evaluate(x): 

    val = 0
    d = len(x)
    for i in range(d):
        val = val + x[i]*math.sin(math.sqrt(abs(x[i])))
                                    
    val = 418.9829*d - val         
                
    return val    
          

# neighborhood structure of positions         
def neighborhood(x):

    # randomly re-generate one component, set the neighborhood size =20*200    
    nbrhood = []     
    for i in range(n):
        for j in range(20):
            mid=x[:]
            mid[i]=myPRNG.uniform(lbound,ubound)
            nbrhood.append(mid[:])  

    return nbrhood
          

#create the initial solution, randomly
def initial_solution():
    pos1 = []
    for i in range(0,n):
        pos1.append(myPRNG.uniform(lbound,ubound))

    return pos1
    
#compute the distance between position x and y
def dist(x,y):
    distance=np.array(x)-np.array(y)
    a=0
    for i in range(n):
        a=a+distance[i]**2
    a=math.sqrt(a)

    return a


#main code:

#varaible to record the number of solutions evaluated
solutionsChecked = 0

# initialize the position and values
curr_pos = initial_solution()  #hold the current position 
best_pos = curr_pos[:]           # hold the best position
curr_val = evaluate(curr_pos)   #hold the evaluation of the current position 
best_val = curr_val   
bestqueue=[]                # track all the best values found within each sphere
bestqueue.append(best_val)


# Sphere radius cutoff
R=0.2

while min(bestqueue)>0.002:                   # while haven't reached our expected values yet
    
    while dist(curr_pos, best_pos)<R:      # while still within a sphere, radius euqals to 0.2
        
        # best accept local search!
        Neighborhood = neighborhood(curr_pos)   #get the neighborhood structures 
        for s in Neighborhood:                    #evaluate every member in the neighborhood of curr_pos   
            solutionsChecked = solutionsChecked + 1
            if evaluate(s) < best_val:   
                best_pos = s[:]                 #find the best member and keep track of that position
                best_val = evaluate(s)          #and store its evaluation value. 
        
        if curr_val==best_val:         # stop the while loop if reached local minima
            break

    # queue the best values found within the sphere 
    bestqueue.append(best_val) 

    # update the current position and values, move to next!
    curr_pos = best_pos[:]         
    curr_val = best_val         
        
    print ("\nTotal number of solutions checked: ", solutionsChecked)
    print ("Best value found so far: ", min(bestqueue)) 
      
    
print ("\nFinal number of solutions checked: ", solutionsChecked)
print ("Best value found: ", best_val)
print ("Best position: ", best_pos)
