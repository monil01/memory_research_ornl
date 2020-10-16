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

bwell=[1.01329757268451, 1.00664442610665, 0.645074965635715, 0.641592213238659, 0.872555452784627, 0.140716132057309, 1.24265498171867, 1.8273310825351, 1.55418999228563, 1.79646168094792, 2.69749326324149, 2.42103254222656, 3.5825217604221, 5.29145864124974]
slake=[0.142826912952481, 0.0905315660888305, 0.145628414355477, 0.112599470670294, 0.0836252097134799, 11.4262752723197, 21.8709107434609, 16.2206522285226, 0.289030989339573, 0.333069340882973, 0.52743061939484, 0.920171017174767, 1.97753808227538, 3.02605865132925]
clake=[0.19101842130457, 0.135409194881203, 0.0997060877408937, 0.100301694691289, 0.104775705372766, 10.5245068174194, 24.9542387588648, 16.162753394389, 0.236673726611326, 0.282794802988159, 0.737736202894735, 0.84683466290589, 2.48261475658662, 4.05502458156324]

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
fig.savefig('500_init_pref.png', dpi=100)

# Example data
