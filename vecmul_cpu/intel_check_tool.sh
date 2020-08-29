


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
    declare -i write_ratio=$2/$1

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
    #write_ratio=$write/$write_ratio
    #echo "$stride $(($write/$write_ratio))" >> temp
    VAR=$(echo "scale=4; $write/$write_ratio" | bc)
    ideal=$(echo "scale=4; $1/16" | bc)
    #echo $VAR
    echo "$stride $ideal $VAR" >> temp
    #echo "stride: $stride $read $write"
}

run_broadwell()
{
    
    # for oswald
    export TAU_METRICS=TIME,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=12

    echo " started executing"
    taskset --cpu 12 ./tau_vecmul $1 $2
    echo " finished executing"

    #export TAU_METRICS=TIME,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=12
#taskset --cpu 12 ./tau_vecmul


    #ls

    #echo " data for each counters"
    #echo " " 
    declare -i read=0
    declare -i write=0
    declare -i write_ratio=$2/$1



    cd MULTI__PAPI_NATIVE_bdx_unc_imc0__UNC_M_CAS_COUNT_RD_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
       #for i in "${ADDR[@]}"; do
       #  echo -n "$i" 
       #done
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc1__UNC_M_CAS_COUNT_RD_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc4__UNC_M_CAS_COUNT_RD_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc5__UNC_M_CAS_COUNT_RD_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    read=$read+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc0__UNC_M_CAS_COUNT_WR_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc1__UNC_M_CAS_COUNT_WR_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc4__UNC_M_CAS_COUNT_WR_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..

    cd MULTI__PAPI_NATIVE_bdx_unc_imc5__UNC_M_CAS_COUNT_WR_cpu\=12
    IFS=' ' read -ra ADDR <<< $(pprof | grep -i "vecmul(")
    #echo ${ADDR[5]}
    write=$write+${ADDR[5]} 
    cd ..
     
    #write=$write*64
    #read=$read*64
    #write_ratio=$write/$write_ratio
    #echo "$stride $(($write/$write_ratio))" >> temp
    VAR=$(echo "scale=4; $write/$write_ratio" | bc)
    ideal=$(echo "scale=4; $1/16" | bc)
    #echo $VAR
    echo "$stride $ideal $VAR"
    echo "$stride $ideal $VAR" >> temp
    #echo "stride: $stride $read $write"

}



stride_array=( 4 8 16 32 64 128 256)
#stride_array=(1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192)
n_array=(5000000)

rm temp
make clean
make


for array_size in "${n_array[@]}"
do
for stride in "${stride_array[@]}"
do
    for i in 1
    do
	#run_skylake $stride $array_size
	run_broadwell $stride $array_size
	rm -rf MULT*
    done
done
done



