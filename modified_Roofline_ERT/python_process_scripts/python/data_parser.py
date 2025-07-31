#!/usr/bin/python
import numpy as np
from python.heatmap_sea import *

def standalone(pu, str, metric):
    dir = "../data/intensity/standalone_"+pu+"/"+pu+"_"+str 
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    bw = 0
    flops = 0
    byte = 0
    time_loop = 0
    time = 0.0
    i = 0
    for line in file.split("\n"):
        if len(line) > 10:
            key,value = line.split(":")
            if i == 0 : 
                bw = value.strip(" ")
            if i == 1 : 
                byte = value.strip(" ")
            if i == 2 : 
                flop = value.strip(" ")
            if i == 3 : 
                time = float(value.strip(" "))
        i += 1

    fo.close()
    time = time*1000
    # Close opend file

    dir = "../data/intensity/standalone_"+pu+"/power_"+str
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    avg_pw = 0.0
    pw = 0
    energy = 0
    i = 0
    for line in file.split("\n"):
        if len(line) > 2:
            pw = int(line.strip(" "))
            energy += pw
            i += 1

    avg_pw = energy/float(i)
    energy = energy * 50
    est_energy = int(avg_pw * float(time))
    fo.close()

    if metric == 'time':
        return time
    
    if metric == 'energy':
        return est_energy
  
    if metric == 'power':
        return int(avg_pw)

    if metric == 'bw':
        return bw

    if metric == 'intensity':
        return float(flop)/float(byte) 

    #print bw, flops, byte, time,
    #print int(avg_pw), est_energy
    #print int(avg_pw), energy, est_energy
    # Close opend file


def csv_for_poly(location, pu1, str1, pu2, str2):
    dir = location+pu1+"/"+pu1+"_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    bw = 0
    flops = 0
    byte = 0
    time_loop = 0
    time = 0.0
    i = 0
    for line in file.split("\n"):
        if len(line) > 10:
            key,value = line.split(":")
            if i == 0 : 
                bw = value.strip(" ")
            if i == 1 : 
                flops = value.strip(" ")
            if i == 2 : 
                byte = value.strip(" ")
            if i == 3 : 
                time = float(value.strip(" "))
        i += 1

    fo.close()
    time = time*1000
    # Close opend file

    dir = location+pu1+"/power_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    avg_pw = 0.0
    pw = 0
    energy = 0
    i = 0
    for line in file.split("\n"):
        if len(line) > 2:
            pw = int(line.strip(" "))
            energy += pw
            i += 1

    avg_pw = energy/float(i)
    energy = energy * 50
    est_energy = (avg_pw * float(time))

    st_avg_pw = standalone(pu1, str1, 'power')
    st_time = standalone(pu1, str1, 'time')
    st_energy = standalone(pu1, str1, 'energy')
    st_bw = standalone(pu1, str1, 'bw')
    interference_bw = standalone(pu2, str2, 'bw')
    st_intensity = standalone(pu1, str1, 'intensity')
    interference_intensity = standalone(pu2, str2, 'intensity')

    
    fo.close()
    csv=str(st_intensity)+","+str(interference_intensity)+","+str(avg_pw/st_avg_pw)+","+str(time/st_time)
    #csv=str(st_bw)+","+str(interference_bw)+","+str(avg_pw/st_avg_pw)+","+str(time/st_time)
    return csv


def gpu_cpu_col_list(location, pu1, str1, pu2, str2):
    dir = location+pu1+"/"+pu1+"_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    bw = 0
    flops = 0
    byte = 0
    time_loop = 0
    time = 0.0
    i = 0
    for line in file.split("\n"):
        if len(line) > 10:
            key,value = line.split(":")
            if i == 0 : 
                bw = value.strip(" ")
            if i == 1 : 
                flops = value.strip(" ")
            if i == 2 : 
                byte = value.strip(" ")
            if i == 3 : 
                time = float(value.strip(" "))
        i += 1

    fo.close()
    time = time*1000
    # Close opend file

    dir = location+pu1+"/power_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    avg_pw = 0.0
    pw = 0
    energy = 0
    i = 0
    for line in file.split("\n"):
        if len(line) > 2:
            pw = int(line.strip(" "))
            energy += pw
            i += 1

    avg_pw = energy/float(i)
    energy = energy * 50
    est_energy = (avg_pw * float(time))

    st_avg_pw = standalone(pu1, str1, 'power')
    st_time = standalone(pu1, str1, 'time')
    st_energy = standalone(pu1, str1, 'energy')
    st_bw = standalone(pu1, str1, 'bw')
    interference_bw = standalone(pu2, str2, 'bw')
    st_intensity = standalone(pu1, str1, 'intensity')
    interference_intensity = standalone(pu2, str2, 'intensity')

    print pu1+"_"+str1+"_col"+pu2+"_"+str2, bw, flops, byte, time,
    print avg_pw, est_energy, 
    print st_bw, 
    print st_avg_pw, st_time, st_energy,  
    print interference_bw, 
    print avg_pw/st_avg_pw, time/st_time, est_energy/st_energy,
    print st_intensity, interference_intensity
    #print int(avg_pw), energy, est_energy
    # Close opend file
    fo.close()

def matrix_bw(location, pu1, str1, pu2, str2):
    dir = location+pu1+"/"+pu1+"_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    bw = 0
    flops = 0
    byte = 0
    time_loop = 0
    time = 0.0
    i = 0
    for line in file.split("\n"):
        if len(line) > 10:
            key,value = line.split(":")
            if i == 0 : 
                bw = value.strip(" ")
            if i == 1 : 
                flops = value.strip(" ")
            if i == 2 : 
                byte = value.strip(" ")
            if i == 3 : 
                time = float(value.strip(" "))
        i += 1

    fo.close()
    time = time*1000
    # Close opend file

    dir = location+pu1+"/power_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    avg_pw = 0.0
    pw = 0
    energy = 0
    i = 0
    for line in file.split("\n"):
        if len(line) > 2:
            pw = int(line.strip(" "))
            energy += pw
            i += 1

    avg_pw = energy/float(i)
    energy = energy * 50
    est_energy = int(avg_pw * float(time))

    print bw,
    #print int(avg_pw), energy, est_energy
    # Close opend file
    fo.close()
    return bw


def matrix_power(location, pu1, str1, pu2, str2):
    dir = location+pu1+"/"+pu1+"_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    bw = 0
    flops = 0
    byte = 0
    time_loop = 0
    time = 0.0
    i = 0
    for line in file.split("\n"):
        if len(line) > 10:
            key,value = line.split(":")
            if i == 0 : 
                bw = value.strip(" ")
            if i == 1 : 
                flops = value.strip(" ")
            if i == 2 : 
                byte = value.strip(" ")
            if i == 3 : 
                time = float(value.strip(" "))
        i += 1

    fo.close()
    time = time*1000
    # Close opend file

    dir = location+pu1+"/power_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    avg_pw = 0.0
    pw = 0
    energy = 0
    i = 0
    for line in file.split("\n"):
        if len(line) > 2:
            pw = int(line.strip(" "))
            energy += pw
            i += 1

    avg_pw = energy/float(i)
    energy = energy * 50
    est_energy = int(avg_pw * float(time))

    print int(avg_pw),
    #print int(avg_pw), energy, est_energy
    # Close opend file
    fo.close()
    return avg_pw


def matrix_energy(location, pu1, str1, pu2, str2):
    dir = location+pu1+"/"+pu1+"_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    bw = 0
    flops = 0
    byte = 0
    time_loop = 0
    time = 0.0
    i = 0
    for line in file.split("\n"):
        if len(line) > 10:
            key,value = line.split(":")
            if i == 0 : 
                bw = value.strip(" ")
            if i == 1 : 
                flops = value.strip(" ")
            if i == 2 : 
                byte = value.strip(" ")
            if i == 3 : 
                time = float(value.strip(" "))
        i += 1

    fo.close()
    time = time*1000
    # Close opend file

    dir = location+pu1+"/power_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    avg_pw = 0.0
    pw = 0
    energy = 0
    i = 0
    for line in file.split("\n"):
        if len(line) > 2:
            pw = int(line.strip(" "))
            energy += pw
            i += 1

    avg_pw = energy/float(i)
    energy = energy * 50
    est_energy = int(avg_pw * float(time))

    print est_energy,
    #print int(avg_pw), energy, est_energy
    # Close opend file
    fo.close()
    return est_energy

def matrix_time(location, pu1, str1, pu2, str2):
    dir = location+pu1+"/"+pu1+"_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    bw = 0
    flops = 0
    byte = 0
    time_loop = 0
    time = 0.0
    i = 0
    for line in file.split("\n"):
        if len(line) > 10:
            key,value = line.split(":")
            if i == 0 : 
                bw = value.strip(" ")
            if i == 1 : 
                flops = value.strip(" ")
            if i == 2 : 
                byte = value.strip(" ")
            if i == 3 : 
                time = float(value.strip(" "))
        i += 1

    fo.close()
    time = time*1000
    # Close opend file

    dir = location+pu1+"/power_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    avg_pw = 0.0
    pw = 0
    energy = 0
    i = 0
    for line in file.split("\n"):
        if len(line) > 2:
            pw = int(line.strip(" "))
            energy += pw
            i += 1

    avg_pw = energy/float(i)
    energy = energy * 50
    est_energy = int(avg_pw * float(time))

    print time,
    #print int(avg_pw), energy, est_energy
    # Close opend file
    fo.close()
    return time


def matrix_power_ratio(location, pu1, str1, pu2, str2):
    dir = location+pu1+"/"+pu1+"_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    bw = 0
    flops = 0
    byte = 0
    time_loop = 0
    time = 0.0
    i = 0
    for line in file.split("\n"):
        if len(line) > 10:
            key,value = line.split(":")
            if i == 0 : 
                bw = value.strip(" ")
            if i == 1 : 
                flops = value.strip(" ")
            if i == 2 : 
                byte = value.strip(" ")
            if i == 3 : 
                time = float(value.strip(" "))
        i += 1

    fo.close()
    time = time*1000
    # Close opend file

    dir = location+pu1+"/power_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    avg_pw = 0.0
    pw = 0
    energy = 0
    i = 0
    for line in file.split("\n"):
        if len(line) > 2:
            pw = int(line.strip(" "))
            energy += pw
            i += 1

    avg_pw = energy/float(i)
    energy = energy * 50
    est_energy = int(avg_pw * float(time))

    st_avg_pw = standalone(pu1, str1, 'power')
    st_time = standalone(pu1, str1, 'time')
    st_energy = standalone(pu1, str1, 'energy')

    #print pu1+"_"+str1+"_col"+pu2+"_"+str2, bw, flops, byte, time,
    #print int(avg_pw), est_energy, 
    #print st_avg_pw, st_time, st_energy,  
    #print avg_pw/st_avg_pw, time/st_time, est_energy/st_energy,  
    #print int(avg_pw), energy, est_energy
    # Close opend file
    fo.close()
    return avg_pw/st_avg_pw


def matrix_energy_ratio(location, pu1, str1, pu2, str2):
    dir = location+pu1+"/"+pu1+"_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    bw = 0
    flops = 0
    byte = 0
    time_loop = 0
    time = 0.0
    i = 0
    for line in file.split("\n"):
        if len(line) > 10:
            key,value = line.split(":")
            if i == 0 : 
                bw = value.strip(" ")
            if i == 1 : 
                flops = value.strip(" ")
            if i == 2 : 
                byte = value.strip(" ")
            if i == 3 : 
                time = float(value.strip(" "))
        i += 1

    fo.close()
    time = time*1000
    # Close opend file

    dir = location+pu1+"/power_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    avg_pw = 0.0
    pw = 0
    energy = 0
    i = 0
    for line in file.split("\n"):
        if len(line) > 2:
            pw = int(line.strip(" "))
            energy += pw
            i += 1

    avg_pw = energy/float(i)
    energy = energy * 50
    est_energy = int(avg_pw * float(time))

    st_avg_pw = standalone(pu1, str1, 'power')
    st_time = standalone(pu1, str1, 'time')
    st_energy = standalone(pu1, str1, 'energy')

    #print pu1+"_"+str1+"_col"+pu2+"_"+str2, bw, flops, byte, time,
    #print int(avg_pw), est_energy, 
    #print st_avg_pw, st_time, st_energy,  
    #print avg_pw/st_avg_pw, time/st_time, est_energy/st_energy,  
    # Close opend file
    fo.close()
    return  est_energy/st_energy


def matrix_time_ratio(location, pu1, str1, pu2, str2):
    dir = location+pu1+"/"+pu1+"_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    bw = 0
    flops = 0
    byte = 0
    time_loop = 0
    time = 0.0
    i = 0
    for line in file.split("\n"):
        if len(line) > 10:
            key,value = line.split(":")
            if i == 0 : 
                bw = value.strip(" ")
            if i == 1 : 
                flops = value.strip(" ")
            if i == 2 : 
                byte = value.strip(" ")
            if i == 3 : 
                time = float(value.strip(" "))
        i += 1

    fo.close()
    time = time*1000
    # Close opend file

    dir = location+pu1+"/power_"+str1+"_col"+pu2+"_"+str2
    #print dir
    fo = open(dir, "r")
    #str = fo.read(10);
    file = fo.read()
    avg_pw = 0.0
    pw = 0
    energy = 0
    i = 0
    for line in file.split("\n"):
        if len(line) > 2:
            pw = int(line.strip(" "))
            energy += pw
            i += 1

    avg_pw = energy/float(i)
    energy = energy * 50
    est_energy = int(avg_pw * float(time))

    st_avg_pw = standalone(pu1, str1, 'power')
    st_time = standalone(pu1, str1, 'time')
    st_energy = standalone(pu1, str1, 'energy')

    #print pu1+"_"+str1+"_col"+pu2+"_"+str2, bw, flops, byte, time,
    #print int(avg_pw), est_energy, 
    #print st_avg_pw, st_time, st_energy,  
    #print avg_pw/st_avg_pw, time/st_time, est_energy/st_energy,  
    # Close opend file
    fo.close()
    return  time/st_time


