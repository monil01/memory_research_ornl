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

bwell=[5.04162043501897, 4.63546604271373, 3.74311652908623, 3.47605132726607, 3.16435742666784, 4.13031454368285, 3.37434703222519, 2.61681620663392, 2.35404478590249, 1.95646090126649, 1.58781326512427, 1.47025394381327, 1.293452667997, 1.02507633924204]
slake=[5.25641263002054, 5.30276725516157, 5.17200771130107, 5.22647914550374, 5.20009771822247, 5.91380084369278, 4.79849365532252, 4.27440495586128, 4.20096461347143, 4.31763239263022, 3.6350853000704, 2.90690909251961, 2.63080662354015, 1.75253761315389]
clake=[6.76825290647361, 6.69448507975646, 6.27744009109013, 6.20291573964299, 6.07750099910998, 7.06491891614915, 5.45428369035534, 4.81261254885194, 5.36187555245409, 5.09523056579809, 4.31119703985282, 3.25780477170938, 2.38521968333797, 2.38827498066317]

def average(lst):
    return sum(lst) / len(lst)

print("accurcy")
print("Broadwell shows {:.1f}".format((100-average(bwell)))+"\% accuracy, Sky Lake shows {:.1f}".format((100-average(slake)))+"\% accuracy, and Cascade Lake shows {:.1f}".format((100-average(slake)))+"\% accuracy")
#print("number{:.2f}".format(100-average(slake)))
#print(100-average(clake))

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
fig.savefig('500_non_init_nonp.png', dpi=100)

# Example data
