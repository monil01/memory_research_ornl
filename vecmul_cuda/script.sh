module load cuda
make clean
make


nvprof -m dram_read_bytes,dram_write_bytes ./vecmul
