# -*- coding: utf-8 -*-

from __future__ import division
from matplotlib.pyplot import *
from numpy import *

file = open("positions.txt", "r")

x = []
y = []
z = []

numberOfBodies = 9

for line in file:
    word = line.split()
    x.append(float(word[0]))
    y.append(float(word[1]))
    z.append(float(word[2]))



pos_jordx = [] 
pos_jordy = []
pos_jordz = []
pos_jupx = []
pos_jupy = []
pos_jupz = []
pos_marsx = []
pos_marsy = []
pos_sunx = []
pos_suny = []
pos_venusx = []
pos_venusy = []
pos_saturnx = []
pos_saturny = []
pos_mercuryx = []
pos_mercuryy = []
pos_uranusx = []
pos_uranusy = []
pos_neptunx = []
pos_neptuny = []

count = 0

for i in range(len(x)):
    if i % numberOfBodies == 1:
        pos_jordx.append(x[i])
        pos_jordy.append(y[i])
    
    elif i % numberOfBodies == 2:
        pos_jupx.append(x[i])
        pos_jupy.append(y[i])

    elif i % numberOfBodies == 0:
        pos_sunx.append(x[i])
        pos_suny.append(y[i])            
            
    elif i % numberOfBodies == 3:
        pos_marsx.append(x[i])
        pos_marsy.append(y[i])            
           
    elif i % numberOfBodies == 4:
        pos_venusx.append(x[i])
        pos_venusy.append(y[i])        
           
    elif i % numberOfBodies == 5:
        pos_saturnx.append(x[i])
        pos_saturny.append(y[i])

    elif i % numberOfBodies == 6:
        pos_mercuryx.append(x[i])
        pos_mercuryy.append(y[i])           

    elif i % numberOfBodies == 7:
        pos_uranusx.append(x[i])
        pos_uranusy.append(y[i])
        
    elif i % numberOfBodies == 8:
        pos_neptunx.append(x[i])
        pos_neptuny.append(y[i])        

plot(pos_sunx, pos_suny, label = 'Sun')
plot(pos_jordx, pos_jordy, label = 'Earth')
plot(pos_jupx, pos_jupy, label = 'Jupiter')
plot(pos_marsx, pos_marsy, label = 'Mars')
plot(pos_venusx, pos_venusy, label = 'Venus')
plot(pos_saturnx, pos_saturny, label = 'Saturn')
plot(pos_mercuryx, pos_mercuryy, label = 'Mercury')
plot(pos_uranusx, pos_uranusy, label = 'Uranus')
plot(pos_neptunx, pos_neptuny, label = 'Neptun')
xlabel('$x[AU]$', fontsize = 18)
ylabel('$y[AU]$', fontsize = 18)
title('Solar system')
legend()
show()
