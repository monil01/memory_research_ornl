import random
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import style

import numpy as np
import matplotlib.patches as mpatches

#plt.rcdefaults()
fig, ax = plt.subplots()

fig.set_size_inches(7, 5)


#stride = ['stride-1', 'stride-2', 'stride-4', 'stride-8', 'stride-16', 'stride-32', 'stride-64', 'stride-128', 'stride-256', 'stride-512', 'stride-1024', 'stride-2048', 'stride-4096', 'stride-8192']
stride = ['1', '2', '4', '8', '16', '32', '64', '128', '256', '512', '1024']

total_MI50_50M=[0.00298657746755297,0.00298657746755297,0.00298657746755297,0.00298657746755297,0.00343028232759503,0.00343028232759503,0.00465898292866739,0.00793537024901704,0.0144875008190813,0.0341387414832285,0.0734180582842174]
total_MI60_50M=[0.125538203499729,0.0565440096610942,0.0323308770966019,0.0159547873747293,0.00977824376598564,0.0218576213993792,0.0603283828923238,0.226965295713865,0.675091537835639,1.1800462243378,2.92156086970353]
total_MI100_50M=[0.124176277473043,0.0597829053298038,0.0408579661092127,0.00947110289713358,0.00732106398097957,0.0177632441109983,0.0259516633634175,0.0930461435212467,0.327983130838069,0.813903649895996,2.52466422320174]



def average(lst):
    return sum(lst) / len(lst)

print("accurcy")
print("Broadwell showed {:.3f}".format((100-average(total_MI50_50M)))+"\% accuracy, Sky Lake showed {:.1f}".format((100-average(total_MI60_50M)))+"\% accuracy, and Cascade Lake showed {:.1f}".format((100-average(total_MI100_50M)))+"\% accuracy")


barwidth=.25
# Set position of bar on X axis
r1 = np.arange(len(total_MI50_50M))
r2 = [x + barwidth for x in r1]
r3 = [x + barwidth for x in r2]


x_pos = np.arange(len(stride))  # the label locations
#ax.barh(x_pos, read, hatch='....', color='white', edgecolor='black')
#rects1 = plt.bar(x, traffic, .8, hatch='....', color='white', edgecolor='black')
plt.bar(r1, total_MI50_50M, width=barwidth, hatch='....', color='white', edgecolor='black', label='MI50')
plt.bar(r2, total_MI60_50M, width=barwidth, hatch='////', color='grey', edgecolor='black', label='MI60')
plt.bar(r3, total_MI100_50M, width=barwidth, hatch='oo', color='white', edgecolor='black', label='MI100')

#plt.legend(handlelength=3, fontsize=12)

plt.legend(loc="upper left", fontsize=18)


ax.set_ylabel('Error', fontsize=18)
ax.set_xlabel('Stride', fontsize=18)


#plt.title('', fontsize=18)
#ax.set_xticks(x_pos)

plt.yticks(fontsize=16)
#plt.yticks(np.arange(0, 100, 10), fontsize=14)
#ax.get_yaxis().get_major_formatter().set_scientific(False)

plt.xticks([r + barwidth for r in range(len(total_MI50_50M))], stride, fontsize=16, rotation=90)

#plt.xticks(rotation=90, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('50_amd_experiments.png', dpi=100)

# Example data
