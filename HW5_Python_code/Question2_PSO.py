# Particle swarm optimization for Schwefel minimization problem
# DSA5113-HW5, Dr. Charles Nicholson
# Student name: Genwei Zhang
# Date: 05/06/2018
#------------------------------------------------------------------------------


#need some python libraries
import copy
import math
from random import Random
import numpy as np 


#to setup a random number generator, we will specify a "seed" value
seed = 12345
myPRNG = Random(seed)

#to get a random number between 0 and 1, write call this:             myPRNG.random()
#to get a random number between lwrBnd and upprBnd, write call this:  myPRNG.uniform(lwrBnd,upprBnd)
#to get a random integer between lwrBnd and upprBnd, write call this: myPRNG.randint(lwrBnd,upprBnd)


#number of dimensions of problem
n = 200

#number of particles in swarm
swarmSize =50

      
#Schwefel function to evaluate a real-valued solution x    
# note: the feasible space is an n-dimensional hypercube centered at the origin with side length = 2 * 500
               
def evaluate(x):          
      val = 0
      d = len(x)
      for i in range(d):
            val = val + x[i]*math.sin(math.sqrt(abs(x[i])))
                                        
      val = 418.9829*d - val         
                    
      return val          
          
# update the position          
def updatePos (position):
      # just add the velocity to the position
      newpos=np.array(position)+np.array(vel)
      
      # limit the range of position between -500 and 500
      for i in range(swarmSize):
            for j in range(n):
                  # if a paticular dimension exceed the limit, randomly update to a position within the global best
                  if newpos[i][j]> 500 or newpos[i][j]< -500:
                        d=myPRNG.randint(0, n-1)
                        newpos[i][j]=gbest[d]    

      return newpos

# update the velocity
def updateVel (velocity):
      w=0.99   # inertia weight
      phi1=10  # cognitive constant
      phi2=1  # social constant, small compared with cognitive constant to explore as much the space as possible
      
      r1=myPRNG.random()  # r1 and r2 ~ (0,1)
      r2=myPRNG.random()
      newvel=[]
      for i in range(swarmSize):

            vel_cogn = phi1*r1*(np.array(pBest[i])-np.array(pos[i]))
            vel_soci = phi2*r2*(np.array(gbest)-np.array(pos[i]))
            newvel.append(w*np.array(velocity[i])+vel_cogn+vel_soci)

      # limit the range of velocity between -1000 and 1000
      # define Vmax to be the same to the width of jth dimension, make sure particles can freely move to search the entire space!
      Vmax=1000
      for i in range(swarmSize):
            for j in range(n):
                  if newvel[i][j]> Vmax:
                        newvel[i][j]=Vmax
                  if newvel[i][j]< -Vmax:
                        newvel[i][j]=-Vmax

      return newvel


#the swarm will be represented as a list of positions, velocities, values, pbest, and pbest values
def initializeSwarm():
      pos = [[] for _ in range(swarmSize)]      #position of particles -- will be a list of lists
      vel = [[] for _ in range(swarmSize)]      #velocity of particles -- will be a list of lists

      curValue = [] #value of current position  -- will be a list of real values
      pBest = []    #particles' best historical position -- will be a list of lists
      pBestVal = [] #value of pbest position  -- will be a list of real values
      

      #initialize the swarm position and velocity randomly
      for i in range(swarmSize):
            for j in range(n):
                  pos[i].append(myPRNG.uniform(-500,500))    #assign random value between -500 and 500
                  vel[i].append(myPRNG.uniform(-1,1))        #assign random value between -1 and 1
                  
            curValue.append(evaluate(pos[i]))   #evaluate the current position
                                                      
      pBest = pos[:]  # initialize pbest to the starting position
      pBestVal = curValue[:]  # initialize pbestval to the starting position
      

      return pos, vel, curValue, pBest, pBestVal


## main code:

# iterations
itr=500000

# swarm nitialization
pos, vel, curValue, pBest, pBestVal=initializeSwarm()

##Global best approach

gbestVal=min(pBestVal)                          # global best value
gbest=pBest[pBestVal.index(min(pBestVal))]             # global best position


'''
## use 'star' for local best, focal point is the first particle!!!

lbestVal=[]   #  store the local best value
lbest=[]    # store the local best position 
for i in range(swarmSize):
      if pBestVal[0]>pBestVal[i] :
            lbestVal.append(pBestVal[i])        #  local best value
            lbest.append(pBest[i])                 # local best position                         
      else:
            lbestVal.append(pBestVal[0])        #  local best value
            lbest.append(pBest[0])               # local best position                  
'''

## create a file to store the data
#f = open('pso_2Dim_5P.txt', 'w')

j=0
while j<itr and gbestVal>0.003:

      #f.write("particle pos is: " + str(pos)+'\n')
      #f.write("particle  vel is: " + str(vel)+'\n')
      #f.write("global best position is "+ str(gbest)+'\n')
      
      # update velocity
      vel=updateVel(vel)
      #update position
      pos=updatePos(pos)

      curValue = [] #value of the current position
      for i in range(swarmSize):
            curValue.append(evaluate(pos[i]))
            if curValue[i] < pBestVal[i]:
                  # update individual best positions and values!
                  pBest[i]=pos[i]
                  pBestVal[i]=curValue[i]
         
      ## update the global best position and value            
      gbestVal=min(pBestVal)
      gbest=pBest[pBestVal.index(min(pBestVal))]
      '''
      ## update the local best value and position
      for i in range(swarmSize):
            if pBestVal[0]>pBestVal[i] :
                  lbestVal[i]=pBestVal[i]         # local best value
                  lbest[i]=pBest[i]                # local best position                         
            else:
                  lbestVal[i]=pBestVal[0]        # local best value
                  lbest[i]=pBest[0]                # local best position  
      '''
      
      j+=1  
      
      if j % 100 == 0:

           print ("global best value is: " , gbestVal)
      #f.write("paticle best value is: " + str(pBestVal)+'\n')
      #f.write("global best value at iteration " +str(j) + " is " + str(gbestVal)+'\n')
      

print ("global best position is ", gbest)
#f.write("global best position is "+ str(gbest))
#f.write("steps took to converge is "+ str(j))
#f.close()
          
                                                                          


