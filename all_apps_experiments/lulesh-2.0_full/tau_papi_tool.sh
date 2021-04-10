run_skylake()
{
    export TAU_METRICS=TIME,PAPI_NATIVE_skx_unc_imc0::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc1::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc4::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc5::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_skx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_skx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_skx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_skx_unc_imc2::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc3::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc2::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_skx_unc_imc3::UNC_M_CAS_COUNT:WR:cpu=12
 
    #taskset --cpu 12 ./tau_stencil_jacobi $1 $2
    #taskset --cpu 12 ./jacobi $1 $2
    taskset --cpu 16 ./lulesh2.0 -s $2 -i 1
    #taskset --cpu 16 ./lulesh2.0 -s 400 -i 1

    declare -i read=0
    declare -i write=0
    declare -i total=0


    echo "<<<<<<<< Memory access: TAU + PAPI dynamic analysis >>>>>>>"
    IFS=' ' read -ra ADDR <<< $(cat function_name.sh)
    for i in "${ADDR[@]}"; do
	name=$i
	i=" "$i"("
        #echo  "$i" 
    	IFS1=' ' read -ra ADDR1 <<< $(cat profile_folder_name_read.sh)
    	for j in "${ADDR1[@]}"; do
            #echo "$j" 
	    #pwd
	    cd $j 
	    	#pprof
    	    IFS3=' ' read -ra ADDR3 <<< $(pprof | grep -i "$i")
            temp=$(printf "%.0f" ${ADDR3[2]})
            #temp=$(printf "%.0f" ${ADDR3[1]}) #exclusive
	    	#echo $temp
    	    	#temp=${ADDR3[5]}*${ADDR3[3]}
    	    read=$read+$temp
	    	#echo $i ${ADDR3[5]} ${ADDR3[3]}  ${ADDR3[2]} 
	    	#echo $i ${ADDR3[0]} ${ADDR3[1]}  ${ADDR3[2]} ${ADDR3[3]} ${ADDR3[4]}  ${ADDR3[5]} 

	    cd ..
            #echo -n "$j" 
    	done
        #echo  $read

    	IFS4=' ' read -ra ADDR4 <<< $(cat profile_folder_name_write.sh)
    	for j in "${ADDR4[@]}"; do
            #echo "$j" 
	    #pwd
	    cd $j 
	    	#pprof
    	    IFS5=' ' read -ra ADDR5 <<< $(pprof | grep -i "$i")
            temp=$(printf "%.0f" ${ADDR5[2]})
            #temp=$(printf "%.0f" ${ADDR5[1]}) #exclusive
    	    	#temp=${ADDR5[5]}*${ADDR5[3]}
    	    write=$write+$temp
	    	#echo $i ${ADDR5[5]} ${ADDR5[3]}  ${ADDR5[2]} 
	    	#echo $i ${ADDR5[0]} ${ADDR5[1]}  ${ADDR5[2]} ${ADDR5[3]} ${ADDR5[4]}  ${ADDR5[5]} 
	    cd ..
            #echo -n "$j" 
    	done
        #echo  $write



    	#echo "read: $read $write"
    	total=$read+$write
    	#echo "$name: $read $write $total"
    	echo "$name: $total"

    	read=0
    	write=0
	total=0
    done
}


run_skylake1()
{
    
    # for oswald
    #export TAU_METRICS=TIME,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=12
    export TAU_METRICS=TIME,PAPI_NATIVE_skx_unc_imc0::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc1::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc4::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc5::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_skx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_skx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_skx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_skx_unc_imc2::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc3::UNC_M_CAS_COUNT:RD:cpu=12,PAPI_NATIVE_skx_unc_imc2::UNC_M_CAS_COUNT:WR:cpu=12,PAPI_NATIVE_skx_unc_imc3::UNC_M_CAS_COUNT:WR:cpu=12
 
    #taskset --cpu 12 ./tau_stencil_jacobi $1 $2
    #taskset --cpu 12 ./jacobi $1 $2
    #taskset --cpu 16 ./lulesh2.0 -s 300 -i 1


}


run_broadwell()
{
    
    # for oswald



    export TAU_METRICS=TIME,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:RD:cpu=16,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:RD:cpu=16,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:RD:cpu=16,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:RD:cpu=16,PAPI_NATIVE_bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=16,PAPI_NATIVE_bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=16,PAPI_NATIVE_bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=16,PAPI_NATIVE_bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=16
    #taskset --cpu 12 ./tau_stencil_jacobi $1 $2
    taskset --cpu 16 ./lulesh2.0 -s 300 -i 1
    #./jacobi $1 $2
}

#export OMP_PLACES='{16},{18},{20},{22},{24},{26},{28},{30}'

#stride_array=( 1 2 4 8 16 32 64 128 256 512 1024 2048	4096	8192	16384	32768	65536	131072	262144	524288	1048576	2097152	4194304	8388608	16777216	33554432	67108864)
#stride_array=(1 2 4 8 16 32 48 64 80 96 112 128 )
stride_array=(1)
#stride_array=(2 4 8 16 32 64 128 256 512)
#n_array=(250 300 400)
n_array=(400)
#n_array=(1000000 5000000 10000000 50000000 100000000 500000000 1000000000)


make clean
make

#intel-prefetch -d
#echo "" | sudo /usr/local/bin/intel-prefetch-disable -d

intel-prefetch-disable -d

for array_size in "${n_array[@]}"
do
    #echo "----------------------Array size = $array_size -------------------"
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
intel-prefetch-disable -e

for array_size in "${n_array[@]}"
do
    #echo "----------------------Array size = $array_size -------------------"
for stride in "${stride_array[@]}"
do
    #echo "----------------------stride = $stride-------------------"
    for i in 1
    #for i in 1 2 3 4 5 
    do
	run_skylake $stride $array_size
	#run_broadwell $stride $array_size
	rm -rf MULT*
	echo ""

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


