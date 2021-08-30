

#stride_array=(200)
#stride_array=(8192)
#stride_array=( 1 2 4 8 16 32 64 128 256 512 1024 2048	4096	8192	16384	32768	65536	131072	262144	524288	1048576	2097152	4194304	8388608	16777216	33554432	67108864)
#stride_array=(1 2 4 8 16 32 48 64 80 96 112 128 )
stride_array=(1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192)
#stride_array=(2 4 8 16 32 64 128 256 512)
n_array=(100000000)
#n_array=(5000000 50000000 500000000)
#n_array=(1000000 5000000 10000000 50000000 100000000 500000000)
#n_array=(1000000 5000000 10000000 50000000 100000000 500000000 1000000000)
#stride_array=(1 8 11)

#module load cuda
#module load nvhpc
make clean
make 

for array_size in "${n_array[@]}"
do
    echo "----------------------Array size = $array_size -------------------"
for stride in "${stride_array[@]}"
do
    #echo "----------------------stride = $stride-------------------"
    for i in 1
    #for i in 1 2 3 4 5 
    do
	#nvprof -m dram_read_bytes,dram_write_bytes ./vecmul $stride $array_size
	#nvprof -m dram_read_transactions -m dram_write_transactions -m l2_read_transactions -m l2_write_transactions ./vecmul $stride $array_size
    rocprof -i input.txt vecmul $stride $array_size
    cat input.csv >> output


	#run_skylake $stride $array_size
	#run_broadwell $stride $array_size
	#rm -rf MULT*

    done
done
done
