import subprocess


filename='kill.txt'
with open(filename) as f:
    content = f.readlines()
# you may also want to remove whitespace characters like `\n` at the end of each line
content = [x.strip() for x in content]

#print(content[0])
i=0
for op in content:
    print(op)
    twos = op.split("   ");
    twoss = twos[1].split("  ");
    print(twos[1])
    command = "echo \"password\" | sudo -S kill -9 " + twoss[0] 

    print(command)

    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)

    process.wait()


    print (process.returncode)
    #break;

    #print(gpu)
    #print(cpu)
