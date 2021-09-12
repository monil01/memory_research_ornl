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

read=[800000800,1199420576,1199616416,1199429920,599708064,299862112,149854336,74863872,37356192,18602016,9222240,4533120,2186144,1013152]
write=[399888448,400825440,401014272,400811072,201077184,101228320,51176864,26263168,13756288,7435680,4239136,2638624,1888768,1444704]

readp=[800000000,1200000000,1200000000,1200000000,600000000,300000000,150000000,75000000,37500000,18750000,9375000,4687500,2343750,1171875]
writep=[400000000,400000000,400000000,400000000,200000000,100000000,50000000,25000000,12500000,6250000,3125000,1562500,781250,390625]

readi=[13171615,18823643,18801890,18801483,18800558,9415883,4698887,2349495,1175287,587742,294012,147303,73686,36900]
writei=[7151216,6608016,6587184,6584156,6586975,3296237,1644959,822515,411790,205808,103543,56143,29479,14986]


read = np.array(read) / 1000000
write = np.array(write) / 1000000
readp = np.array(readp) / 1000000
writep = np.array(writep) / 1000000

readi = np.array(readi) / 1000000 * 64
writei = np.array(writei) / 1000000 * 64


x_pos = np.arange(len(stride))  # the label locations

#ax.barh(x_pos, read, hatch='....', color='white', edgecolor='black')
#rects1 = plt.bar(x, traffic, .8, hatch='....', color='white', edgecolor='black')
#plt.plot(stride, readp, marker='x', markersize=4,  color='grey', linestyle='solid', label="Predicted-read", linewidth=2)
#plt.plot(stride, writep, marker='v', markersize=4,  color='grey', linestyle='solid', label="Predicted-write", linewidth=2)


plt.plot(stride, read, marker='o', markersize=10,  color='blue', linestyle='dashed', label="Read - P100", linewidth=2)
plt.plot(stride, write, marker='*', markersize=10,  color='blue', linestyle='dashed', label="Write - P100", linewidth=2)



plt.plot(stride, readi, marker='s', markersize=7,  color='green', linestyle='dashdot', label="Read-Intel", linewidth=1.5)
plt.plot(stride, writei, marker='<', markersize=7,  color='green', linestyle='dashdot', label="Write-Intel", linewidth=1.5)


#plt.plot(stride, read, "-b", label="Read")
#plt.plot(stride, write, "-r", label="Write")
#plt.legend()
plt.legend(loc="upper right", handlelength=2, fontsize=16)

#plt.legend(loc="upper right", fontsize=12)


ax.set_ylabel('Read/Write in MBytes', fontsize=16)
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




#plt.title('P100 : LLC - DRAM Bytes vs Stride', fontsize=18)
#ax.set_xticks(x_pos)
plt.yticks(np.arange(0, max(read)+1, 100), fontsize=14)
#ax.get_yaxis().get_major_formatter().set_scientific(False)


plt.xticks(rotation=90, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('gpu_p100.png', dpi=100)

# Example data
