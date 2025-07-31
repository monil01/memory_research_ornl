import subprocess


filename='all_o_p.txt'
with open(filename) as f:
    content = f.readlines()
# you may also want to remove whitespace characters like `\n` at the end of each line
content = [x.strip() for x in content]

#print(content[0])
i=0
for op in content:
    print(op)
    twos = op.split("|");
    gpu = " ".join(twos[0])
    cpu = " ".join(twos[1])
    cpu_command = "" 
    cpu_tegra = "" 
    gpu_command = "" 
    gpu_tegra = "" 

    #print(op)
    op = op.replace("|","x")
    #print(op)
    if len(cpu) > 0 : 
        cpu_command = "echo \"password\" | sudo -S ./cpu_ert/cpu_ert " + cpu + " > ./data/cpu_time_" + str(i) + "_" + op 
        #cpu_command = "echo \"password\" | sudo -S ./cpu_ert/cpu_ert " + cpu + " > ./data/cpu_time_" + str(i) + "_" + op + " &"
        cpu_tegra = " echo \"password\" | sudo -S ./c_parser/tegra_parse_cpu -p cpu -t 50 -c 0 -l 1 > ./data/cpu_power_" + str(i) + "_" + op 
        #cpu_tegra = " ./c_parser/tegra_parse_cpu -p cpu -t 50 -c 0 -l 1 > ./data/cpu_power_" + str(i) + "_" + op + " &"
    if len(gpu) > 0 : 
        gpu_command = "echo \"password\" | sudo -S ./gpu_ert/gpu_ert " + gpu + " > ./data/gpu_time_" + str(i) + "_" + op 
        #gpu_command = "echo \"password\" | sudo -S ./gpu_ert/gpu_ert " + gpu + " > ./data/gpu_time_" + str(i) + "_" + op +" & " 
        gpu_tegra = "echo \"password\" | sudo -S ./c_parser/tegra_parse_gpu -p gpu -t 50 -c 0 -l 1 > ./data/gpu_power_" + str(i) + "_" + op 
        #gpu_tegra = "./c_parser/tegra_parse_gpu -p gpu -t 50 -c 0 -l 1 > ./data/gpu_power_" + str(i) + "_" + op + " &"


    #if len(cpu_command)> 0 and len(gpu_command) >0 :
    #    command = gpu_command + " & " + cpu_command
    #else: 
    #    command = gpu_command + cpu_command
    if i > 399:
        print(cpu_command)
        print(gpu_command)
        print(gpu_tegra)
        print(cpu_tegra)


        process = subprocess.Popen(cpu_command, shell=True, stdout=subprocess.PIPE)

        process1 = subprocess.Popen(cpu_tegra, shell=True, stdout=subprocess.PIPE)


        process2 = subprocess.Popen(gpu_command, shell=True, stdout=subprocess.PIPE)

        process3 = subprocess.Popen(gpu_tegra, shell=True, stdout=subprocess.PIPE)

        process3.wait()
        process.wait()
        process2.wait()
        process1.wait()

        print (process3.returncode)

        print (process.returncode)

        print (process1.returncode)
        print (process2.returncode)
    #break;

    i += 1
    #print(gpu)
    #print(cpu)
