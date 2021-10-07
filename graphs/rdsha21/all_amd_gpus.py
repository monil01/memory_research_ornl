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

read_mi50=[800036864,800036864,800035840,800035840,800030720,400017408,200010752,100007936,50007040,25008128,12508160,6259712,3132416,1568768]
write_mi50=[400000000,400000000,400000000,400000000,199999488,99999744,49999872,24999936,12499968,6249472,3124224,1561600,780288,390144]

read_mi60=[801601536,800580608,800454656,800311296,800093184,400144384,200140800,100259840,50509824,25374720,12894208,6599680,3445760,1967104]
write_mi60=[400000000,400000000,400000000,400000000,199999488,99999744,49999872,24999936,12499968,6249472,3124224,1561600,780288,390144]

read_mi100=[801411072,800720896,800409600,800125952,800070656,400084992,200059904,100107264,50185216,25262080,12862464,6637568,3526656,1972224]
write_mi100=[400000000,400000000,400000000,400000000,199999488,99999744,49999872,24999936,12499968,6249472,3124224,1561600,780288,390144]

read=[13159180,13034186,12938265,12891037,12906523,6616530,3468820,1907931,1120988,722937,528230,430157,376966,364022]

writei=[6824619,6755515,6740634,6725749,6734401,3368188,1676038,839272,420643,212602,106874,58650,31081,15670]



read_mi50 = np.array(read_mi50) / 1000000
write_mi50 = np.array(write_mi50) / 1000000

read_mi100 = np.array(read_mi100) / 1000000
write_mi100 = np.array(write_mi100) / 1000000

read_mi60 = np.array(read_mi60) / 1000000
write_mi60 = np.array(write_mi60) / 1000000



read = np.array(read) / 1000000 * 64
writei = np.array(writei) / 1000000 * 64


x_pos = np.arange(len(stride))  # the label locations

#ax.barh(x_pos, read, hatch='....', color='white', edgecolor='black')
#rects1 = plt.bar(x, traffic, .8, hatch='....', color='white', edgecolor='black')
#plt.plot(stride, readp, marker='x', markersize=4,  color='grey', linestyle='solid', label="Predicted-read", linewidth=2)
#plt.plot(stride, writep, marker='v', markersize=4,  color='grey', linestyle='solid', label="Predicted-write", linewidth=2)


plt.plot(stride, read_mi50, marker='s', markersize=10,  color='blue', linestyle='solid', label="Read - MI50", linewidth=2)
plt.plot(stride, write_mi50, marker='*', markersize=10,  color='blue', linestyle='solid', label="Write - MI50", linewidth=2)

plt.plot(stride, read_mi60, marker='o', markersize=10,  color='red', linestyle='dashed', label="Read - MI50", linewidth=2)
plt.plot(stride, write_mi60, marker='^', markersize=10,  color='red', linestyle='dashed', label="Write - MI50", linewidth=2)




plt.plot(stride, read_mi100, marker='+', markersize=10,  color='green', linestyle='dashdot', label="Read - MI100", linewidth=2)
plt.plot(stride, write_mi100, marker='>', markersize=7,  color='green', linestyle='dashdot', label="Write - MI100", linewidth=2)


#plt.plot(stride, read, "-b", label="Read")
#plt.plot(stride, write, "-r", label="Write")
#plt.legend()
plt.legend(loc="upper right", handlelength=2, fontsize=16)

#plt.legend(loc="upper right", fontsize=12)


ax.set_ylabel('Read/Write in MBytes', fontsize=16)
ax.set_xlabel('Stride', fontsize=16)


#plt.yscale("log")

#plt.title('P100 : LLC - DRAM Bytes vs Stride', fontsize=18)
#ax.set_xticks(x_pos)
plt.yticks(np.arange(0, max(read)+1, 100), fontsize=14)
#ax.get_yaxis().get_major_formatter().set_scientific(False)


plt.xticks(rotation=90, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('all_amd_gpu.png', dpi=100)

# Example data
