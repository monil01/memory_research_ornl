


run_skylake()
{
    
    # for oswald
    #export TAU_METRICS=TIME,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=12
    export TAU_METRICS=TIME,PAPI_NATIVE_skx_unc_imc0::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc1::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc4::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc5::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_skx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_skx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_skx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_skx_unc_imc2::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc3::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc2::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_skx_unc_imc3::UNC_M_CAS_COUNT:WR:cpu=12
 
    taskset --cpu 12 ./tau_vecmul $1 $2

    #export TAU_METRICS=TIME,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=12
#taskset --cpu 12 ./tau_vecmul


    #ls

    #echo " data for each counters"
    #echo " " 
    declare -i read=0
    declare -i write=0

    cd MULTI__PAPI_NATIVE_skx_unc_imc0__UNC_M_CAS_COUNT_RD_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
       #for i in "${ADDR[@]}"; do
       #  echo -n "$i" 
       #done
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc1__UNC_M_CAS_COUNT_RD_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc2__UNC_M_CAS_COUNT_RD_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
       #for i in "${ADDR[@]}"; do
       #  echo -n "$i" 
       #done
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc3__UNC_M_CAS_COUNT_RD_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc4__UNC_M_CAS_COUNT_RD_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc5__UNC_M_CAS_COUNT_RD_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc0__UNC_M_CAS_COUNT_WR_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc1__UNC_M_CAS_COUNT_WR_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc2__UNC_M_CAS_COUNT_WR_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc3__UNC_M_CAS_COUNT_WR_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc4__UNC_M_CAS_COUNT_WR_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc5__UNC_M_CAS_COUNT_WR_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..
    
    #write=$write*64
    #read=$read*64
    echo "stride: $stride $read $write"
}


run_broadwell()
{

    # for oswald



    export TAU_METRICS=TIME,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:RD:cpu=16,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:RD:cpu=16,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:RD:cpu=16,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:RD:cpu=16,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=16,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=16,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=16,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=16
    #taskset --cpu 12 ./tau_vecmul $1 $2
    ./omp_vecmul $1 $2

    #export TAU_METRICS=TIME,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=12
#taskset --cpu 12 ./tau_vecmul


    #ls

    #echo " data for each counters"
    #echo " " 
    declare -i read=0
    declare -i write=0

    cd MULTI__PAPI_NATIVE_bdx_unc_imc0__UNC_M_CAS_COUNT_RD_cpu\=16
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
       #for i in "${ADDR[@]}"; do
       #  echo -n "$i" 
       #done
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]}
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc1__UNC_M_CAS_COUNT_RD_cpu\=16
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]}
    cd ..
    cd MULTI__PAPI_NATIVE_bdx_unc_imc4__UNC_M_CAS_COUNT_RD_cpu\=16
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]}
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc5__UNC_M_CAS_COUNT_RD_cpu\=16
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]}
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc0__UNC_M_CAS_COUNT_WR_cpu\=16
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]}
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc1__UNC_M_CAS_COUNT_WR_cpu\=16
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]}
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc4__UNC_M_CAS_COUNT_WR_cpu\=16
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]}
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc5__UNC_M_CAS_COUNT_WR_cpu\=16
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]}
    cd ..

    #write=$write*64
    #read=$read*64
    echo "stride: $stride $read $write"
}



numa_run_broadwell()
{
    
    # for oswald



    #export TAU_METRICS=TIME,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:RD:cpu=16,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:RD:cpu=16,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:RD:cpu=16,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:RD:cpu=16,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=16,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=16,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=16,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=16
    export TAU_METRICS=TIME,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:RD:cpu=16,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:RD:cpu=16,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:RD:cpu=16,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:RD:cpu=16,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=16,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=16,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=16,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=16,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:RD:cpu=0,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:RD:cpu=0,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:RD:cpu=0,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:RD:cpu=0,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=0,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=0,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=0,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=0


    #taskset --cpu 12 ./tau_vecmul $1 $2
    ./omp_vecmul $1 $2

    #export TAU_METRICS=TIME,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=12
#taskset --cpu 12 ./tau_vecmul


    #ls

    #echo " data for each counters"
    #echo " " 
    declare -i read=0
    declare -i write=0

    cd MULTI__PAPI_NATIVE_bdx_unc_imc0__UNC_M_CAS_COUNT_RD_cpu\=16
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
       #for i in "${ADDR[@]}"; do
       #  echo -n "$i" 
       #done
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc1__UNC_M_CAS_COUNT_RD_cpu\=16
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc4__UNC_M_CAS_COUNT_RD_cpu\=16
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc5__UNC_M_CAS_COUNT_RD_cpu\=16
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc0__UNC_M_CAS_COUNT_WR_cpu\=16
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc1__UNC_M_CAS_COUNT_WR_cpu\=16
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc4__UNC_M_CAS_COUNT_WR_cpu\=16
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc5__UNC_M_CAS_COUNT_WR_cpu\=16
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..
   
    cd MULTI__PAPI_NATIVE_bdx_unc_imc0__UNC_M_CAS_COUNT_RD_cpu\=0
#pprof
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
       #for i in "${ADDR[@]}"; do
       #  echo -n "$i" 
       #done
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc1__UNC_M_CAS_COUNT_RD_cpu\=0
#pprof
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc4__UNC_M_CAS_COUNT_RD_cpu\=0
#pprof
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc5__UNC_M_CAS_COUNT_RD_cpu\=0
#pprof
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc0__UNC_M_CAS_COUNT_WR_cpu\=0
#pprof
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc1__UNC_M_CAS_COUNT_WR_cpu\=0
#pprof
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc4__UNC_M_CAS_COUNT_WR_cpu\=0
#pprof
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc5__UNC_M_CAS_COUNT_WR_cpu\=0
#pprof
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..
 
    #write=$write*64
    #read=$read*64
    echo "stride: $stride $read $write"
}

export OMP_NUM_THREADS=16
#export OMP_NUM_THREADS=8

#export OMP_PLACES='{2}, {4}, {6}, {8}, {16},{18},{20},{22}'
export OMP_PLACES='{16},{17}, {18}, {19}, {20}, {21}, {22}, {23}, {24}, {25}, {26}, {27}, {28}, {29}, {30}, {31}'


#stride_array=(1)
#stride_array=( 1 2 4 8 16 32 64 128 256 512 1024 2048	4096	8192	16384	32768	65536	131072	262144	524288	1048576	2097152	4194304	8388608	16777216	33554432	67108864)
#stride_array=(1)
#stride_array=(1 2 4 8 16 32 48 64 80 96 112 128 )
#stride_array=(1)
stride_array=(1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192)
#stride_array=(2 4 8 16 32 64 128 256 512)
n_array=(100000000)
#n_array=(5000000 50000000 500000000)
#n_array=(1000000 5000000 10000000 50000000 100000000 500000000)
#n_array=(1000000 5000000 10000000 50000000 100000000 500000000 1000000000)
#stride_array=(1 8 11)


make clean
make omp

intel-prefetch -d

#intel-prefetch-disable -d

for array_size in "${n_array[@]}"
do
    echo "----------------------Array size = $array_size -------------------"
for stride in "${stride_array[@]}"
do
    #echo "----------------------stride = $stride-------------------"
    for i in 1
    #for i in 1 2 3 4 5 
    do
	#run_skylake $stride $array_size
	run_broadwell $stride $array_size
	rm -rf MULT*

    done
done
done

intel-prefetch -e
#intel-prefetch-disable -e

for array_size in "${n_array[@]}"
do
    echo "----------------------Array size = $array_size -------------------"
for stride in "${stride_array[@]}"
do
    #echo "----------------------stride = $stride-------------------"
    for i in 1
    #for i in 1 2 3 4 5 
    do
	#run_skylake $stride $array_size
	run_broadwell $stride $array_size
	rm -rf MULT*

    done
done
done



export OMP_PLACES='{0}, {2}, {4}, {6}, {8}, {10}, {12}, {14}, {16},{18},{20},{22},{24},{26},{28},{30}'
#export OMP_PLACES='{2}, {4}, {6}, {8}, {16},{18},{20},{22}'
#export OMP_PLACES='{2},{16}'

intel-prefetch -d

#intel-prefetch-disable -d

for array_size in "${n_array[@]}"
do
    echo "----------------------Array size = $array_size -------------------"
for stride in "${stride_array[@]}"
do
    #echo "----------------------stride = $stride-------------------"
    for i in 1
    #for i in 1 2 3 4 5 
    do
	#run_skylake $stride $array_size
	numa_run_broadwell $stride $array_size
	rm -rf MULT*

    done
done
done

intel-prefetch -e
#intel-prefetch-disable -e

for array_size in "${n_array[@]}"
do
    echo "----------------------Array size = $array_size -------------------"
for stride in "${stride_array[@]}"
do
    #echo "----------------------stride = $stride-------------------"
    for i in 1
    #for i in 1 2 3 4 5 
    do
	#run_skylake $stride $array_size
	numa_run_broadwell $stride $array_size
	rm -rf MULT*

    done
done
done



