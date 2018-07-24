#basic hill climbing search provided as base code for the DSA/ISE 5113 course
#author: Charles Nicholson
#date: 4/5/2017

#NOTE: YOU MAY CHANGE ALMOST ANYTHING YOU LIKE IN THIS CODE.  
#However, I would like all students to have the same problem instance, therefore please do not change anything relating to:
#   random number generation
#   number of items (should be 100)
#   random problem instance
#   weight limit of the knapsack

#------------------------------------------------------------------------------

#Student name: Genwei Zhang
#Date: 4/06/2018

#need some python libraries
import copy
from random import Random   # need this for the random number generation -- do not change
import numpy as np


#to setup a random number generator, we will specify a "seed" value
#need this for the random number generation -- do not change
seed = 5113
myPRNG = Random(seed)

#to get a random number between 0 and 1, use this:             myPRNG.random()
#to get a random number between lwrBnd and upprBnd, use this:  myPRNG.uniform(lwrBnd,upprBnd)
#to get a random integer between lwrBnd and upprBnd, use this: myPRNG.randint(lwrBnd,upprBnd)

#number of elements in a solution
n = 100

#create an "instance" for the knapsack problem
value = []
for i in range(0,n):
    value.append(myPRNG.uniform(10,100))
    
weights = []
for i in range(0,n):
    weights.append(myPRNG.uniform(5,20))
    
#define max weight for the knapsack
maxWeight = 5*n

#change anything you like below this line -------------------------


#function to evaluate a solution x
def evaluate(x):
          
    a=np.array(x)
    b=np.array(value)
    c=np.array(weights)
    
    totalValue = np.dot(a,b)     #compute the value of the knapsack selection
    totalWeight = np.dot(a,c)    #compute the weight value of the knapsack selection
    
    if totalWeight > maxWeight:   # if th totalweight exceed the limit, assign 0 to both values and weights to guranttee no improvement
        totalValue=0
        totalWeight=0

    return [totalValue, totalWeight]   #returns a list of both total value and total weight
          
       
#here is a simple function to create a neighborhood
#1-flip neighborhood of solution x         
def neighborhood(x):
        
    nbrhood = []     
    
    for i in range(0,n):
        nbrhood.append(x[:])
        if nbrhood[i][i] == 1:
            nbrhood[i][i] = 0
        else:
            nbrhood[i][i] = 1
      
    return nbrhood
          


restart=200    # define the # of restart 

#create the initial solution
def initial_solution():
    init=[]   #i recommend creating the solution as a list

    # this initial solution is trying to get ~15% of the items selected, using randomly generate 0 and 1.
    for j in range(0, restart):
        x = []
        for i in range(0,n):
            mynumber=myPRNG.random()
            if mynumber > 0.15:
                x.append(0)
            else:
                x.append(1)
        init.append(x[:])
    return init


#varaible to record the number of solutions evaluated
solutionsChecked = 0


#begin local search overall logic ---------

# apply best search together with random restart

myinitial=initial_solution()        #get the initial solution
x_curr = myinitial[0]               #x_curr will hold the first initial solution   
f_curr = evaluate(x_curr)           #f_curr will hold the evaluation of the current soluton 
x_best = x_curr[:]                  #x_best will hold the best solution, initially the current one. 
f_best = f_curr[:]                  #f_best will hold the evaluation of the best solution
overall_bestx= x_best[:]            # hold the best solution among all restarts
overall_bestf= f_best[:]            # hold the evaluation of the best solution among all restarts

for j in range(0, restart):                     
    x_curr = myinitial[j]          #x_curr will hold the first initial solution   
    f_curr = evaluate(x_curr)      #f_curr will hold the evaluation of the current soluton 
    x_best = x_curr[:]             #x_best will hold the best solution 
    f_best = f_curr[:]
    done=0
    while done == 0:         
        Neighborhood = neighborhood(x_curr)   #create a list of all neighbors in the neighborhood of x_curr
        
        for s in Neighborhood:                #evaluate every member in the neighborhood of x_curr
            solutionsChecked = solutionsChecked + 1
            if evaluate(s)[0] > f_best[0]:   
                x_best = s[:]                 #find the best member and keep track of that solution
                f_best = evaluate(s)[:]       #and store its evaluation, don't forget to include [:] !!! 

        if f_best == f_curr and f_best[0]!= 0:
            done=1                             #if there were no improving solutions in the neighborhood, move to next restart
            if f_best[0]>overall_bestf[0]:    # update the best solution after this random restart
                overall_bestf=f_best[:]
                overall_bestx=x_best[:]
        else:                          
            x_curr = x_best[:]         #else: move to the neighbor solution and continue
            f_curr = f_best[:]         #evalute the current solution
            
            print ("\nTotal number of solutions checked: ", solutionsChecked)
            print ("Best value found so far: ", f_best)      



print ("\nFinal number of solutions checked: ", solutionsChecked)
print ("Best value found: ", overall_bestf[0])
print ("Weight is: ", overall_bestf[1])
print ("Total number of items selected: ", np.sum(overall_bestx))
print ("Best solution: ", overall_bestx)

