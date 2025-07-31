from pathlib import Path
import fnmatch
import os



def find_energy(pu, i):
    pw = 0
    energy = 0
    count = 0
    dir=pu+"_power_"+str(i)+"_*"
    file_name=""
    for file in os.listdir("./data"):
        #print(file)
        if fnmatch.fnmatch(file, dir):
            file_name=file
            break
            

    dir="./data/"+file_name
 
    my_file = Path(dir)
    if my_file.is_file():
        fo = open(dir, "r")

        #str = fo.read(10);
        file = fo.read()
        for line in file.split("\n"):
            if len(line) > 2:
                pw = float(line.strip(" "))
                energy += pw
                count += 1

        avg_pw = energy/float(count)
        energy = energy * 50
        #print(pu,i,name, " power " ,  avg_pw, "energy", energy)
        return energy

    else:
        return 0;
 
 


def find_time(pu, i):
    time=0
    dir=pu+"_time_"+str(i)+"_*"
    file_name=""
    for file in os.listdir("./data"):
        #print(file)
        if fnmatch.fnmatch(file, dir):
            file_name=file
            break
            

    dir="./data/"+file_name
    my_file = Path(dir)
    if my_file.is_file():
        fo = open(dir, "r")

        #str = fo.read(10);
        file = fo.read()
        for line in file.split("\n"):
            if "Total time " in line:
                times = line.split();

                #print(pu,i, " time " , times[3])
                time += float(times[3])
                #print(time)
                #print(times[3])
        return time 


    else:
        return 0;
 
 

pus = {'cpu', 'gpu'}
metric = {'time', 'power'}
app = {'cfd', 'srad1', 'srad2', 'particle', 'vector'}

cpu_time=0
gpu_time=0

cpu_energy=0
gpu_energy=0


for i in range(0,200,1):
#for i in range(0,5,1):
    cpu_time=0
    gpu_time=0
    cpu_energy=0
    gpu_energy=0
    total_time = 0
    total_energy = 0

 
    for pu in pus:
        if pu == 'cpu': 
            cpu_time += find_time(pu,i)
            cpu_energy += find_energy(pu, i)
            #print(name, cpu_energy)
        else:
            gpu_time += find_time(pu,i)
            gpu_energy += find_energy(pu, i)
            #print(name, gpu_energy)
    
    if cpu_time >= gpu_time:
        total_time = cpu_time
        #print(cpu_time)
    else:
        #print(gpu_time)
        total_time = gpu_time

    total_energy = cpu_energy + gpu_energy
    #print(cpu_energy ,  gpu_energy)

    print(i , total_time, total_energy)





