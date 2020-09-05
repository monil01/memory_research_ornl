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

bwell=[22.3954356099408, 22.5176675214518, 22.4282321518222, 24.9018316743647, 23.7238388022324, 32.09963149112, 33.4483913038663, 22.8646465843231, 26.030600844553, 28.6998503267258, 30.8921873894275, 44.4819499715748, 47.3210432624879, 50.6985813812601]
slake=[0.942629933552316, 0.850858274630431, 0.34750816951128, 0.123048404365821, 0.165964101278035, 12.0288514622902, 17.355905724715, 19.1235843392203, 0.700340637551477, 1.94171101516216, 3.20042622788323, 7.10905545515077, 10.6857051399305, 14.2463558131366]
clake=[0.429032828242251, 0.562991853593156, 0.405719431077096, 0.192588381459136, 0.363073454529105, 10.5514889453565, 23.9245333299494, 16.2171437150793, 0.954953092290595, 2.74468029143323, 7.58648231794646, 2.68796004206099, 2.22642170604726, 25.0642648864334]

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
fig.savefig('5_init_pref.png', dpi=100)

# Example data
