import matplotlib.pyplot as plt
import numpy as np
import sys

filename = sys.argv[1]
f = sys.argv[2]
title = sys.argv[3]

intOk = True
if f == "F":
    intOk = False
 

xpoints = []
ypoints = []

firstLine = True

# Open the file in read mode
with open(filename, 'r') as file:
    # Read each line in the file
    for line in file:
                
        if firstLine:
            firstLine = False
            continue
        
        # Print each line
        rl = line.strip()
        spl = rl.split()
        
        xpoints.append(int(spl[1]))
        
        if not intOk:
            ypoints.append(float(spl[0]))
        else:
            ypoints.append(int(spl[0]))
        # print(spl[0], spl[1])

xpoints = np.array(xpoints)
ypoints = np.array(ypoints)

plt.plot(xpoints, ypoints)
plt.title(title)
plt.show()