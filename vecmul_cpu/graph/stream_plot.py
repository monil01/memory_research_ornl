
import random
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import style

import numpy as np
import matplotlib.patches as mpatches

plt.rcdefaults()
fig, ax = plt.subplots()

fig.set_size_inches(5, 1.5)

labels = ['PAPI Preset', 'Manual']
traffic = [12.46, 18.75]

y_pos = np.arange(len(labels))  # the label locations

ax.barh(y_pos, traffic,hatch='....', color='white', edgecolor='black')
#rects1 = plt.bar(x, traffic, .8, hatch='....', color='white', edgecolor='black')

ax.set_xlabel('Cacheline transferred between LLC-DRAM', fontsize=12)
#plt.title('', fontsize=18)
ax.set_yticks(y_pos)
ax.set_yticklabels(labels, fontsize=12)
ax.set_xlim([0,20])

ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('stream.png', dpi=100)

# Example data
