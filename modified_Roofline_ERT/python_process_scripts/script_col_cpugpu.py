#!/usr/bin/python
import numpy as np
from python.heatmap_sea import *
from python.data_parser import *

location="../data/intensity/collocate_"

print "-----------------------------------------List data GPU ----------------------"
#gpu_cpu("gpu","10")
print "Name Bandwidth Flops Byte Time Power Energy ST_BW ST_power ST_time ST_energy Interference_BW power_fator time_factor energy_factor ST_intens Interference_intens"
for i in range(1,16,1): 
    for j in range(1,16,1): 
        gpu_cpu_col_list(location,"gpu",str(j),"cpu",str(i))


print "-----------------------------------------GPU time ratio data ----------------------"
array = np.zeros((15,15))
print array
for i in range(1,16,1): 
    for j in range(1,16,1): 
        array[i - 1][j - 1] = matrix_time_ratio(location,"gpu",str(i),"cpu",str(j))
        #array[j - 1][i - 1] = matrix_time_ratio(location,"gpu",str(i),"cpu",str(j))

    print ""

print array
heat(array,"For GPU: Time Ratio (collocated/standalone)","GPU", "CPU", "Ratio of Collocated and Standalone Time for GPU")

print "-----------------------------------------GPU power ratio data ----------------------"
array = np.zeros((15,15))
print array
for i in range(1,16,1): 
    for j in range(1,16,1): 
        array[i - 1][j - 1] = matrix_power_ratio(location,"gpu",str(i),"cpu",str(j))
        #array[j - 1][i - 1] = matrix_power_ratio(location,"gpu",str(i),"cpu",str(j))

    print ""

#heat(array,"GPU: Power Ratio (collocated/standalone)","GPU", "CPU")
heat(array,"For GPU: Power Ratio (collocated/standalone)","GPU", "CPU", "Ratio of Collocated and Standalone Power for GPU")


print "-----------------------------------------GPU Energy ratio data ----------------------"
array = np.zeros((15,15))
print array
for i in range(1,16,1): 
    for j in range(1,16,1): 
        array[i - 1][j - 1] = matrix_energy_ratio(location,"gpu",str(i),"cpu",str(j))
        #array[j - 1][i - 1] = matrix_energy_ratio(location,"gpu",str(i),"cpu",str(j))

    print ""

#heat(array,"GPU: Energy Ratio (collocated/standalone)","GPU", "CPU")
heat(array,"For GPU: Energy Ratio (collocated/standalone)","GPU", "CPU", "Ratio of Collocated and Standalone Energy for GPU")



print "-----------------------------------------GPU BW data ----------------------"
array = np.zeros((15,15))
print array
for i in range(1,16,1): 
    for j in range(1,16,1): 
        array[i - 1][j - 1] = matrix_bw(location,"gpu",str(i),"cpu",str(j))

    print ""

#heat(array,"GPU: Bandwidht","GPU", "CPU")

print "-----------------------------------------GPU power data ----------------------"
for i in range(1,16,1): 
    for j in range(1,16,1): 
        #matrix_power(location,"gpu",str(i),"cpu",str(j))
        array[i - 1][j - 1] = matrix_power(location,"gpu",str(i),"cpu",str(j))
    print ""

#heat(array,"GPU: Average Power","GPU", "CPU")

print "-----------------------------------------GPU time data ----------------------"
for i in range(1,16,1): 
    for j in range(1,16,1): 
        #matrix_time(location,"gpu",str(i),"cpu",str(j))
        array[i - 1][j - 1] = matrix_time(location,"gpu",str(i),"cpu",str(j))
    print ""

#heat(array,"GPU: Execution Time","GPU", "CPU")

print "-----------------------------------------GPU Energy data ----------------------"
for i in range(1,16,1): 
    for j in range(1,16,1): 
        #matrix_energy(location,"gpu",str(i),"cpu",str(j))
        array[i - 1][j - 1] = matrix_energy(location,"gpu",str(i),"cpu",str(j))
    print ""

#heat(array,"GPU: Energy","GPU", "CPU")

print "-----------------------------------------List data CPU ----------------------"
print "Name Bandwidth Flops Byte Time Power Energy ST_BW ST_power ST_time ST_energy Interference_BW power_fator time_factor energy_factor ST_intens Interference_intens"
#gpu_cpu("gpu","10")
for i in range(1,16,1): 
    for j in range(1,16,1): 
        gpu_cpu_col_list(location,"cpu",str(j),"gpu",str(i))
        #array[i - 1][j - 1] = gpu_cpu_col_list(location,"cpu",str(j),"gpu",str(i))


print "-----------------------------------------CPU time ratio data ----------------------"
array = np.zeros((15,15))
print array
for i in range(1,16,1): 
    for j in range(1,16,1): 
        #array[i - 1][j - 1] = matrix_time_ratio(location,"cpu",str(i),"gpu",str(j))
        array[j - 1][i - 1] = matrix_time_ratio(location,"cpu",str(i),"gpu",str(j))

    print ""

#heat(array,"CPU: Time Ratio (collocated/standalone)","CPU", "GPU")
heat(array,"For CPU: Time Ratio (collocated/standalone)","GPU", "CPU", "Ratio of Collocated and Standalone Time for CPU")


print "-----------------------------------------CPU power ratio data ----------------------"
array = np.zeros((15,15))
print array
for i in range(1,16,1): 
    for j in range(1,16,1): 
        #array[i - 1][j - 1] = matrix_power_ratio(location,"cpu",str(i),"gpu",str(j))
        array[j - 1][i - 1] = matrix_power_ratio(location,"cpu",str(i),"gpu",str(j))

    print ""

#heat(array,"CPU: Power Ratio (collocated/standalone)","CPU", "GPU")
heat(array,"For CPU: Power Ratio (collocated/standalone)","GPU", "CPU", "Ratio of Collocated and Standalone Power for CPU")


print "-----------------------------------------CPU Energy ratio data ----------------------"
array = np.zeros((15,15))
print array
for i in range(1,16,1): 
    for j in range(1,16,1): 
        #array[i - 1][j - 1] = matrix_energy_ratio(location,"cpu",str(i),"gpu",str(j))
        array[j - 1][i - 1] = matrix_energy_ratio(location,"cpu",str(i),"gpu",str(j))

    print ""

#heat(array,"CPU: Energy Ratio (collocated/standalone)","CPU", "GPU")
heat(array,"For CPU: Energy Ratio (collocated/standalone)","GPU", "CPU", "Ratio of Collocated and Standalone Energy for CPU")



print "-----------------------------------------CPU BW data ----------------------"
for i in range(1,16,1): 
    for j in range(1,16,1): 
        #matrix_bw(location,"cpu",str(i),"gpu",str(j))
        array[i - 1][j - 1] = matrix_bw(location,"cpu",str(i),"gpu",str(j))
    print ""

#heat(array,"CPU: Bandwidth","CPU", "GPU")

print "-----------------------------------------CPU power data ----------------------"
for i in range(1,16,1): 
    for j in range(1,16,1): 
        #matrix_power(location,"cpu",str(i),"gpu",str(j))
        array[i - 1][j - 1] = matrix_power(location,"cpu",str(i),"gpu",str(j))
    print ""

#heat(array,"CPU: Average Power","CPU", "GPU")

print "-----------------------------------------CPU time data ----------------------"
for i in range(1,16,1): 
    for j in range(1,16,1): 
        #matrix_time(location,"cpu",str(i),"gpu",str(j))
        array[i - 1][j - 1] = matrix_time(location,"cpu",str(i),"gpu",str(j))
    print ""

#heat(array,"CPU: Execution Time","CPU", "GPU")

print "-----------------------------------------CPU Energy data ----------------------"
for i in range(1,16,1): 
    for j in range(1,16,1): 
        #matrix_energy(locaiton,"cpu",str(i),"gpu",str(j))
        array[i - 1][j - 1] = matrix_energy(location,"cpu",str(i),"gpu",str(j))
    print ""

#heat(array,"CPU: Energy","CPU", "GPU")

#for i in range(1,16,1): 
#    for j in range(1,16,1): 
#        gpu_cpu_col("cpu",str(j),"gpu",str(i))
