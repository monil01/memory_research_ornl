import random
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import style

import numpy as np
import matplotlib.patches as mpatches



def autolabel(rects, xpos='center'):
    """
    Attach a text label above each bar in *rects*, displaying its height.

    *xpos* indicates which side to place the text w.r.t. the center of
    the bar. It can be one of the following {'center', 'right', 'left'}.
    """

    xpos = xpos.lower()  # normalize the case of the parameter
    ha = {'center': 'center', 'right': 'left', 'left': 'right'}
    offset = {'center': 0.5, 'right': 0.57, 'left': 0.43}  # x_txt = x + w*off

    for rect in rects:
        height = rect.get_height()
        ax.text(rect.get_x() + rect.get_width()*offset[xpos] + .03, height + 4,
                '{}'.format(height), ha=ha[xpos], va='bottom', fontsize=20, rotation=90)


def average(lst):
    return sum(lst) / len(lst)



#plt.rcdefaults()
fig, ax = plt.subplots()

fig.set_size_inches(7.5, 3.5)




#stride = ['stride-1', 'stride-2', 'stride-4', 'stride-8', 'stride-16', 'stride-32', 'stride-64', 'stride-128', 'stride-256', 'stride-512', 'stride-1024', 'stride-2048', 'stride-4096', 'stride-8192']
#stride = ['MAPInt', 'literature', 'BW_no_pref', 'BW_pref', 'SL_no_pref', 'SL_pref', 'CL_no_pref', 'CL_pref']
#stride = ['BW', 'BW_Pref', 'SK', 'SK_pref', 'CS', 'CS_pref', 'CP', 'CP_pref']
stride = ['BW', 'BW_Pf', 'SK', 'SK_Pf', 'CS', 'CS_Pf', 'CP', 'CP_Pf']

#stride = ['BW_no_pref', 'BW_Pref', 'SK_no_pref', 'SK_pref', 'CS_no_pref', 'CS_pref', 'CP_no_pref', 'CP_pref']

mapr=[95.3101043330511, 78.7016557954816, 71.6890368938188, 79.4437128944134, 71.6890368938188, 79.4437128944134, 32.1122980870215, 24.5260870712568]

#Here lit means the corrected results
#
#
lit=[94.7103434724552, 94.6297431281576, 98.0897308123935, 98.7615042635082, 98.177610635759, 97.0360885136902, 95.6535956134869, 99.9241483420006]



mapr=np.round(mapr, 1)
lit=np.round(lit, 1)

#total=[8388608, 8388608, 9441832, 9310190, 8837973, 9382619, 9266269, 9326488]
#total = np.array(total) / 1000000

map_no_pref = np.array([mapr[0],mapr[2], mapr[4]])
map_pref = np.array([mapr[1],mapr[3], mapr[5]])

lit_no_pref = np.array([lit[0],lit[2], lit[4]])
lit_pref = np.array([lit[1],lit[3], lit[5]])


#mapint=total[0]
#literature=total[1]
#i=0
#mapint_accuracy=np.arange(6)
#literature_accuracy=np.arange(6)
#for x in total:
#    if i > 1: 
#    	mapint_accuracy[i-2]=100-abs((x-mapint)/x*100)
#    	literature_accuracy[i-2]=100-abs((x-literature)/x*100)
#    i=i+1

#def average(lst):
#    return sum(lst) / len(lst)


print("MAPredict provided {:.1f}".format(average(map_no_pref))+"\% and {:.1f}".format(average(map_pref))+"\% average accuracy in all processors when prefetching is disabled and enabled, respectively.")


print("On the other hand, the model from literature provided {:.1f}".format(average(lit_no_pref))+"\% and {:.1f}".format(average(lit_pref))+"\% average accuracy in all processors when prefetching is disabled and enabled, respectively.")

# where the highest accuracy is {:.1f}".format(max(literature_accuracy))+"\%  and the lowest accuracy is {:.1f}".format(min(literature_accuracy))+"\%")
##the highest accuracy is {:.1f}".format(max(mapint_accuracy))+"\%  and the lowest accuracy is {:.1f}".format(min(mapint_accuracy))+"\%.")

#print("On the other hand, the model from literature provided {:.1f}".format(average(literature_accuracy))+"\% average accuracy in all processors where the highest accuracy is {:.1f}".format(max(literature_accuracy))+"\%  and the lowest accuracy is {:.1f}".format(min(literature_accuracy))+"\%")
#print("MAPInt provided {:.1f}".format(average(mapint_accuracy)))+"\% accuracy, Sky Lake showed {:.1f}".format((100-average(slake)))+"\% accuracy, and Cascade Lake showed {:.1f}".format((100-average(slake)))+"\% accuracy")


#print("accurcy")
#print("Broadwell showed {:.1f}".format((100-average(bwell)))+"\% accuracy, Sky Lake showed {:.1f}".format((100-average(slake)))+"\% accuracy, and Cascade Lake showed {:.1f}".format((100-average(slake)))+"\% accuracy")


barwidth=.35
# Set position of bar on X axis
#r1 = np.arange(len(bwell))
#r2 = [x + barwidth for x in r1]
#r3 = [x + barwidth for x in r2]


x_pos = np.arange(len(stride))  # the label locations
barwidth1=.25
#barwidth=.15
# Set position of bar on X axis
r1 = np.arange(len(stride))
r2 = [x + barwidth for x in r1]


#ax.barh(x_pos, read, hatch='....', color='white', edgecolor='black')
#rects1 = plt.bar(x, traffic, .8, hatch='....', color='white', edgecolor='black')
rects1=ax.bar(r1, mapr, width=barwidth, hatch='...', color='cornflowerblue', edgecolor='black', label="MAPredict")
rects2=ax.bar(r2, lit, width=barwidth, hatch='///', color='khaki', edgecolor='black', label="Individual_factor")

#plt.legend(handlelength=3, fontsize=12)

plt.legend(loc="upper center", handlelength=2, fontsize=20, ncol=4, framealpha=1)


#plt.legend(loc="upper right", fontsize=12)


#ax.set_ylabel('Accuracy', fontsize=16)
#ax.set_xlabel('Stride', fontsize=16)

plt.yticks(np.arange(0, max(mapr)+160, 20))

#plt.title('', fontsize=18)
#ax.set_xticks(x_pos)

plt.yticks(fontsize=14)
#plt.yticks(np.arange(0, 100, 10), fontsize=14)
#ax.get_yaxis().get_major_formatter().set_scientific(False)

ax.set_yticklabels([])


#plt.xticks([ + barwidth for r in range(len(stride))], stride, fontsize=12, rotation=90)
plt.xticks([r + barwidth/2 for r in range(len(mapr))], stride, fontsize=20, rotation=0)

#plt.xticks(rotation=45, fontsize=14)

#ax.set_xticklabels(stride, fontsize=12)

autolabel(rects1, "center")
autolabel(rects2, "center")



#ax.invert_yaxis()
plt.tight_layout()

plt.show()
fig.savefig('xsbench.png', dpi=100)

# Example data
