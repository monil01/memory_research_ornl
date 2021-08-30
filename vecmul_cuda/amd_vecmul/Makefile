NVCC=nvcc
HIP=hipcc
#NVCCFLAG=-arch=sm_37 
#\
 -gencode=arch=compute_50,code=sm_50 \
 -gencode=arch=compute_52,code=sm_52 \
 -gencode=arch=compute_60,code=sm_60 \
 -gencode=arch=compute_61,code=sm_61 \
 -gencode=arch=compute_62,code=sm_62 \
 -gencode=arch=compute_70,code=sm_70 \
 -gencode=arch=compute_70,code=compute_70 

all: vecmul-hip

vecmul: vecmul.cu
	${NVCC} ${NVCCFLAG} vecmul.cu -o vecmul

vecmul-hip: vecmul_hip.cpp
	${HIP} vecmul_hip.cpp -o vecmul


test: test.cu
	${NVCC} test.cu -o vecmul


clean:
	rm vecmul output
