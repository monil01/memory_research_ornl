import random
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import style

import numpy as np
import matplotlib.patches as mpatches

#plt.rcdefaults()
fig, ax = plt.subplots()

fig.set_size_inches(7, 3.5)


#stride = ['stride-1', 'stride-2', 'stride-4', 'stride-8', 'stride-16', 'stride-32', 'stride-64', 'stride-128', 'stride-256', 'stride-512', 'stride-1024', 'stride-2048', 'stride-4096', 'stride-8192']
stride = ['1', '2', '4', '8', '16', '32', '64', '128', '256', '512', '1024', '2048', '4096', '8192']

bwell=[28.4712883751538, 29.5727035067159, 28.6252655140123, 28.4276704351884, 29.3707498848743, 27.8590886005817, 28.5738774670583, 29.7484432255019, 29.61394657417, 32.3006932409012, 34.4478939419366, 37.4599743836055, 43.2890534262486, 51.0249498495487]
slake=[0.998724863576243, 0.886471399800187, 1.36121522982837, 0.956757720420736, 0.0628394631828789, 1.15920484557114, 0.905328915032265, 1.8653435498053, 3.32858998948215, 6.80543958010259, 11.1003641329085, 17.9703905921882, 29.3881055676067, 42.0781435349941]
clake=[1.15723881200939, 9.77719620258723, 2.9526829469176, 3.49224222152307, 8.7864652231428, 11.1150618688664, 0.89106992961839, 11.2257972665148, 1.12614070286713, 1.21129680010364, 4.58597948216903, 12.8847011596789, 19.5582784184514, 33.9267591339648]


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


ax.set_ylabel('Error', fontsize=16)
ax.set_xlabel('Stride', fontsize=16)


#plt.title('', fontsize=18)
#ax.set_xticks(x_pos)

plt.yticks(fontsize=14)
#plt.yticks(np.arange(0, 100, 10), fontsize=14)
#ax.get_yaxis().get_major_formatter().set_scientific(False)

plt.xticks([r + barwidth for r in range(len(bwell))], stride, fontsize=12, rotation=90)

#plt.xticks(rotation=90, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('1_init_nonp.png', dpi=100)

# Example data
