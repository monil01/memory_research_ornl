import random
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import style

import numpy as np
import matplotlib.patches as mpatches

from matplotlib.patches import Ellipse

#plt.rcdefaults()
fig, ax = plt.subplots()

fig.set_size_inches(7, 5)

#labels = ['Manaul', 'PAPI']
#traffic = [12.46, 18.75]

#stride = ['stride-1', 'stride-2', 'stride-4', 'stride-8', 'stride-16', 'stride-32', 'stride-64', 'stride-128', 'stride-256', 'stride-512', 'stride-1024', 'stride-2048', 'stride-4096', 'stride-8192']
stride = ['1', '2', '4', '8', '16', '32', '64', '128', '256', '512', '1024', '2048', '4096', '8192']

read=[19083795,19005683,18970043,18940397,18938589,9468337,4724431,2363247,1182735,594024,296881,149252,75072,37848]
write=[6824619,6755515,6740634,6725749,6734401,3368188,1676038,839272,420643,212602,106874,58650,31081,15670]

#with prefetch
#read=[18861923,18813995,18800278,18803630,18803353,18590975,14190254,2364840,1183868,594090,297740,149395,75338,37868]
#write=[6665144,6625435,6662691,6637524,6645248,3644694,2029784,839811,421381,212587,106996,58520,31292,15906]

#with 500M
#read=[95096032,94854667,94794684,94762290,94749534,47332587,23620261,11811849,6016970,2959146,1481325,743100,373174,188464]
#write=[32795417,32568573,32412027,32481545,32375031,16234319,8085510,4046707,2116022,1016951,510146,257767,132420,68704]
read = np.array(read) / 1000000 * 64
write = np.array(write) / 1000000 * 64
x_pos = np.arange(len(stride))  # the label locations

#ax.barh(x_pos, read, hatch='....', color='white', edgecolor='black')
#rects1 = plt.bar(x, traffic, .8, hatch='....', color='white', edgecolor='black')

plt.plot(stride, read, marker='o', markersize=10,  color='black', linestyle='dashed', label="Read", linewidth=2)
plt.plot(stride, write, marker='<', markersize=10,  color='black', linestyle='solid', label="Write", linewidth=1)

#plt.plot(stride, read, "-b", label="Read")
#plt.plot(stride, write, "-r", label="Write")
#plt.legend()
plt.legend(handlelength=3, fontsize=20)

#plt.legend(loc="upper right", fontsize=12)

ax.set_ylabel('Read/Write in MBytes', fontsize=15)

ax.set_xlabel('Stride', fontsize=16)



#plt.title('', fontsize=18)
#ax.set_xticks(x_pos)
plt.yticks(np.arange(0, max(read)+1, 100), fontsize=14)

#ax.get_yaxis().get_major_formatter().set_scientific(False)


plt.xticks(rotation=90, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('read_write_sk.png', dpi=100)

# Example data
