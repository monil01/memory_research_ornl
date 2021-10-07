import random
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import style

import numpy as np
import matplotlib.patches as mpatches

#plt.rcdefaults()
fig, ax = plt.subplots()

fig.set_size_inches(7, 5)


#stride = ['stride-1', 'stride-2', 'stride-4', 'stride-8', 'stride-16', 'stride-32', 'stride-64', 'stride-128', 'stride-256', 'stride-512', 'stride-1024', 'stride-2048', 'stride-4096', 'stride-8192']
stride = ['1', '2', '4', '8', '16', '32', '64', '128', '256', '512', '1024']


total_P100_200M=[0.10200650714218,0.0786560835041872,0.094623379358708,0.0697922563902145,0.214265915370561,0.451099868014086,0.27528011676568,1.01666182572154,2.33059515203454,3.5595030151157,5.18937247196943]
total_V100_200M=[0.0183406965279913,0.0227568200926105,0.0356662746298748,0.0388349126364407,3.43976588578339,3.57582342389829,3.8139506547789,4.40535967107638,5.50596044940896,7.67654384174787,11.6135115608064]
total_A100_200M=[0.409587442107597,0.521139281462331,0.52745499040277,0.528402415194868,3.1965985287552,3.06190667201498,2.7873221259407,2.25487882975496,0.935984149757464,1.1722020653084,7.5348561257787]

def average(lst):
    return sum(lst) / len(lst)

print("accurcy")
print("Broadwell showed {:.1f}".format((100-average(total_P100_200M)))+"\% accuracy, Sky Lake showed {:.1f}".format((100-average(total_V100_200M)))+"\% accuracy, and Cascade Lake showed {:.1f}".format((100-average(total_A100_200M)))+"\% accuracy")


barwidth=.25
# Set position of bar on X axis
r1 = np.arange(len(total_P100_200M))
r2 = [x + barwidth for x in r1]
r3 = [x + barwidth for x in r2]


x_pos = np.arange(len(stride))  # the label locations
#ax.barh(x_pos, read, hatch='....', color='white', edgecolor='black')
#rects1 = plt.bar(x, traffic, .8, hatch='....', color='white', edgecolor='black')
plt.bar(r1, total_P100_200M, width=barwidth, hatch='....', color='white', edgecolor='black', label='P100')
plt.bar(r2, total_V100_200M, width=barwidth, hatch='////', color='grey', edgecolor='black', label='V100')
plt.bar(r3, total_A100_200M, width=barwidth, hatch='oo', color='white', edgecolor='black', label='A100')

#plt.legend(handlelength=3, fontsize=12)

plt.legend(loc="upper left", fontsize=18)


ax.set_ylabel('Error', fontsize=18)
ax.set_xlabel('Stride', fontsize=18)


#plt.title('', fontsize=18)
#ax.set_xticks(x_pos)

plt.yticks(fontsize=16)
#plt.yticks(np.arange(0, 100, 10), fontsize=14)
#ax.get_yaxis().get_major_formatter().set_scientific(False)

plt.xticks([r + barwidth for r in range(len(total_P100_200M))], stride, fontsize=16, rotation=90)

#plt.xticks(rotation=90, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('200_nvidia_experiments.png', dpi=100)

# Example data
