import random
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import style

import numpy as np
import matplotlib.patches as mpatches

#plt.rcdefaults()
fig, ax = plt.subplots()

fig.set_size_inches(7, 3.5)


#stride = ['stride-1', 'stride-2', 'stride-4', 'stride-8', 'stride-16', 'stride-32', 'stride-64', 'stride-128', 'stride-256', 'stride-512', 'stride-1024', 'stride-2048', 'stride-4096', 'stride-8192']
#stride = ['1', '2', '4', '8', '16', '32', '64', '128', '256', '512', '1024', '2048', '4096', '8192']
#stride = ['1', '2', '4', '8', '16', '32', '64', '128', '256', '512', '1024', '2048', '4096', '8192']

stride=["Stream", "Jacobi","Laplace", "XSBench", "Vecmul-50", "Vecmul-200"]
#gcc=[25338856, 9441832, 6860474, 426155, 10896302, 2338203]
#gccp=[25080477, 9310190, 6775994, 472839, 16974365, 2346605]
#omp=[25046979, 9272076, 6603716, 665453, 11066649, 2504817]
#ompp=[25033750, 9145806, 6597481, 879404, 19813172, 2529047]

gcc=[25338856, 9441832, 6860474, 4261550, 10896302, 2338203]
gccp=[25080477, 9310190, 6775994, 4728390, 16974365, 2346605]
omp=[25046979, 9272076, 6603716, 6654530, 11066649, 2504817]
ompp=[25033750, 9145806, 6597481, 8794040, 19813172, 2529047]


#bwell=[3.54690440734318, 3.13407754775781, 3.01531589890099, 2.98962687482247, 2.99217907426445, 3.83323579642171, 6.0207244000754, 3.74593114800149, 3.90623462499754, 5.27340671385718, 4.88429059812411, 9.92533458774915, 12.9654468646394, 15.7118505092353]
#slake=[0.184212033008842, 0.174271763326455, 0.202333780400265, 0.227083158730729, 0.146058357519289, 11.0937423980139, 21.1548362684466, 16.4979702994637, 0.341867258556249, 0.428999663529676, 0.949615842990085, 2.37499000319898, 3.74332209671378, 6.20798117556665]

def average(lst):
    return sum(lst) / len(lst)

#print("accurcy")
#print("Broadwell showed {:.1f}".format((100-average(bwell)))+"\% accuracy, Sky Lake showed {:.1f}".format((100-average(slake)))+"\% accuracy, and Cascade Lake showed {:.1f}".format((100-average(slake)))+"\% accuracy")



barwidth1=.25
barwidth=.15
# Set position of bar on X axis
r1 = np.arange(len(gcc))
r2 = [x + barwidth for x in r1]
r3 = [x + barwidth for x in r2]
r4 = [x + barwidth for x in r3]
#r3 = [x + barwidth for x in r2]


x_pos = np.arange(len(stride))  # the label locations
#ax.barh(x_pos, read, hatch='....', color='white', edgecolor='black')
#rects1 = plt.bar(x, traffic, .8, hatch='....', color='white', edgecolor='black')
plt.bar(r1, gcc, width=barwidth, hatch='....', color='white', edgecolor='black', label='Sequential')
plt.bar(r2, omp, width=barwidth, hatch='////', color='white', edgecolor='black', label='Multi-threaded')
plt.bar(r3, gccp, width=barwidth, hatch='....', color='grey', edgecolor='black', label='Sequential and prefetching')
plt.bar(r4, ompp, width=barwidth, hatch='////', color='grey', edgecolor='black', label='Multi-threaded and prefetching')
#

#plt.bar(r3, clake, width=barwidth, hatch='oo', color='white', edgecolor='black', label='Cascade Lake')

#plt.legend(handlelength=3, fontsize=12)

plt.legend(loc="upper center", fontsize=10)


ax.set_ylabel('Total traffic', fontsize=16)
#ax.set_xlabel('application', fontsize=16)


#plt.title('', fontsize=18)
#ax.set_xticks(x_pos)

plt.yticks(fontsize=14)
#plt.yticks(np.arange(0, 100, 10), fontsize=14)
#ax.get_yaxis().get_major_formatter().set_scientific(False)

plt.xticks([r + barwidth for r in range(len(gcc))], stride, fontsize=12, rotation=90)

#plt.xticks(rotation=90, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('omp.png', dpi=100)

# Example data
