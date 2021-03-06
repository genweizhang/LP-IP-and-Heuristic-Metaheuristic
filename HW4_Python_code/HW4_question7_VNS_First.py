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
          
       

# 4 neighborhood structures of solution x         
def neighborhood(x):
    # swap neighbors
    nbrhood3 =[]
    for i in range(0,n-1):
        nbrhood3.append(x[:])
        mid=nbrhood3[i][i]
        nbrhood3[i][i] = nbrhood3[i][i+1]
        nbrhood3[i][i+1]=mid

    # one-flip     
    nbrhood1 = []     
    for i in range(0,n):
        nbrhood1.append(x[:])
        if nbrhood1[i][i] == 1:
            nbrhood1[i][i] = 0
        else:
            nbrhood1[i][i] = 1

    # two-flip 
    nbrhood2 = []
    k=0     
    for i in range(0,n):
        for j in range (0, n):
            if j>i:
                nbrhood2.append(x[:])
                if nbrhood2[k][i] == 1:
                    nbrhood2[k][i] = 0
                else:
                    nbrhood2[k][i] = 1
                if nbrhood2[k][j] == 1:
                    nbrhood2[k][j] = 0
                else:
                    nbrhood2[k][j] = 1
                k+=1
    
    
    # 3-flip
    nbrhood4 = []
    k=0     
    for i in range(0,n):
        for j in range (0, n):
            for l in range(0,n):
                if j>i and l>j:
                    nbrhood4.append(x[:])
                    if nbrhood4[k][i] == 1:
                        nbrhood4[k][i] = 0
                    else:
                        nbrhood4[k][i] = 1
                    if nbrhood4[k][j] == 1:
                        nbrhood4[k][j] = 0
                    else:
                        nbrhood4[k][j] = 1
                    if nbrhood4[k][l] == 1:
                        nbrhood4[k][l] = 0
                    else:
                        nbrhood4[k][l] = 1
                    k+=1
    nbrhood= [nbrhood3, nbrhood1, nbrhood2, nbrhood4]

    return nbrhood
          


#create the initial solution
def initial_solution():
    x = []   #i recommend creating the solution as a list

    # this initial solution is trying to get ~15% of the items selected, using randomly generate 0 and 1. 
    for i in range(0,n):
        mynumber=myPRNG.random()
        if mynumber > 0.15:
            x.append(0)
        else:
            x.append(1)
    return x

#varaible to record the number of solutions evaluated
solutionsChecked = 0

x_curr = initial_solution()  #x_curr will hold the current solution 
x_best = x_curr[:]           #x_best will hold the best solution 
f_curr = evaluate(x_curr)   #f_curr will hold the evaluation of the current soluton 
f_best = f_curr[:]



#begin local search overall logic ----------------
done = 0

## variable neighborhood search
id = 0      # neighborhood ID

while done == 0:
    if id > 3:  # when all neighbohood has been tried and still no improvement, stop!
        break

    Neighborhood = neighborhood(x_curr)[id]   #create a list of all neighbors in the neighborhood of x_curr
    
    for s in Neighborhood:                     #evaluate every member in the neighborhood of x_curr
        solutionsChecked = solutionsChecked + 1
        if evaluate(s)[0] > f_best[0]:   
            x_best = s[:]                 #find the best member and keep track of that solution
            f_best = evaluate(s)[:]       #and store its evaluation, don't forget to include [:] !!! 
            break                         # this is the  first accept local search!!!
    if f_best == f_curr:               #if there were no improving solutions in the neighborhood, change to next neighborhood structure
        id += 1                        
    else:                               #else: move to the neighbor solution and continue evalute the current solution         
        x_curr = x_best[:]         
        f_curr = f_best[:]         
        id = 0

        print ("\nTotal number of solutions checked: ", solutionsChecked)
        print ("Best value found so far: ", f_best) 
      
    
print ("\nFinal number of solutions checked: ", solutionsChecked)
print ("Best value found: ", f_best[0])
print ("Weight is: ", f_best[1])
print ("Total number of items selected: ", np.sum(x_best))
print ("Best solution: ", x_best)
