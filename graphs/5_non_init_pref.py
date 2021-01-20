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

bwell=[29.6632689961692, 29.2030720202989, 29.2421322911737, 28.9669406459121, 29.4761223075864, 25.2020740766745, 14.1179626197402, 12.1025629486285, 7.71768631146058, 5.00759776373772, 4.21235551912963, 2.24734898297167, 13.4188252604966, 5.86636611931363]
slake=[15.6470076956922, 14.5890160108014, 17.4481574428741, 15.0088481455157, 10.2355419379548, 3.08972269689312, 19.4465934213785, 7.76987861630617, 2.41823428687365, 5.52310319139178, 3.05424880648206, 1.16666492931822, 1.06644827514342, 3.56245592275488]
clake=[13.810460238352, 10.7473516954195, 10.4888882099305, 7.27397351052329, 9.16718663406051, 6.06067462508259, 27.1180925045478, 6.49960864476194, 0.0973001064809008, 1.20072637833365, 0.838830617168438, 12.3663725490366, 21.1369831609271, 9.99366653947566]


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
fig.savefig('5_non_init_pref.png', dpi=100)

# Example data
