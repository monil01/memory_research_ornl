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

bwell=[2.13636395771223, 1.8772583881148, 1.68372596907421, 1.62091427918596, 1.60617451009242, 1.73370361960522, 1.39399545282749, 1.40149337140382, 1.4688922946845, 1.67677439913654, 2.9093515724149, 2.14010355549899, 3.49467253534349, 4.87817588180518]
slake=[0.172244406744692, 0.142096199381819, 0.0876119741112455, 0.0686128903894586, 0.0638735755874048, 0.0555802911331374, 0.0765685276811567, 0.078511111621288, 0.155533715798877, 0.242253308190338, 0.486479408439409, 1.18324604151151, 1.83288835097849, 2.73708124345148]
clake=[0.415858594470703, 0.40967079460614, 0.162808900362587, 0.13038816729499, 0.158634351589596, 0.217583143419455, 0.150512318934537, 0.173203485025342, 0.207020137552727, 0.277703460290294, 0.438338930450971, 0.844116416685959, 1.7083930526926, 4.41563665976298]


def average(lst):
    return sum(lst) / len(lst)

print("accurcy")
print("Broadwell showed {:.1f}".format((100-average(bwell)))+"\% accuracy, Sky Lake showed {:.1f}".format((100-average(slake)))+"\% accuracy, and Cascade Lake showed {:.1f}".format((100-average(slake)))+"\% accuracy")




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
fig.savefig('500_init_nonp.png', dpi=100)

# Example data
