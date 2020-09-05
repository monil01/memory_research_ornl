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

bwell=[6.89069444247191, 6.47014122859027, 6.42643296065269, 6.43609859988483, 6.38857299539492, 3.26365220729129, 6.49735416269361, 6.55447542164415, 4.47203648233109, 2.75758863247103, 2.22480859663468, 1.49070279370441, 1.15001617368554, 0.590199260221682]
slake=[5.88882956120705, 5.98463222291239, 6.0207752729683, 6.07153591824467, 5.92163829413803, 13.8424115016415, 31.509156151405, 7.1446060078777, 5.90311254823126, 5.17520925596162, 4.50237654769609, 3.70262794271104, 2.72875165721473, 2.36387533932971]
clake=[6.67622832997136, 6.78572110367297, 6.44110340219069, 6.5672415879124, 6.42267823185875, 12.2711733852531, 29.5646990964552, 7.86374802607294, 6.69108987991964, 5.85502399957178, 5.15318394311387, 3.19693147444586, 1.53771100204558, 2.40203739138471]

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
fig.savefig('50_non_init_pref.png', dpi=100)

# Example data
