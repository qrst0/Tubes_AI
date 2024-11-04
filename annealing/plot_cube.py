import matplotlib.pyplot as plt
import sys

filename = sys.argv[1]
title = sys.argv[2]

array_state = []

with open(filename, 'r') as file:
    # Read each line in the file
    u = file.readline()
    array_state = u.split()

fig = plt.figure(figsize=(8, 8))
ax = fig.add_subplot(111, projection='3d')

size = 5

takeColor = ["#3a86ff", "#8338ec", "#ff006e", "#fb5607", "#ffbe0b"]

for i in range(size):
    for j in range(size):
        for k in range(size):
            integer = i * size * size + j * size + k
            
            color = takeColor[i]
            ax.text(i, j, k, array_state[integer], color=color, weight='bold', ha='center', va='center')
            
            if i < size - 1:  
                ax.plot([i, i+1], [j, j], [k, k], color="gray", linewidth=0.25)
            if j < size - 1: 
                ax.plot([i, i], [j, j+1], [k, k], color="gray", linewidth=0.25)
            if k < size - 1:
                ax.plot([i, i], [j, j], [k, k+1], color="gray", linewidth=0.25)

ax.set_axis_off()

ax.set_title(title, pad=20)

plt.show()