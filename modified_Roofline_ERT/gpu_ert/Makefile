CC = g++
ARCH=sm_35
#CFLAGS = -DBW_PCT=${pct} -DINFIN_LOOP=${inf} -DLIM=${lim}
#CFLAGS = -O3 -DINTENS=${intens} -DINFIN_LOOP=${inf} -DLIM=${lim}
CFLAGS = -O3  -DLIM=${lim}



all: gpu_ert

gpu_ert : driver1.cu Makefile
	nvcc -std=c++11 -ccbin=$(CC) $(CFLAGS) driver1.cu -arch=$(ARCH) -o gpu_ert 

.PHONY: clean
clean :
	rm -f gpu_ert 


