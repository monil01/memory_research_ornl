import random 
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import style

import numpy as np
import matplotlib.patches as mpatches


labels = ['Prediction', 'Broadwell']
#labels = ['Actual', 'Broadwell', '5123 | 4', '345 | 12']
read = [12.5, 13.17]
#time = [52.3626,71.0796,107.572,122.252 ]
write = [6.25, 6.83]
total = [18.75, 20.00]
#energy = [751.589, 1057.12, 889.84, 1143.66]

x = np.arange(len(labels))  # the label locations

width = 0.35  # the width of the bars

fig = plt.figure()

fig.set_size_inches(7, 3)

ax = fig.add_subplot(131)
ax1 = fig.add_subplot(132)
ax2 = fig.add_subplot(133)
#ax2 = fig.add_subplot(132)

#rects1 = ax.bar(x, stand_alone, width, label='Stand Alone')
#rects1 = ax.bar(x - width/2, stand_alone, width, color='cornflowerblue')
#rects1 = ax.bar(x,time, width)
rects1 = ax.bar(x,read, width, hatch='....', color='white', edgecolor='black')
#rects1 = ax.bar(x - width/2, stand_alone, width, label='Stand Alone')
#rects2 = ax.bar(x, collocated, width, label='Collocated')
#rects2 = ax.bar(x + width/2, collocated, width, color='orange')
#rects2 = ax.bar(x + width/2, collocated, width, label='Collocated')

# Add some text for labels, title and custom x-axis tick labels, etc.
ax.set_ylabel('Traffic in Million', fontsize=14)
ax.set_title('Read', fontsize=16)
ax.set_xticks(x)
#ax.set_xticklabels(labels, fontsize=14)
ax.set_xticklabels(labels, fontsize=14, rotation=20)
#ax.set_xticklabels(labels, fontsize=12, rotation='vertical')
#ax.legend(loc=1, bbox_to_anchor=(0.5, 0., 0.5, 0.99))
ax.set_yticks(np.arange(0, max(read)+2, 3))


x = np.arange(len(labels))  # the label locations

width = 0.35  # the width of the bars

rects1 = ax1.bar(x, write, width, hatch='////', color='grey', edgecolor='black')

# Add some text for labels, title and custom x-axis tick labels, etc.
ax1.set_ylabel('Traffic in Million', fontsize=14)
ax1.set_title('Write', fontsize=16)
ax1.set_xticks(x)
ax1.set_xticklabels(labels, fontsize=14, rotation=20)
ax1.set_yticks(np.arange(0, max(write)+2, 2))
#ax1.set_xticklabels(labels, fontsize=12, rotation='vertical')
#ax1.legend(loc=1, bbox_to_anchor=(0.5, 0., 0.5, 0.99))



x = np.arange(len(labels))  # the label locations

width = 0.35  # the width of the bars

rects2 = ax2.bar(x, total, width, hatch='**', color='white', edgecolor='black')

# Add some text for labels, title and custom x-axis tick labels, etc.
ax2.set_ylabel('Traffic in Million', fontsize=14)
ax2.set_title('Total', fontsize=16)
ax2.set_xticks(x)
ax2.set_xticklabels(labels, fontsize=14, rotation=20)
ax2.set_yticks(np.arange(0, max(total)+2, 4))


fig.subplots_adjust(wspace=.5)
plt.tight_layout()
plt.show()
fig.savefig('method-stream.png', dpi=100)

