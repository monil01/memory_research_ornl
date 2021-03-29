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
read1=[18861923,18813995,18800278,18803630,18803353,18590975,14190254,2364840,1183868,594090,297740,149395,75338,37868]
write1=[6665144,6625435,6662691,6637524,6645248,3644694,2029784,839811,421381,212587,106996,58520,31292,15906]

readc=[18706394, 18750993, 18760631, 18766661, 18763123, 16630885, 11066714, 2930101, 1172688, 590092, 292798, 147153, 74118, 37785]
writec=[6258120,6265611,6272502,6270325,6275745,3148710,1580119,789113,391925,199966,98858,50376,25516,14507]

reads=[18765642,18772132,18764571,18759543,18764915,16576687,11395672,2952856,1175004,588251,295965,148305,74884,37756]
writes=[6271286,6264048,6265378,6268979,6266406,3144219,1573146,789636,392824,196725,99267,50322,25902,13290]

readcp=[18909461,18931537,18907056,18934899,18936431,16468747,10983595,2669717,1180263,590775,295572,148110,74962,38080]
writecp=[6279061,6259989,6263780,6257942,6266792,3135475,1580211,785815,391856,196223,98589,49926,25361,13198]




read = np.array(read) / 1000000
write = np.array(write) / 1000000
write1 = np.array(write1) / 1000000
read1 = np.array(read1) / 1000000
writec = np.array(writec) / 1000000
readc = np.array(readc) / 1000000
writes = np.array(writes) / 1000000
reads = np.array(reads) / 1000000

writecp = np.array(writecp) / 1000000
readcp = np.array(readcp) / 1000000


x_pos = np.arange(len(stride))  # the label locations

#ax.barh(x_pos, read, hatch='....', color='white', edgecolor='black')
#rects1 = plt.bar(x, traffic, .8, hatch='....', color='white', edgecolor='black')

plt.plot(stride, read, marker='o', markersize=3,  color='black', linestyle='dashed', label="Read", linewidth=2)
plt.plot(stride, write, marker='*', markersize=3,  color='black', linestyle='solid', label="write", linewidth=2)
plt.plot(stride, read1, marker='x', markersize=4,  color='black', linestyle='dotted', label="RD-BW-Pf", linewidth=2)
plt.plot(stride, write1, marker='v', markersize=4,  color='black', linestyle='dashdot', label="WR-BW-Pf", linewidth=1)

plt.plot(stride, readc, marker='1', markersize=8,  color='blue', linestyle=':', label="RD-CS-Pf", linewidth=2)
plt.plot(stride, writec, marker='s', markersize=4,  color='black', linestyle='dashdot', label="WR-CS-Pf", linewidth=1)

plt.plot(stride, readcp, marker='2', markersize=8,  color='violet', linestyle='-.', label="RD-CP-Pf", linewidth=2)
plt.plot(stride, writecp, marker='P', markersize=4,  color='black', linestyle='dashdot', label="WR-CP-Pf", linewidth=1)




plt.plot(stride, reads, marker='2', markersize=8,  color='green', linestyle='-.', label="RD-SK-Pf", linewidth=2)
plt.plot(stride, writes, marker='P', markersize=4,  color='black', linestyle='dashdot', label="WR-SK-Pf", linewidth=1)


#plt.plot(stride, read, "-b", label="Read")
#plt.plot(stride, write, "-r", label="Write")
#plt.legend()
plt.legend(handlelength=2, fontsize=16)

#plt.legend(loc="upper right", fontsize=12)


ax.set_ylabel('Read/Write in Million', fontsize=15)
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
ax.add_patch(circle)
label = ax.annotate("6", xy=(x, y), fontsize=20, weight="bold", ha="center", va="center", color="white")

x=5.5
y=11
circle = Ellipse((x, y), width-.7, height, color="black")
#circle = plt.Circle((x, y), radius=1, color="black")
ax.add_patch(circle)
label = ax.annotate("7", xy=(x, y), fontsize=20, weight="bold", ha="center", va="center", color="white")


x=8.5
y=2.2
circle = Ellipse((x, y), width-.7, height, color="black")
#circle = plt.Circle((x, y), radius=1, color="black")
ax.add_patch(circle)
label = ax.annotate("8", xy=(x, y), fontsize=20, weight="bold", ha="center", va="center", color="white")






#plt.title('', fontsize=18)
#ax.set_xticks(x_pos)
plt.yticks(np.arange(0, max(read)+1, 2), fontsize=14)
#ax.get_yaxis().get_major_formatter().set_scientific(False)


plt.xticks(rotation=90, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('stride_method_initialization_pref.png', dpi=100)

# Example data
