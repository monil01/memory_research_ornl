# CXX compiler
CC = gcc
C_FLAGS = -O3

cpu: tegra_parse_cpu
gpu: tegra_parse_gpu

tegra_parse_cpu: parse_tegra_cpu.c
	$(CC) $(CC_FLAGS) parse_tegra_cpu.c -o $@ 

tegra_parse_gpu: parse_tegra_gpu.c
	$(CC) $(CC_FLAGS) parse_tegra_gpu.c -o $@ 


clean:
	rm -f *.o tegra_parse tegra_parse_cpu tegra_parse_gpu 
