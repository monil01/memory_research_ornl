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

bwell=[28.5977589978248, 28.3803336597917, 28.1505688175768, 27.3483906215491, 26.8017314611233, 22.5089734608732, 14.8042203333489, 2.45857102052802, 9.31158838607853, 8.31352489885165, 4.84893245391249, 7.6756351060072, 17.295417990059, 9.3929992610696]
slake=[10.8536087885505, 8.80873568540327, 10.0503717917966, 7.25746218824905, 11.3080991078777, 6.16742733605573, 4.26040915165902, 3.49479832596225, 2.40137664094058, 1.36846506488168, 0.906857690209648, 9.05192758395697, 7.78622912717638, 18.7764460695686]
#clake=[12.1948478278176, 6.63364236352826, 10.1022963948863, 4.06164614865072, 11.0211356835143, 8.79826760485281, 1.05096347145657, 20.0509688828063, 10.5422143490572, 2.0059700391996, 0.855593632179388, 22.0693990265854, 8.63763057533695, 52.6333343228941]

clake=[12.1948478278176, 6.63364236352826, 10.1022963948863, 4.06164614865072, 11.0211356835143, 8.79826760485281, 1.05096347145657, 20.0509688828063, 10.5422143490572, 2.0059700391996, 0.855593632179388, 22.0693990265854, 8.63763057533695, 8.71415116727873]

def average(lst):
    return sum(lst) / len(lst)

print("accurcy")
print("Broadwell shows {:.1f}".format((100-average(bwell)))+"\% accuracy, Sky Lake shows {:.1f}".format((100-average(slake)))+"\% accuracy, and Cascade Lake shows {:.1f}".format((100-average(clake)))+"\% accuracy")




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
fig.savefig('5_non_init_nonp.png', dpi=100)

# Example data
