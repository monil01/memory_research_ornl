#!/bin/bash

#pct_array=(90 80)
#pct_array=(100 90 80 70 60 50 40 30 20 10)
#iteration_array=(1 2 3 4 5)
#pct_array=(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20)
#pct_array=(100 90 80 70 60 50 40 30 20 10)
#iteration_array=(1 2 3 4 5)
pct_array=(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15)
limit=35
memory_array=(seq strided random) 


cd ../collocation_roofline


# standalone cpu

#warmup

make clean_cpu;
make cpu_ert intens=3 lim=80 inf=0 memory=seq
echo "mon01nil" | sudo -S ./cpu_ert
sleep 5s


for memory in "${memory_array[@]}"
do
    for pct_var in "${pct_array[@]}"
    do
        make clean_cpu;
        make cpu_ert intens=$pct_var lim=$limit inf=0 memory=$memory

        echo "now  cpu $memory $pct_var$"
        echo "mon01nil" | sudo -S ./cpu_ert &> ../data/intensity/mixed/standalone_cpu/cpu_${memory}_${pct_var} & sudo ../../c_parser/tegra_parse -t 50 -p cpu -l 1 -c 0 &> ../data/intensity/mixed/standalone_cpu/power_${memory}_${pct_var}
        sleep 5s
    done
done


sleep 5s

# standalone gpu

make clean_gpu;
make gpu_ert intens=3 lim=80 inf=0 memory=seq
echo "mon01nil" | sudo -S ./gpu_ert
sleep 5s


for memory in "${memory_array[@]}"
do
    for pct_var in "${pct_array[@]}"
    do
        make clean_gpu;
        make gpu_ert intens=$pct_var lim=$limit inf=0 memory=$memory

        echo "now  gpu $memory $pct_var$"
        echo "mon01nil" | sudo -S ./gpu_ert &> ../data/intensity/mixed/standalone_gpu/gpu_${memory}_${pct_var} & sudo ../../c_parser/tegra_parse -t 50 -p gpu -l 1 -c 0 &> ../data/intensity/mixed/standalone_gpu/power_${memory}_${pct_var}
        sleep 5s
    done
done




sleep 5s



# collocate gpu

for outer_memory in "${memory_array[@]}"
do
for outer_var in "${pct_array[@]}"
do
    make clean_cpu;
    make cpu_ert intens=$outer_var lim=$limit inf=1 memory=$outer_memory

    echo "mon01nil" | sudo -S ./cpu_ert & PID1=$!
    echo $PID1


    for inner_memory in "${memory_array[@]}"
    do

        for inner_var in "${pct_array[@]}"
	    do
    	    echo $outer_var " " $inner_var " " ${outer_memory} " " ${inner_memory}

    	    make clean_gpu;
            make gpu_ert intens=$inner_var lim=$limit inf=0 memory=$inner_memory

	        echo "mon01nil" | sudo -S ../../c_parser/tegra_parse -t 50 -p gpu -l 1 -c 0 &> ../data/intensity/mixed/collocate_gpu/power_${inner_memory}_${inner_var}_colcpu_${outer_memory}_${outer_var} & PID2=$!
    	    echo "mon01nil" | sudo -S ./gpu_ert &> ../data/intensity/mixed/collocate_gpu/gpu_${inner_memory}_${inner_var}_colcpu_${outer_memory}_${outer_var}
    	    sleep 5s

    	    echo "mon01nil" | sudo -S kill  $(pidof gpu_ert)
    	    echo "mon01nil" | sudo -S kill  $(pidof tegra_parse)

        done

     done

     echo $PID1
     echo "mon01nil" | sudo -S kill $PID1
     echo "mon01nil" | sudo -S kill  $(pidof gpu_ert)
     echo "mon01nil" | sudo -S kill  $(pidof cpu_ert)
     echo "mon01nil" | sudo -S kill  $(pidof tegra_parse)

done
done


sleep 5s

# collocate cpu

for outer_memory in "${memory_array[@]}"
do
for outer_var in "${pct_array[@]}"
do
    make clean_gpu;
    make gpu_ert intens=$outer_var lim=$limit inf=1 memory=$outer_memory

    echo "mon01nil" | sudo -S ./gpu_ert & PID1=$!
    echo $PID1


    for inner_memory in "${memory_array[@]}"
    do

        for inner_var in "${pct_array[@]}"
	    do
    	    echo $outer_var " " $inner_var " " ${outer_memory} " " ${inner_memory}

    	    make clean_cpu;
            make cpu_ert intens=$inner_var lim=$limit inf=0 memory=$inner_memory

    	    #make pct=$inner_var inf=0
	        echo "mon01nil" | sudo -S ../../c_parser/tegra_parse -t 50 -p cpu -l 1 -c 0 &> ../data/intensity/mixed/collocate_cpu/power_${inner_memory}_${inner_var}_colgpu_${outer_memory}_${outer_var} & PID2=$!
    	    echo "mon01nil" | sudo -S ./cpu_ert &> ../data/intensity/mixed/collocate_cpu/cpu_${inner_memory}_${inner_var}_colgpu_${outer_memory}_${outer_var}
    	    sleep 5s

    	    echo "mon01nil" | sudo -S kill  $(pidof cpu_ert)
    	    echo "mon01nil" | sudo -S kill  $(pidof tegra_parse)

        done

     done

     echo $PID1
     echo "mon01nil" | sudo -S kill $PID1
     echo "mon01nil" | sudo -S kill  $(pidof gpu_ert)
     echo "mon01nil" | sudo -S kill  $(pidof cpu_ert)
     echo "mon01nil" | sudo -S kill  $(pidof tegra_parse)

done
done



