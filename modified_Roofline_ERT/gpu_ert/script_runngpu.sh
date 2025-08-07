#!/bin/bash


#pct_array=(70)
pct_array=(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20)

#pct_array=(100 90 80 70 60 50 40 30 20 10)
#iteration_array=(1 2 3 4 5)


for pct_var in "${pct_array[@]}"
do
    echo $pct_var
    make clean;
    #make pct=100 inf=0
    #make pct=$pct_var inf=0
    make intens=$pct_var inf=0 lim=35

    #sudo ./gpu_ert
    echo "now $pct_var$"
    ./gpu_ert 7
done
    
