import matplotlib.pyplot as plt
import numpy as np
import sys

filename = sys.argv[1]
f = sys.argv[2]

intOk = True
if f == "F":
    intOk = False
 
print(filename, intOk)

itrPoints = []
optPoints = []
avgPoints = []

firstLine = True

# Open the file in read mode
with open(filename, 'r') as file:
    # Read each line in the file
    for line in file:
        
        # Print each line
        rl = line.strip()
        spl = rl.split()
        
        itrPoints.append(int(spl[2]))
        
        if not intOk:
            optPoints.append(float(spl[0]))
            avgPoints.append(float(spl[1]))
        else:
            optPoints.append(int(spl[0]))
            avgPoints.append(int(spl[1]))
        # print(spl[0], spl[1])

itrPoints = np.array(itrPoints)
optPoints = np.array(optPoints)
avgPoints = np.array(avgPoints)

plt.plot(itrPoints, optPoints, label = "Optimum")
plt.plot(itrPoints, avgPoints, label = "Average")
plt.legend()  
plt.show()