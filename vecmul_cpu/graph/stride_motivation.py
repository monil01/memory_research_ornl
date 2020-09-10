import random
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import style

import numpy as np
import matplotlib.patches as mpatches

#plt.rcdefaults()
fig, ax = plt.subplots()

fig.set_size_inches(7, 3.2)

#labels = ['Manaul', 'PAPI']
#traffic = [12.46, 18.75]

#stride = ['stride-1', 'stride-2', 'stride-4', 'stride-8', 'stride-16', 'stride-32', 'stride-64', 'stride-128', 'stride-256', 'stride-512', 'stride-1024', 'stride-2048', 'stride-4096', 'stride-8192']
stride = ['1', '2', '4', '8', '16', '32', '64', '128', '256', '512', '1024', '2048', '4096', '8192']
read = [13058939, 13019508, 12935173, 12891315, 12879236, 6609380, 3474199, 1985516, 1118506, 730145, 531435, 432230, 382032, 353338]
write = [6912853, 6874974, 6793000, 6757685, 6742949, 6559251, 6445801, 6442060, 6357768, 6377454, 6353869, 6334685, 6347598, 6316528]
read = np.array(read) / 1000000
write = np.array(write) / 1000000
x_pos = np.arange(len(stride))  # the label locations

#ax.barh(x_pos, read, hatch='....', color='white', edgecolor='black')
#rects1 = plt.bar(x, traffic, .8, hatch='....', color='white', edgecolor='black')

plt.plot(stride, read, marker='o', markersize=5,  color='black', linestyle='dashed', label="Read", linewidth=2)
plt.plot(stride, write, marker='*', markersize=5,  color='black', linestyle='solid', label="write", linewidth=1)

#plt.plot(stride, read, "-b", label="Read")
#plt.plot(stride, write, "-r", label="Write")
#plt.legend()
plt.legend(handlelength=3, fontsize=16)

#plt.legend(loc="upper right", fontsize=12)


ax.set_ylabel('Read/Write traffic', fontsize=16)
ax.set_xlabel('Stride', fontsize=16)


#plt.title('', fontsize=18)
#ax.set_xticks(x_pos)
plt.yticks(np.arange(0, max(read)+1, 2), fontsize=14)
#ax.get_yaxis().get_major_formatter().set_scientific(False)


plt.xticks(rotation=90, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('stride_motivation.png', dpi=100)

# Example data
