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
stride = ['MAPInt', 'literature', 'BW_no_pref', 'BW_pref', 'SL_no_pref', 'SL_pref', 'CL_no_pref', 'CL_pref']
total=[6291456, 4194304, 6860474, 6775994, 6053006, 6029796, 6297782, 5666516]

total = np.array(total) / 1000000

mapint=total[0]
literature=total[1]
i=0
mapint_accuracy=np.arange(6)
literature_accuracy=np.arange(6)
for x in total:
    if i > 1: 
    	mapint_accuracy[i-2]=100-abs(x-mapint)/x*100
    	literature_accuracy[i-2]=100-abs(x-literature)/x*100
    i=i+1

def average(lst):
    return sum(lst) / len(lst)


print("MAPInt provided {:.1f}".format(average(mapint_accuracy))+"\% average accuracy in all processors where the highest accuracy is {:.1f}".format(max(mapint_accuracy))+"\%  and the lowest accuracy is {:.1f}".format(min(mapint_accuracy))+"\%.")

print("On the other hand, the model from literature provided {:.1f}".format(average(literature_accuracy))+"\% average accuracy in all processors where the highest accuracy is {:.1f}".format(max(literature_accuracy))+"\%  and the lowest accuracy is {:.1f}".format(min(literature_accuracy))+"\%")
#print("MAPInt provided {:.1f}".format(average(mapint_accuracy)))+"\% accuracy, Sky Lake showed {:.1f}".format((100-average(slake)))+"\% accuracy, and Cascade Lake showed {:.1f}".format((100-average(slake)))+"\% accuracy")



def average(lst):
    return sum(lst) / len(lst)

print("accurcy")
#print("Broadwell showed {:.1f}".format((100-average(bwell)))+"\% accuracy, Sky Lake showed {:.1f}".format((100-average(slake)))+"\% accuracy, and Cascade Lake showed {:.1f}".format((100-average(slake)))+"\% accuracy")


barwidth=.25
# Set position of bar on X axis
#r1 = np.arange(len(bwell))
#r2 = [x + barwidth for x in r1]
#r3 = [x + barwidth for x in r2]


x_pos = np.arange(len(stride))  # the label locations
#ax.barh(x_pos, read, hatch='....', color='white', edgecolor='black')
#rects1 = plt.bar(x, traffic, .8, hatch='....', color='white', edgecolor='black')
plt.bar(stride, total, width=barwidth, hatch='....', color='white', edgecolor='black', label="Total Traffic = Read + Write")

#plt.legend(handlelength=3, fontsize=16)

#plt.legend(loc="upper right", fontsize=12)


ax.set_ylabel('Traffic in million', fontsize=16)
#ax.set_xlabel('Stride', fontsize=16)

plt.yticks(np.arange(0, max(total)+3, 3))

#plt.title('', fontsize=18)
#ax.set_xticks(x_pos)

plt.yticks(fontsize=14)
#plt.yticks(np.arange(0, 100, 10), fontsize=14)
#ax.get_yaxis().get_major_formatter().set_scientific(False)

#plt.xticks([ + barwidth for r in range(len(stride))], stride, fontsize=12, rotation=90)

plt.xticks(rotation=45, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('laplace.png', dpi=100)

# Example data
