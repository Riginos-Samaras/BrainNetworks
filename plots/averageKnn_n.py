import matplotlib.pyplot as plt
import numpy as np


x=[]
y=[]

results = []
with open('averageKnn_n.dat') as inputfile:
    for line in inputfile:
        x.append(line.strip().split(' ')[0])
        y.append(line.strip().split(' ')[1])


#t = np.arange(0.0, 2.0, 0.01)
#s = np.sin(2*np.pi*t)

plt.xlabel('Degree K')
plt.ylabel('<K>nn(K)')
plt.title('Neighboring node\'s degree versus Degree')

plt.grid(True)
# ,s=100
# , marker='*'
plt.scatter(x, y, color='g',marker='^',facecolors='none')
plt.loglog(x,y, color='g',alpha=0.6)
plt.xlim(0.9)
plt.ylim(0.8)

plt.savefig("averageKnn_n.png")

plt.show()