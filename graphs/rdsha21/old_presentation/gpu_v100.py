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
read_v100=[800010688,1198831296,1198840064,1198846144,999422144,499715200,249715552,124718976,62215968,30974624,15344832,7508864,3605696,1695360]
write_v100=[400020352,402240416,402366624,402580736,203197216,103305408,53417856,28532832,16317568,10072096,7058304,5051744,3220384,2537760]


read_p100=[800000800,1199420576,1199616416,1199429920,599708064,299862112,149854336,74863872,37356192,18602016,9222240,4533120,2186144,1013152]
write_p100=[399888448,400825440,401014272,400811072,201077184,101228320,51176864,26263168,13756288,7435680,4239136,2638624,1888768,1444704]


read_v100 = np.array(read_v100) / 1000000
write_v100 = np.array(write_v100) / 1000000
read_p100 = np.array(read_p100) / 1000000
write_p100 = np.array(write_p100) / 1000000


x_pos = np.arange(len(stride))  # the label locations

#ax.barh(x_pos, read, hatch='....', color='white', edgecolor='black')
#rects1 = plt.bar(x, traffic, .8, hatch='....', color='white', edgecolor='black')

plt.plot(stride, read_v100, marker='o', markersize=3,  color='red', linestyle='solid', label="Read - V100", linewidth=2)
plt.plot(stride, write_v100, marker='*', markersize=3,  color='red', linestyle='solid', label="Write - V100", linewidth=2)
plt.plot(stride, read_p100, marker='x', markersize=4,  color='blue', linestyle='dashed', label="Read - P100", linewidth=2)
plt.plot(stride, write_p100, marker='v', markersize=4,  color='blue', linestyle='dashed', label="Write - P100", linewidth=2)



#plt.plot(stride, read, "-b", label="Read")
#plt.plot(stride, write, "-r", label="Write")
#plt.legend()
plt.legend(loc="upper right", handlelength=2, fontsize=15)

#plt.legend(loc="upper right", fontsize=12)


ax.set_ylabel('Read/Write in MBytes', fontsize=15)
ax.set_xlabel('Stride', fontsize=16)


x0, y0 = ax.transAxes.transform((0, 0)) # lower left in pixels
x1, y1 = ax.transAxes.transform((1, 1)) # upper right in pixes
dx = x1 - x0
dy = y1 - y0
maxd = max(dx, dy)
width = 1.5 * maxd / dx
height = 1.5 * maxd / dy

#ax.axis('equal')

#ax.set_aspect('equal')




x=2
y=17.5
circle = Ellipse((x, y), width-.7, height, color="black")
#circle = plt.Circle((x, y), radius=1, color="black")
#ax.add_patch(circle)
#label = ax.annotate("6", xy=(x, y), fontsize=20, weight="bold", ha="center", va="center", color="white")

x=5.5
y=11
circle = Ellipse((x, y), width-.7, height, color="black")
#circle = plt.Circle((x, y), radius=1, color="black")
#ax.add_patch(circle)
#label = ax.annotate("7", xy=(x, y), fontsize=20, weight="bold", ha="center", va="center", color="white")


x=8.5
y=2.2
circle = Ellipse((x, y), width-.7, height, color="black")
#circle = plt.Circle((x, y), radius=1, color="black")
#ax.add_patch(circle)
#label = ax.annotate("8", xy=(x, y), fontsize=20, weight="bold", ha="center", va="center", color="white")






plt.title('V100 vs P100 : LLC - DRAM Bytes vs Stride', fontsize=18)
#ax.set_xticks(x_pos)
plt.yticks(np.arange(0, max(read_v100)+100, 200), fontsize=14)
#ax.get_yaxis().get_major_formatter().set_scientific(False)


plt.xticks(rotation=90, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('gpu_v100.png', dpi=100)

# Example data
