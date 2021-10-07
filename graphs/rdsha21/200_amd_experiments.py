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

total_MI50_200M=[0.00298657746755297,0.00298657746755297,0.00290124915842442,0.00285858494925158,0.00312310245926399,0.00291831483189995,0.00383985254966209,0.00547809988777575,0.0103925198430576,0.0194010352679083,0.0406874385849984]
total_MI60_200M=[0.124218838223607,0.0542425614770352,0.0363387901230145,0.0272139253400035,0.00783298639517775,0.0251328817945799,0.0779168423163659,0.192703138030841,0.562627788955776,1.14163224813735,2.4093309296153]
total_MI100_200M=[0.132900472927973,0.0631920424077447,0.036509332484861,0.00883122002664725,0.00639959042621272,0.0167395973896466,0.0228811633254367,0.0758719907009487,0.288089247935437,0.82357373826005,2.17470789524298]


def average(lst):
    return sum(lst) / len(lst)

print("accurcy")
print("Broadwell showed {:.3f}".format((100-average(total_MI50_200M)))+"\% accuracy, Sky Lake showed {:.1f}".format((100-average(total_MI60_200M)))+"\% accuracy, and Cascade Lake showed {:.1f}".format((100-average(total_MI100_200M)))+"\% accuracy")


barwidth=.25
# Set position of bar on X axis
r1 = np.arange(len(total_MI50_200M))
r2 = [x + barwidth for x in r1]
r3 = [x + barwidth for x in r2]


x_pos = np.arange(len(stride))  # the label locations
#ax.barh(x_pos, read, hatch='....', color='white', edgecolor='black')
#rects1 = plt.bar(x, traffic, .8, hatch='....', color='white', edgecolor='black')
plt.bar(r1, total_MI50_200M, width=barwidth, hatch='....', color='white', edgecolor='black', label='MI50')
plt.bar(r2, total_MI60_200M, width=barwidth, hatch='////', color='grey', edgecolor='black', label='MI60')
plt.bar(r3, total_MI100_200M, width=barwidth, hatch='oo', color='white', edgecolor='black', label='MI100')

#plt.legend(handlelength=3, fontsize=12)

plt.legend(loc="upper left", fontsize=18)


ax.set_ylabel('Error', fontsize=18)
ax.set_xlabel('Stride', fontsize=18)


#plt.title('', fontsize=18)
#ax.set_xticks(x_pos)

plt.yticks(fontsize=16)
#plt.yticks(np.arange(0, 100, 10), fontsize=14)
#ax.get_yaxis().get_major_formatter().set_scientific(False)

plt.xticks([r + barwidth for r in range(len(total_MI50_200M))], stride, fontsize=16, rotation=90)

#plt.xticks(rotation=90, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('200_amd_experiments.png', dpi=100)

# Example data
