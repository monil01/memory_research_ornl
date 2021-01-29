import random
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import style

import numpy as np
import matplotlib.patches as mpatches

#plt.rcdefaults()
fig, ax = plt.subplots()

fig.set_size_inches(7, 4)


#stride = ['stride-1', 'stride-2', 'stride-4', 'stride-8', 'stride-16', 'stride-32', 'stride-64', 'stride-128', 'stride-256', 'stride-512', 'stride-1024', 'stride-2048', 'stride-4096', 'stride-8192']
stride = ['1', '2', '4', '8', '16', '32', '64', '128', '256', '512', '1024', '2048', '4096', '8192']

bwell=[8.14668822027081, 7.58285849816773, 5.75658861971854, 6.29732921901148, 6.04906713989209, 6.08954459589655, 4.41437867210293, 3.06620503035453, 2.93694723594845, 0.74109513846772, 1.15160522802623, 0.0444057219416002, 0.717284320581838, 0.322391667743442]
slake=[5.47726720714513, 5.70785789978058, 5.46476195220359, 5.47825833583459, 5.49717156814617, 6.12812144648004, 4.76869911647105, 4.07832756337303, 3.94260153811616, 3.78738818203589, 3.32450566083733, 3.22931497202145, 2.14255305459791, 0.244128375528345]
clake=[8.14188223603137, 7.94136567093757, 6.55601037721669, 6.04682626179112, 6.1602892365101, 6.12188923614611, 5.0608004252941, 3.5167001503009, 4.48448291464933, 3.24616870651873, 2.0117016237512, 2.13085018699738, 1.17109222657508, 0.897816056960041]

def average(lst):
    return sum(lst) / len(lst)

print("accurcy")
print("Broadwell shows {:.1f}".format((100-average(bwell)))+"\% accuracy, Sky Lake shows {:.1f}".format((100-average(slake)))+"\% accuracy, and Cascade Lake shows {:.1f}".format((100-average(clake)))+"\% accuracy")


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


ax.set_ylabel('Error', fontsize=20)
ax.set_xlabel('Stride', fontsize=20)


#plt.title('', fontsize=18)
#ax.set_xticks(x_pos)

plt.yticks(fontsize=20)
#plt.yticks(np.arange(0, 100, 10), fontsize=14)
#ax.get_yaxis().get_major_formatter().set_scientific(False)

plt.xticks([r + barwidth for r in range(len(bwell))], stride, fontsize=20, rotation=90)

#plt.xticks(rotation=90, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('50_non_init_nonp.png', dpi=100)

# Example data
