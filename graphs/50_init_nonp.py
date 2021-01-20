import random
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import style

import numpy as np
import matplotlib.patches as mpatches

#plt.rcdefaults()
fig, ax = plt.subplots()

fig.set_size_inches(7, 4)


#stride = ['stride-1', 'stride-2', 'stride-4', 'stride-8', 'stride-16', 'stride-32', 'stride-64', 'stride-128', 'stride-256', 'stride-512', 'stride-1024', 'stride-2048', 'stride-4096', 'stride-8192']
stride = ['1', '2', '4', '8', '16', '32', '64', '128', '256', '512', '1024', '2048', '4096', '8192']

bwell=[4.21852275844524, 3.90608688058248, 3.8223683780258, 3.73424119901852, 3.7676356393251, 4.02841127557144, 3.68713389553336, 3.63028568609069, 3.70927287405481, 4.14933686677218, 4.71166512172513, 8.86279432213751, 12.4614550278779, 14.1619348147106]
slake=[0.159616817401684, 0.119840210921328, 0.12671921865537, 0.102247347794585, 0.102103641909677, 0.0730985269655542, 0.175818334683489, 0.174542815378168, 0.255855699428283, 0.47212837407447, 0.924995941887834, 1.9515562248996, 2.58922515261541, 4.78506103506104]
clake=[0.350090063588601, 8.53364951909188, 0.207934730560625, 0.103365046119479, 0.0773880644918124, 0.043485082249818, 0.0929694863148149, 0.0285521499256748, 0.127779066533547, 0.0767410628637207, 0.00384014746166253, 0.497987671302664, 1.92398465432049, 3.16107056443616]


def average(lst):
    return sum(lst) / len(lst)

print("accurcy")
print("Broadwell showed {:.1f}".format((100-average(bwell)))+"\% accuracy, Sky Lake showed {:.1f}".format((100-average(slake)))+"\% accuracy, and Cascade Lake showed {:.1f}".format((100-average(clake)))+"\% accuracy")


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

ax.set_ylabel('Error', fontsize=20)
ax.set_xlabel('Stride', fontsize=20)


#plt.title('', fontsize=18)
#ax.set_xticks(x_pos)

plt.yticks(fontsize=20)
#plt.yticks(np.arange(0, 100, 10), fontsize=14)
#ax.get_yaxis().get_major_formatter().set_scientific(False)

plt.xticks([r + barwidth for r in range(len(bwell))], stride, fontsize=20, rotation=90)


#plt.xticks(rotation=90, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('50_init_nonp.png', dpi=100)

# Example data
