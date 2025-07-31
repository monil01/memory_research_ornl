#!/usr/bin/python
import numpy as np
from python.data_parser import *

#location="../data/collocate_"
location="../data/intensity/collocate_"

print "-----------------------------------------Creating GPU csv for poly ----------------------"

pu_csv=""

for i in range(1,16,1): 
    for j in range(1,16,1): 
#for i in range(10,110,10): 
#    for j in range(10,110,10): 
        pu_csv += csv_for_poly(location,"gpu",str(j),"cpu",str(i)) + "\n"

print pu_csv

text_file = open("csv_poly/gpu_csv.csv", "w")
text_file.write("%s" % pu_csv)
text_file.close()

print "-----------------------------------------Creating CPU csv for poly ----------------------"

pu_csv=""

for i in range(1,16,1): 
    for j in range(1,16,1): 
#for i in range(10,110,10): 
    #for j in range(10,110,10): 
        pu_csv += csv_for_poly(location,"cpu",str(j),"gpu",str(i)) + "\n"

print pu_csv

text_file = open("csv_poly/cpu_csv.csv", "w")
text_file.write("%s" % pu_csv)
text_file.close()
pu_csv=""

