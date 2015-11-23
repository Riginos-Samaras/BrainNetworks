import matplotlib.pyplot as plt
import numpy as np


x=[]
y=[]

results = []
with open('clusteringCoefficient.dat') as inputfile:
    for line in inputfile:
        x.append(line.strip().split(' ')[0])
        y.append(line.strip().split(' ')[1])


#t = np.arange(0.0, 2.0, 0.01)
#s = np.sin(2*np.pi*t)


plt.xlabel('Degree K')
plt.ylabel('Clustering C')
plt.title('Clustering versus Degree')

plt.grid(True)
# ,s=100
# , marker='*'
plt.scatter(x, y, color='b',marker='^',facecolors='none')
plt.loglog(x,y, color='b',alpha=0.6) 

plt.savefig("clusteringCoefficient.png")

plt.show()