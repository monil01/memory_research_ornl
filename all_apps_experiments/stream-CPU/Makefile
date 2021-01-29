
ICC=icc

ICCFLAG=-qopt-streaming-stores=always -qopenmp -DSTREAM_ARRAY_SIZE=50000000
PAPILD=-lpapi

CC = tau_cxx.sh -optCompInst
#CFLAGS = -DSTREAM_TYPE=float 
CFLAGS=  -qopt-streaming-stores=always
#CFLAGS = -O3 -fopenmp -DSTREAM_ARRAY_SIZE=${val} -DNTIMES=20 -DSTREAM_TYPE=float 
#CFLAGS = 

FF = g77
FFLAGS = -O2

all: stream_c.exe

PAPILDPATH=-L/home/mmonil/packages/download_tar/papi/src/install/lib
PAPIINCLUDE=-I/home/mmonil/packages/download_tar/papi/src/install/include
PAPILDPATH_PW=-L/home/mmonil/packages/download_tar/papi_pw/src/install/lib
PAPIINCLUDE_PW=-I/home/mmonil/packages/download_tar/papi_pw/src/install/include


nat: stream.c
	#${GCC} ${PAPIINCLUDE} ${PAPILDPATH} ${GCCFLAG} vecmul_NAT_PAPI.c -o vecmul_NAT_PAPI ${PAPILD}
	${ICC} ${PAPIINCLUDE} ${PAPILDPATH} ${ICCFLAG} stream.c -o stream ${PAPILD}


stream_f.exe: stream.f mysecond.o
	$(CC) $(CFLAGS) -DSTREAM_ARRAY_SIZE=268435456 -c mysecond.c
	$(FF) $(FFLAGS) -c stream.f
	$(FF) $(FFLAGS) stream.o mysecond.o -o stream_f.exe

stream_c.exe: stream.c
	$(CC) $(CFLAGS) stream.c -o stream_c.exe -qopenmp
	#$(CC) $(CFLAGS) stream.c -o stream_c.exe -fopenmp

clean:
	rm -f stream_f.exe stream_c.exe *.o

# an example of a more complex build line for the Intel icc compiler
stream.icc: stream.c
	#icc -O3  -DSTREAM_ARRAY_SIZE=100000000 -DNTIMES=1 stream.c -o stream.omp.AVX2.80M.20x.icc
	icc -O3 -xCORE-AVX2 -ffreestanding -qopenmp -DSTREAM_ARRAY_SIZE=100000000 -DNTIMES=1 stream.c -o stream.omp.AVX2.80M.20x.icc
