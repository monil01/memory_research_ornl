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

total_P100_50M=[0.0990591089624624,0.120374924141425,0.174610578161104,0.122413964548491,0.395723805151087,0.912917039696505,1.77394680454147,2.39310248755473,3.84970401092883,6.65779343205404,13.1477372275757]
total_V100_50M=[0.00179736563798507,0.145563802910669,0.155394150759524,0.171764462066568,3.75629745776972,4.34751495107712,5.31421054776186,7.4737710474837,11.7162153420998,19.1725769164907,28.6972473714953]
total_A100_50M=[1.66562176999848,1.67897405915174,1.76433923142483,1.73586825205061,2.21532859021479,2.21203129214999,1.09140518417462,1.29942713427414,7.56676557863502,19.4792353328939,32.0269283944214]



def average(lst):
    return sum(lst) / len(lst)

print("accurcy")
print("Broadwell showed {:.1f}".format((100-average(total_P100_50M)))+"\% accuracy, Sky Lake showed {:.1f}".format((100-average(total_V100_50M)))+"\% accuracy, and Cascade Lake showed {:.1f}".format((100-average(total_A100_50M)))+"\% accuracy")


barwidth=.25
# Set position of bar on X axis
r1 = np.arange(len(total_P100_50M))
r2 = [x + barwidth for x in r1]
r3 = [x + barwidth for x in r2]


x_pos = np.arange(len(stride))  # the label locations
#ax.barh(x_pos, read, hatch='....', color='white', edgecolor='black')
#rects1 = plt.bar(x, traffic, .8, hatch='....', color='white', edgecolor='black')
plt.bar(r1, total_P100_50M, width=barwidth, hatch='....', color='white', edgecolor='black', label='P100')
plt.bar(r2, total_V100_50M, width=barwidth, hatch='////', color='grey', edgecolor='black', label='V100')
plt.bar(r3, total_A100_50M, width=barwidth, hatch='oo', color='white', edgecolor='black', label='A100')

#plt.legend(handlelength=3, fontsize=12)

plt.legend(loc="upper left", fontsize=18)


ax.set_ylabel('Error', fontsize=18)
ax.set_xlabel('Stride', fontsize=18)


#plt.title('', fontsize=18)
#ax.set_xticks(x_pos)

plt.yticks(fontsize=16)
#plt.yticks(np.arange(0, 100, 10), fontsize=14)
#ax.get_yaxis().get_major_formatter().set_scientific(False)

plt.xticks([r + barwidth for r in range(len(total_P100_50M))], stride, fontsize=16, rotation=90)

#plt.xticks(rotation=90, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('50_nvidia_experiments.png', dpi=100)

# Example data
