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
stride = ['1', '2', '4', '8', '16', '32', '64', '128', '256', '512', '1024', '2048', '4096', '8192']

bwell=[3.54690440734318, 3.13407754775781, 3.01531589890099, 2.98962687482247, 2.99217907426445, 3.83323579642171, 6.0207244000754, 3.74593114800149, 3.90623462499754, 5.27340671385718, 4.88429059812411, 9.92533458774915, 12.9654468646394, 15.7118505092353]
slake=[0.184212033008842, 0.174271763326455, 0.202333780400265, 0.227083158730729, 0.146058357519289, 11.0937423980139, 21.1548362684466, 16.4979702994637, 0.341867258556249, 0.428999663529676, 0.949615842990085, 2.37499000319898, 3.74332209671378, 6.20798117556665]
clake=[0.178640305309618, 0.0810063265509386, 0.0283119820466844, 0.0830909016062243, 0.108453494177452, 10.7181663634212, 24.5665085502451, 16.2601151081759, 0.0753352032835405, 0.0343157716823179, 0.0725005251804828, 0.533458952943573, 1.67514095851792, 4.05917200455849]

barwidth=.25
# Set position of bar on X axis
r1 = np.arange(len(bwell))
r2 = [x + barwidth for x in r1]
r3 = [x + barwidth for x in r2]


x_pos = np.arange(len(stride))  # the label locations
#ax.barh(x_pos, read, hatch='....', color='white', edgecolor='black')
#rects1 = plt.bar(x, traffic, .8, hatch='....', color='white', edgecolor='black')
plt.bar(r1, bwell, width=barwidth, hatch='....', color='white', edgecolor='black', label='Broadwell')
plt.bar(r2, slake, width=barwidth, hatch='////', color='grey', edgecolor='black', label='Sky Lake')
plt.bar(r3, clake, width=barwidth, hatch='oo', color='white', edgecolor='black', label='Cascade Lake')

#plt.legend(handlelength=3, fontsize=12)

#plt.legend(loc="upper right", fontsize=12)


ax.set_ylabel('Error', fontsize=16)
ax.set_xlabel('Stride', fontsize=16)


#plt.title('', fontsize=18)
#ax.set_xticks(x_pos)

plt.yticks(fontsize=14)
#plt.yticks(np.arange(0, 100, 10), fontsize=14)
#ax.get_yaxis().get_major_formatter().set_scientific(False)

plt.xticks([r + barwidth for r in range(len(bwell))], stride, fontsize=12, rotation=90)

#plt.xticks(rotation=90, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('50_init_pref.png', dpi=100)

# Example data
