module load cuda
make clean
make
nvprof -m dram_read_transactions -m dram_write_transactions -m l2_read_transactions -m l2_write_transactions ./vecmul

