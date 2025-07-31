import numpy as np
import seaborn as sns
import matplotlib.pylab as plt

def heat(d_array, name, Y, X, ctag):
    #yticks = np.linspace(10,100,10)
    #num_ticks = 15
    # the index of the position of yticks
    #yticks = np.linspace(0, len(depth_list) - 1, num_ticks, dtype=np.int)
    # the content of labels of these yticks
    #yticklabels = [depth_list[idx] for idx in yticks]
    my_xticks = ['0.0625','0.125','0.25','0.375','0.5','0.75','1','1.25','1.75','2','3','4','6','8','12']

    #ylabels = np.linspace(1, 15, 1, dtype=np.int)
    ylabels = my_xticks 
    xlabels = my_xticks 
    #xlabels = np.linspace(1, 15, 1, dtype=np.int)
    ax = sns.heatmap(d_array, annot=True, fmt='.2f', cmap='RdYlGn_r', xticklabels=xlabels, yticklabels=ylabels, cbar_kws={"orientation": "vertical","label":ctag} )
    #ax = sns.heatmap(d_array, linewidth=0.5)
    #plt.title(name+' comparison')
    ax.set_title(name+' comparison', fontweight="bold")
    #plt.subplots_adjust(top=0.97)
    #plt.suptitle(name+' comparison', fontweight="bold")
    ax.yaxis.set_label_position("left")
    ax.xaxis.set_label_position("bottom")
    ax.yaxis.tick_left()
    ax.xaxis.tick_bottom()
    plt.ylabel(Y+' Operational Intensity')
    plt.xlabel(X+' Operational Intensity')
    plt.show()
    return 
