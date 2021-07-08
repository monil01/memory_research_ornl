NVCC=nvcc

all: vecmul

vecmul: vecmul.cu
	${NVCC} vecmul.cu -o vecmul

test: test.cu
	${NVCC} test.cu -o vecmul


clean:
	rm vecmul
