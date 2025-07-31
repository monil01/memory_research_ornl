#!/usr/bin/python

def gpu_cpu(pu, str):
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
                flops = value.strip(" ")
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
    op_intensity = float(flops)/float(byte)
    flops_sec = float(flops)/float(time)

    print bw, byte, flops, time,
    print int(avg_pw), est_energy, op_intensity, flops_sec
    #print int(avg_pw), energy, est_energy
    # Close opend file
    fo.close()


#gpu_cpu("gpu","10")
for i in range(1,16,1): 
    gpu_cpu("gpu",str(i))

for i in range(1,16,1): 
    gpu_cpu("cpu",str(i))
