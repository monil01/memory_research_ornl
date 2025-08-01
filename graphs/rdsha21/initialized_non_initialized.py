import random
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import style

import numpy as np
import matplotlib.patches as mpatches

#plt.rcdefaults()
fig, ax = plt.subplots()

fig.set_size_inches(7, 5)

#labels = ['Manaul', 'PAPI']
#traffic = [12.46, 18.75]

#stride = ['stride-1', 'stride-2', 'stride-4', 'stride-8', 'stride-16', 'stride-32', 'stride-64', 'stride-128', 'stride-256', 'stride-512', 'stride-1024', 'stride-2048', 'stride-4096', 'stride-8192']
stride = ['1', '2', '4', '8', '16', '32', '64', '128', '256', '512', '1024', '2048', '4096', '8192', '16384','32768','65536','131072','262144','524288','1048576','2097152','4194304','8388608','16777216','33554432','67108864']

stride = ['1', '2', '4', '8', '16', '32', '64', '128', '256', '512', '1024', '2048', '4096', '8192']


read=[13159180,13034186,12938265,12891037,12906523,6616530,3468820,1907931,1120988,722937,528230,430157,376966,364022]
write=[6932222,6871207,6798102,6758055,6774366,6535310,6462811,6406911,6386789,6361076,6331793,6328232,6321227,6347827]


readi=[19083795,19005683,18970043,18940397,18938589,9468337,4724431,2363247,1182735,594024,296881,149252,75072,37848]
writei=[6824619,6755515,6740634,6725749,6734401,3368188,1676038,839272,420643,212602,106874,58650,31081,15670]


#read=[12959083,12919283,12902727,12898788,12904748,12332178,8041268,1933513,1145951,748236,556137,455652,410271,383331,379650,371440,375630,359555,364233,357222,176823,91798,42924,23070,9425,3862,2046]
#write=[6810151,6769421,6756843,6761755,6762840,6692095,6550141,6390571,6379540,6363557,6370635,6314946,6352228,6344483,6350067,6343315,6324412,6342024,6336080,6319889,3162908,1561251,755448,359941,160736,53189,29941]

read = np.array(read) / 1000000 * 64
write = np.array(write) / 1000000 * 64
readi = np.array(readi) / 1000000 * 64
writei = np.array(writei) / 1000000 * 64
x_pos = np.arange(len(stride))  # the label locations

#ax.barh(x_pos, read, hatch='....', color='white', edgecolor='black')
#rects1 = plt.bar(x, traffic, .8, hatch='....', color='white', edgecolor='black')

plt.plot(stride, read, marker='o', markersize=10,  color='black', linestyle='dotted', label="Read-no-init", linewidth=2)
plt.plot(stride, write, marker='x', markersize=10,  color='black', linestyle='solid', label="Write-no-init", linewidth=1)

plt.plot(stride, readi, marker='<', markersize=10,  color='blue', linestyle='dotted', label="Read-init", linewidth=2)
plt.plot(stride, writei, marker='>', markersize=10,  color='blue', linestyle='solid', label="Write-init", linewidth=1)


#plt.plot(stride, read, "-b", label="Read")
#plt.plot(stride, write, "-r", label="Write")
#plt.legend()
plt.legend(handlelength=3, fontsize=20)

#plt.legend(loc="upper right", fontsize=12)

ax.set_ylabel('Read/Write in MBytes', fontsize=15)

ax.set_xlabel('Stride', fontsize=16)




#ax.set_xticks(x_pos)
plt.yticks(np.arange(0, max(readi)+1, 100), fontsize=14)

#ax.get_yaxis().get_major_formatter().set_scientific(False)


plt.xticks(rotation=90, fontsize=14)
#ax.set_xticklabels(stride, fontsize=12)

#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('stride_init_non_init.png', dpi=100)

# Example data
