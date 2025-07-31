#!/bin/bash

cd ..
#pct_array=(90 80)
#pct_array=(100 90 80 70 60 50 40 30 20 10)
#iteration_array=(1 2 3 4 5)
#pct_array=(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20)
pct_array=(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15)
#pct_array=(100 90 80 70 60 50 40 30 20 10)
#iteration_array=(1 2 3 4 5)
limit=100

# standalone cpu
cd cpu_ert

for pct_var in "${pct_array[@]}"
do
    echo $pct_var
    make clean;
    #make pct=100 inf=0
    make intens=$pct_var inf=0 lim=$limit
    #make pct=$pct_var inf=0

    #sudo ./gpu_ert
    echo "now $pct_var$"
    echo "mon01nil" | sudo -S ./cpu_ert &> ../data/intensity/standalone_cpu/cpu_${pct_var} & sudo ../../c_parser/tegra_parse -t 50 -p cpu -l 1 -c 0 &> ../data/intensity/standalone_cpu/power_${pct_var}
    sleep 5s
done

cd ..

sleep 5s

# standalone gpu
cd gpu_ert

for pct_var in "${pct_array[@]}"
do
    echo $pct_var
    make clean;
    #make pct=100 inf=0
    #make pct=$pct_var inf=0
    make intens=$pct_var inf=0 lim=$limit

    #sudo ./gpu_ert
    echo "now $pct_var$"
    echo "mon01nil" | sudo -S ./gpu_ert &> ../data/intensity/standalone_gpu/gpu_${pct_var} & ../../c_parser/tegra_parse -t 50 -p gpu -l 1 -c 0 &> ../data/intensity/standalone_gpu/power_${pct_var}
    sleep 5s
done

cd ..

sleep 5s

exit 1

# collocate gpu

for outer_var in "${pct_array[@]}"
do
    cd cpu_ert
    make clean;
    make intens=$outer_var inf=1 lim=$limit
    #make pct=$outer_var inf=1

    echo "mon01nil" | sudo -S ./cpu_ert & PID1=$!
    echo $PID1

    cd ../gpu_ert

    for inner_var in "${pct_array[@]}"
	do
    	echo $outer_var " " $inner_var

    	make clean;
    	make intens=$inner_var inf=0 lim=$limit
    	#make pct=$inner_var inf=0
	echo "mon01nil" | sudo -S ../../c_parser/tegra_parse -t 50 -p gpu -l 1 -c 0 &> ../data/intensity/collocate_gpu/power_${inner_var}_colcpu_${outer_var} & PID2=$!
    	echo "mon01nil" | sudo -S ./gpu_ert &> ../data/intensity/collocate_gpu/gpu_${inner_var}_colcpu_${outer_var}
    	sleep 5s

    	echo "mon01nil" | sudo -S kill  $(pidof gpu_ert)
    	echo "mon01nil" | sudo -S kill  $(pidof tegra_parse)

    done

    echo $PID1
    echo "mon01nil" | sudo -S kill $PID1
    echo "mon01nil" | sudo -S kill  $(pidof gpu_ert)
    echo "mon01nil" | sudo -S kill  $(pidof cpu_ert)
    echo "mon01nil" | sudo -S kill  $(pidof tegra_parse)

   

    cd ..

done

sleep 5s

# collocate cpu

for outer_var in "${pct_array[@]}"
do
    cd gpu_ert
    make clean;
    make intens=$outer_var inf=1 lim=$limit
    #make pct=$outer_var inf=1

    echo "mon01nil" | sudo -S ./gpu_ert & PID1=$!

    cd ../cpu_ert

    for inner_var in "${pct_array[@]}"
	do
    	echo $outer_var " " $inner_var

    	make clean;
    	make intens=$inner_var inf=0 lim=$limit
    	#make pct=$inner_var inf=0
	echo "mon01nil" | sudo -S ../../c_parser/tegra_parse -t 50 -p cpu -l 1 -c 0 &> ../data/intensity/collocate_cpu/power_${inner_var}_colgpu_${outer_var} & PID2=$!
    	echo "mon01nil" | sudo -S ./cpu_ert &> ../data/intensity/collocate_cpu/cpu_${inner_var}_colgpu_${outer_var}
    	sleep 5s

	echo "mon01nil" | sudo -S kill  $(pidof cpu_ert)
    	echo "mon01nil" | sudo -S kill  $(pidof tegra_parse)



    done

    echo "mon01nil" | sudo -S kill $PID1
    echo "mon01nil" | sudo -S kill  $(pidof gpu_ert)
    echo "mon01nil" | sudo -S kill  $(pidof cpu_ert)
    echo "mon01nil" | sudo -S kill  $(pidof tegra_parse)

    cd ..

done
       
