


run_skylake()
{
    
    # for oswald
    #export TAU_METRICS=TIME,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:RD:cpu=18,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:RD:cpu=18,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:RD:cpu=18,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:RD:cpu=18,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=18
    export TAU_METRICS=TIME,PAPI_NATIVE_skx_unc_imc0::UNC_M_CAS_COUNT:RD:cpu=18,PAPI_NATIVE_skx_unc_imc1::UNC_M_CAS_COUNT:RD:cpu=18,PAPI_NATIVE_skx_unc_imc4::UNC_M_CAS_COUNT:RD:cpu=18,PAPI_NATIVE_skx_unc_imc5::UNC_M_CAS_COUNT:RD:cpu=18,PAPI_NATIVE_skx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_skx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_skx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_skx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_skx_unc_imc2::UNC_M_CAS_COUNT:RD:cpu=18,PAPI_NATIVE_skx_unc_imc3::UNC_M_CAS_COUNT:RD:cpu=18,PAPI_NATIVE_skx_unc_imc2::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_skx_unc_imc3::UNC_M_CAS_COUNT:WR:cpu=18
 
    #taskset --cpu 12 ./tau_stencil_jacobi $1 $2
    #taskset --cpu 12 ./jacobi $1 $2
    taskset --cpu 18 ./lulesh2.0 -s 300 -i 1

    #export TAU_METRICS=TIME,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=18
#taskset --cpu 12 ./tau_stencil_jacobi


    #ls

    #echo " data for each counters"
    #echo " " 
    declare -i read=0
    declare -i write=0

    cd MULTI__PAPI_NATIVE_skx_unc_imc0__UNC_M_CAS_COUNT_RD_cpu\=18
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
       #for i in "${ADDR[@]}"; do
       #  echo -n "$i" 
       #done
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc1__UNC_M_CAS_COUNT_RD_cpu\=18
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc2__UNC_M_CAS_COUNT_RD_cpu\=18
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
       #for i in "${ADDR[@]}"; do
       #  echo -n "$i" 
       #done
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc3__UNC_M_CAS_COUNT_RD_cpu\=18
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc4__UNC_M_CAS_COUNT_RD_cpu\=18
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc5__UNC_M_CAS_COUNT_RD_cpu\=18
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc0__UNC_M_CAS_COUNT_WR_cpu\=18
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc1__UNC_M_CAS_COUNT_WR_cpu\=18
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc2__UNC_M_CAS_COUNT_WR_cpu\=18
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc3__UNC_M_CAS_COUNT_WR_cpu\=18
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc4__UNC_M_CAS_COUNT_WR_cpu\=18
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_skx_unc_imc5__UNC_M_CAS_COUNT_WR_cpu\=18
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
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



    export TAU_METRICS=TIME,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:RD:cpu=18,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:RD:cpu=18,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:RD:cpu=18,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:RD:cpu=18,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=18
    #taskset --cpu 12 ./tau_stencil_jacobi $1 $2
    taskset --cpu 16 ./lulesh2.0 -s 300 -i 1
    #./jacobi $1 $2

    #export TAU_METRICS=TIME,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=18,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=18
#taskset --cpu 12 ./tau_stencil_jacobi


    #ls

    #echo " data for each counters"
    #echo " " 
    declare -i read=0
    declare -i write=0

    cd MULTI__PAPI_NATIVE_bdx_unc_imc0__UNC_M_CAS_COUNT_RD_cpu\=18
pprof
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
       #for i in "${ADDR[@]}"; do
       #  echo -n "$i" 
       #done
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc1__UNC_M_CAS_COUNT_RD_cpu\=18
pprof
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc4__UNC_M_CAS_COUNT_RD_cpu\=18
pprof
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc5__UNC_M_CAS_COUNT_RD_cpu\=18
pprof
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc0__UNC_M_CAS_COUNT_WR_cpu\=18
pprof
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc1__UNC_M_CAS_COUNT_WR_cpu\=18
pprof
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc4__UNC_M_CAS_COUNT_WR_cpu\=18
pprof
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc5__UNC_M_CAS_COUNT_WR_cpu\=18
pprof
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "LagrangeNodal")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..
    
    #write=$write*64
    #read=$read*64
    echo "stride: $stride $read $write"
}


#export OMP_PLACES='{16},{18},{20},{22},{24},{26},{28},{30}'

export OMP_NUM_THREADS=1


#stride_array=(1)
#stride_array=( 1 2 4 8 16 32 64 128 256 512 1024 2048	4096	8192	16384	32768	65536	131072	262144	524288	1048576	2097152	4194304	8388608	16777216	33554432	67108864)
#stride_array=(1)
#stride_array=(1 2 4 8 16 32 48 64 80 96 112 128 )
stride_array=(1)
#stride_array=(2 4 8 16 32 64 128 256 512)
n_array=(100000000)
#n_array=(5000000 50000000 500000000)
#n_array=(1000000 5000000 10000000 50000000 100000000 500000000)
#n_array=(1000000 5000000 10000000 50000000 100000000 500000000 1000000000)
#stride_array=(1 8 11)


make clean
make

#intel-prefetch -d
echo "" | sudo -S /home/users/mmonil/package/intel/uarch-configure/intel-prefetch/intel-prefetch-disable -d

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
	run_skylake $stride $array_size
	#run_broadwell $stride $array_size
	rm -rf MULT*

    done
done
done

#intel-prefetch -e
echo "" | sudo -S /home/users/mmonil/package/intel/uarch-configure/intel-prefetch/intel-prefetch-disable -e
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
	run_skylake $stride $array_size
	#run_broadwell $stride $array_size
	rm -rf MULT*

    done
done
done

#for stride in "${stride_array[@]}"
#do
#    #echo "----------------------stride = $stride-------------------"
#    for i in 1 
#    #for i in 1 2 3 4 5 
#    do
#	run $stride
#	rm -rf MULT*
#
#    done
#done


