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

bwell=[21.7536203034958, 21.8884254268798, 21.7842208112791, 20.6854301673284, 20.9884409249536, 20.8433914997201, 22.0610791734733, 22.3587052661916, 24.5183667948445, 25.0110383751512, 27.6405972139893, 35.8411076801787, 41.3616848805092, 40.5115436159844]
slake=[0.961387618113449, 0.207886929947533, 0.321840840294856, 0.133501535147814, 0.264418972420319, 0.972730900402114, 0.391421868625051, 0.385706544260623, 0.688980131440121, 2.76671479066063, 3.18603152572618, 3.17643267896094, 8.35562124624625, 8.93673069750093]
clake=[0.0706899353703456, 0.0985427973846598, 0.0631598665077397, 2.46422359169073, 0.0382546285699652, 0.426612248833043, 0.140998525924502, 0.120464943419923, 0.584516743700995, 2.06281190395318, 1.68289254477301, 0.129447349533477, 1.31745149555376, 19.0783476963871]

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
fig.savefig('5_init_nonp.png', dpi=100)

# Example data
